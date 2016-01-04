package Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.function.BiConsumer;

import shared.*;

public class Server {

	public static void main(String[] args) {
		final int PORT = 1001;
		Server server = new Server(PORT, "./");
		System.out.println("Starting server on port: " + PORT);

		Runtime.getRuntime().addShutdownHook(new Thread() {
			public void run() {
				if(server != null)
					server.dispose();
			}
		});

		while(true)
			server.AcceptConnection();
	}

	public Server(int port, String storage_directory) {
		m_port = port;
		m_client_connections = new HashMap<>();
		m_groups = new HashMap<>();
		m_messages = new HashMap<>();
		m_usernames = new HashMap<>();
		m_server_socket = null;
		m_storage = new StorageDAL(storage_directory, e -> {
			// TODO: handle exceptions
		});

		// Read stored user accounts, groups and messages if any
		List<User> users = m_storage.GetStoredUsers();
		Map<Group, List<Message>> groups_with_messages = m_storage.GetStoredGroups();
		if(users != null) {
			// Load users
			for(User user : users) {
				if(user != null)
					m_usernames.put(user.Id, user.Name);
			}
			System.out.println("Loaded " + users.size() + " user account(s).");

			// Load groups and messages
			if(groups_with_messages != null) {
				groups_with_messages.forEach((group, messages) -> {
					if(group != null) {
						m_groups.put(group, new HashSet<>());
						if(messages != null)
							m_messages.put(group, messages);
						else
							m_messages.put(group, new ArrayList<>());
					}
				});
				System.out.println("Loaded " + groups_with_messages.size() + " group(s).");
			}
		}

		// Make storage DAL ready to append objects to history
		m_storage.InitStorageWriting();
	}
	
	public void AcceptConnection() {
		try {
			if(m_server_socket == null)
				m_server_socket = new ServerSocket(m_port);
			Socket socket_to_client = m_server_socket.accept();
			if(socket_to_client != null)
			{
				UUID temporary_id = UUID.randomUUID();
				ClientConnection new_connection = new ClientConnection(socket_to_client, temporary_id, this);
				new_connection.open();
				new_connection.start();
				m_client_connections.put(temporary_id, new_connection);
				System.out.println("Client connected");
			}
		} catch (IOException e) {
			// TODO: handle except.
        }
	}

	@Override
	public void finalize() throws Throwable {
		super.finalize();
		dispose();
	}

	public void dispose() {
		System.out.println("Disposing server...");

		// Close client connections
		if(m_client_connections != null) {
			m_client_connections.forEach((uuid, clientConnection) -> {
				if(clientConnection != null)
					clientConnection.close();
			});
		}

		try {
			if(m_server_socket != null)
				m_server_socket.close();
		} catch (IOException e) { }

		if(m_storage != null)
			m_storage.CloseStorage();

		m_server_socket = null;
		m_storage = null;
	}

	public void on_user_disconnected(UUID user_id, String username, Group group) {
		// Remove user from its group if necessary
		QuitGroup(new User(user_id, username), group);
		// Remove user connection
		if(m_client_connections.remove(user_id) != null)
			System.out.println("Client disconnected");

	}

	public boolean CreateUser(String username, UUID id) {
		if(username != null)
			if(!username.equals(""))
				if(!m_usernames.containsValue(username))
					if(m_usernames.putIfAbsent(id, username) == null) {
						m_storage.AppendUser(new User(id, username));
						System.out.println("New user created: " + username);
						return true;
					}
		return false;
	}

	public boolean Login(String username, UUID password, UUID connection_temporary_id) {
		if(password != null && username != null) {
			if(!username.equals(""))  {
				String pass_username = m_usernames.get(password);
				if(pass_username != null) {
					if (pass_username.equals(username)) {
						// Update key/password associated with user connection according to user credentials
						ClientConnection connection = m_client_connections.remove(connection_temporary_id);
						m_client_connections.put(password, connection);
						return true;
					}
				}
			}
		}
		return false;
	}

	public Group CreateGroup(User creator, String name) {
		Group new_group = new Group(new Date(), name);
		if (!m_groups.containsKey(new_group) && !name.isEmpty())
		{
			HashSet<User> users = new HashSet<>();
			users.add(creator);
			m_groups.put(new_group, users);
			m_messages.put(new_group, new ArrayList<>());
			m_storage.AppendGroup(new_group);
			System.out.println("New group created: " + name);

			// Update group list for every client
			m_client_connections.forEach((uuid, clientConnection) -> {
				ServerRequest request = new ServerRequest(ServerRequest.Type.GROUP_LIST_UPDATED, new_group);
				clientConnection.SendRequest(request);
			});

			return new_group;
		}
		return null;
	}

	// Retourne les utilisateurs du groupe ainsi que l'historique des messages si l'utilisateur a effectivement rejoint le groupe (retourne null sinon)
	public Pair<String[], List<Message>> JoinGroup(User user, Group group) {
		if(user != null && group != null) {
			// Add user to specified group if we can find it (we suppose user is correct)
			HashSet<User> group_users = m_groups.get(group);
			if(group_users != null)
				if(group_users.add(user)) {
					String[] usernames = new String[group_users.size()];
					int i = 0;
					for(User group_user : group_users) {
						usernames[i] = group_user.Name;
						++i;

						// Update group's user list for every users in this group
						ServerRequest request = new ServerRequest(ServerRequest.Type.GROUP_USER_LIST_UPDATED, true, user.Name);
						m_client_connections.get(group_user.Id).SendRequest(request);
					}
					return new Pair<>(usernames, m_messages.get(group));
				}
		}
		return null;
	}

	public boolean QuitGroup(User user, Group group) {
		if(user != null && group != null) {
			Group group_stored = (Group)m_groups.keySet().toArray()[0];
			HashSet<User> group_users = m_groups.get(group);
			if(group_users != null) {
				if (group_users.remove(user))
				{
					// Update group's user list for every users in this group
					for (User group_user : group_users) {
						ServerRequest request = new ServerRequest(ServerRequest.Type.GROUP_USER_LIST_UPDATED, false, user.Name);
						m_client_connections.get(group_user.Id).SendRequest(request);
					}
					return true;
				}
			}
		}
		return false;
	}

	public void SendMessageToGroup(User user, Group group, Message message){
		ServerRequest request = new ServerRequest(ServerRequest.Type.SEND_MESSAGE, message);
		HashSet<User> group_users = m_groups.get(group);
		
		if(!group_users.contains(user))
			return; // TODO: user trying to send message to other groups (disconnect user?)

		// Store message to history
		m_messages.get(group).add(message);
		m_storage.AppendMessage(group, message);

		// Send message to every group users
		for(User group_user : group_users) {
			ClientConnection connection = m_client_connections.get(group_user.Id);
			if(connection != null)
				connection.SendRequest(request);
			//else
				// TODO: uh oh ! (logout user ?)
		}
	}
	
	public Group[] GetGroups() {
		Group[] groups = new Group[m_groups.size()];
		return m_groups.keySet().toArray(groups);
	}

	private HashMap<UUID, ClientConnection> m_client_connections;
	private HashMap<Group, List<Message>> m_messages;
	private HashMap<Group, HashSet<User>> m_groups;
	private HashMap<UUID, String> m_usernames;

	private final int m_port;
	private StorageDAL m_storage;
	private ServerSocket m_server_socket;
}
