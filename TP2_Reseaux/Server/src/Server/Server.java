package Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

import shared.*;

public class Server {
	
	public static void main(String[] args) {
		Server server = new Server(1001);

		// TODO: ...	AcceptConnection()...
	}

	public Server(int port) {
		m_port = port;
		m_client_connections = new HashMap<UUID, ClientConnection>();
		m_groups = new HashMap<Group, HashSet<User>>();
		m_usernames = new HashSet<String>();
		m_server_socket = null;
	}
	
	public void AcceptConnection()
	{
		try {
			if(m_server_socket == null)
				m_server_socket = new ServerSocket(m_port);
			Socket socket_to_client = m_server_socket.accept();
			if(socket_to_client != null) //TODO :verif if null
			{
				UUID client_id = UUID.randomUUID();
				m_client_connections.put(client_id, new ClientConnection(socket_to_client, client_id, this));
			}
		} catch (IOException e) {
			// TODO: handle except.
        }
	}

	public void on_user_disconnected(UUID user_id, String username, Group group) {
		// Remove user from its group if necessary
		QuitGroup(new User(user_id, username), group);
		// Remove user connection
		m_client_connections.remove(user_id);
		// Remove reserved username if any
		if(username != null)
			m_usernames.remove(username);
	}

	public boolean CreateUser(String username) {
		return m_usernames.add(username);
	}

	public Group CreateGroup(User creator, String name)
	{
		Group new_group = new Group(new Date(), name);
		if(m_groups.containsKey(new_group))
			return null;
		else
		{
			HashSet<User> users = new HashSet<User>();
			users.add(creator);
			m_groups.put(new_group, users);
			return new_group;
		}
	}

	public Group JoinGroup(User user, Group group) {
		if(user != null && group != null) {
			// Add user to specified group if we can find it (we suppose user is correct)
			HashSet<User> group_users = m_groups.get(group);
			if(group_users != null)
				if(group_users.add(user))
					return group;
		}
		return null;
	}

	public boolean QuitGroup(User user, Group group) {
		if(user != null && group != null) {
			HashSet<User> group_users = m_groups.get(group);
			if(group_users != null)
				return group_users.remove(user);
		}
		return false;
	}

	public void SendMessageToGroup(User user, Group group, Message message){
		ServerRequest request = new ServerRequest(ServerRequest.Type.SEND_MESSAGE, message);
		HashSet<User> group_users = m_groups.get(group);
		
		if(!group_users.contains(user))
			return; // TODO: user trying to send message to other groups (disconnect user?)
		
		for(User group_user : group_users)
			m_client_connections.get(group_user).SendRequest(request);
	}
	
	public Group[] GetGroups()
	{
		Group[] groups = new Group[m_groups.size()];
		return m_groups.keySet().toArray(groups);
	}

	HashMap<UUID, ClientConnection> m_client_connections;
	HashMap<Group, HashSet<User>> m_groups;
	HashSet<String> m_usernames;

	final int m_port;
	ServerSocket m_server_socket;
}
