package Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.function.BiConsumer;

import shared.*;

/**
 * Classe principale du serveur (NON FINIE)
 * La classe Server permet de gèrer les connexions entrantes des clients, gèrer les comptes, gèrer les groupes/rooms et distribuer les messages dans ces groupes.
 * Server utilise également la classe storageDAL pour enregister son état (utilisateurs, groupes et messages) et pouvoir le charger au lancement du serveur.
 */
public class Server {

	/**
	 * Point d'entrée du programme côté serveur (lance le serveur).
	 */
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

	/**
	 * Construit un Server à partir d'un numéro de port et du chemin du dossier dans le quel l'état du serveur est stocké.
	 * @param port Numéro de port sur le quel lancer le serveur
	 * @param storage_directory chemin du dossier dans le quel l'état du serveur est stocké
	 */
	public Server(int port, String storage_directory) {
		m_port = port;
		m_client_connections = new HashMap<>();
		m_groups = new HashMap<>();
		m_messages = new HashMap<>();
		m_usernames = new HashMap<>();
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
		/*
				UUID temporary_id = UUID.randomUUID();
				ClientConnection new_connection = new ClientConnection(socket_to_client, temporary_id, this);
				new_connection.open();
				new_connection.start();
				m_client_connections.put(temporary_id, new_connection);
				System.out.println("Client connected");
		*/
	}

	/**
	 * Ferme le serveur.
	 * @throws Throwable
	 */
	@Override
	public void finalize() throws Throwable {
		super.finalize();
		dispose();
	}

	/**
	 * Ferme le serveur
	 */
	public void dispose() {
		System.out.println("Disposing server...");

		// Close client connections
		if(m_client_connections != null) {
			m_client_connections.forEach((uuid, clientConnection) -> {
				if(clientConnection != null)
					clientConnection.close();
			});
		}

		if(m_storage != null)
			m_storage.CloseStorage();

		m_storage = null;
	}

	/**
	 * Gère la déconnexion d'un client (appelé par les ClientConexion)
	 * @param user_id Id du client
	 * @param username Eventuel nom de l'utilisateur
	 * @param group Eventuel groupe dans lequel est l'utilisateur
	 */
	public void on_user_disconnected(UUID user_id, String username, Group group) {
		// Remove user from its group if necessary
		QuitGroup(new User(user_id, username), group);
		// Remove user connection
		if(m_client_connections.remove(user_id) != null)
			System.out.println("Client disconnected");

	}

	/**
	 * Crée un nouvel utilisateur si les paramètres sont corrects (noms d'utilisateur et id unique)
	 * @param username Nom de l'utilisateur
	 * @param id Id de l'utilisateur
	 * @return un booléen indiquant si l'utilisateur a effectivement été crée
	 */
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

	/**
	 * Vérifie la validité du nom d'utilisateur et de son mots de passe (Id) et modifie l'id temporaire de la connexion pour être l'id de l'utilisateur si les informations sont correctes.
	 * @param username Nom de l'utilisateur
	 * @param password Mots de passe de l'utilisateur
	 * @param connection_temporary_id Id temporaire de la connexion client
	 * @return un booléen indiquant que les informatiuons sont correctes (utilisateur loggé)
	 */
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

	/**
	 * Crée un groupe si il n'y a pas d'autre groupe ayant le même nom
	 * @param creator Créateur du groupe (utilisateur)
	 * @param name Nom du groupe à créer
	 * @return le groupe crée ou null si le groupe n'a pas été crée
	 */
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
				// TODO: call each rmi client with 'new_group' as parameter to update their group list
			});

			return new_group;
		}
		return null;
	}

	/**
	 * Permet à un utilisateur de rejoindre un groupe (si il n'est pas dejà dans un groupe et que le groupe est valide).
	 * @param user Utilisateur voulant joindre le groupe
	 * @param group Groupe à rejoindre
	 * @return Les utilisateurs du groupe ainsi que l'historique des messages si l'utilisateur a effectivement rejoint le groupe (retourne null sinon)
	 */
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

						// TODO: Update group's user list for every users in this group using RMI
					}
					return new Pair<>(usernames, m_messages.get(group));
				}
		}
		return null;
	}

	/**
	 * Permet à un utilisateur de quitter un groupe
	 * @param user Utilisateur voulant quitter le groupe
	 * @param group Groupe à quitter
	 * @return Un booléen indiquant si le groupe a bien été quittté
	 */
	public boolean QuitGroup(User user, Group group) {
		if(user != null && group != null) {
			HashSet<User> group_users = m_groups.get(group);
			if(group_users != null) {
				if (group_users.remove(user))
				{
					// TODO: Update group's user list for every users in this group using RMI
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Envoi un message donné en paramètre à tout les utilisateur d'un groupe (si possible et si l'auteur appartient bien au groupe).
	 * @param user Utilisateur ayant envoyé le message
	 * @param group Groupe dans lequel envoyer le message
	 * @param message Message à envoyer
	 */
	public void SendMessageToGroup(User user, Group group, Message message){
		HashSet<User> group_users = m_groups.get(group);
		
		if(!group_users.contains(user))
			return; // TODO: user trying to send message to other groups (disconnect user?)

		// Store message to history
		m_messages.get(group).add(message);
		m_storage.AppendMessage(group, message);

		// Send message to every group users
		for(User group_user : group_users) {
			ClientConnection connection = m_client_connections.get(group_user.Id);
			//if(connection != null)
				// TODO: send message to group_user using RMI
		}
	}

	/**
	 * Obtient la liste de tous les groupe crées
	 * @return La liste de tous les groupe crées
	 */
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
