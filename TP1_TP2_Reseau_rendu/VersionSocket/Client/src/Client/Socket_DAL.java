package Client;

import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.io.*;
import java.net.*;

import shared.*;

/**
 * Data access layer donnat accès au serveur gèrant le chat.
 * Gère la reception des requettes serveur sur son propre thread.
 */
public class Socket_DAL extends Thread {

	public Socket_DAL(String host_name, int port, Consumer<Exception> connection_error_callback) {
		reset_callbacks();
		m_error_callback = connection_error_callback;
		m_port = port;
		m_host_name = host_name;
	}

	public void open() {
		m_socket = null;
		m_os = null;
		m_oos = null;
		m_is = null;
		m_ois = null;
		reset_callbacks();
		
		try {
			m_socket = new Socket (m_host_name, m_port);
			m_os = m_socket.getOutputStream();
			m_oos = new ObjectOutputStream(m_os);
			m_is = m_socket.getInputStream();
			m_ois = new ObjectInputStream(m_is);
		} catch (IOException e) {
			if(m_error_callback != null)
				m_error_callback.accept(e);
			close();
        }
	}
	
	public void close() {
		try
		{
			DisposeConnection();
		} catch (IOException e) {
			//if(m_error_callback != null)
			//	m_error_callback.accept(e);
			/* TODO: savoir quoi faire ici */
        } finally {
			m_socket = null;
			m_os = null;
			m_oos = null;
			m_is = null;
			m_ois = null;
			reset_callbacks();
		}
	}

	@Override
	public void finalize() throws Throwable {
		super.finalize();
		DisposeConnection();
	}

	/**
	 * Modifie la callback appelée si un message est recu
	 * @param message_callback Callback appelée si un message est recu
     */
	public void setMessageCallback(Consumer<Message> message_callback) { m_message_callback = message_callback; }

	/**
	 * Modifie la callback appelée si une erreur se produit
	 * @param connection_error_callback Callback appelée si une erreur se produit
	 */
	public void setErrorCallback(Consumer<Exception> connection_error_callback) { m_error_callback = connection_error_callback; }

	/**
	 * Modifie la callback appelée si un groupe est crée (permet de mettre à jour la vue affichant la liste des groupes)
	 * @param group_list_update_callback Callback appelée si un groupe est crée
	 */
	public void setGroupListUpdateCallback(Consumer<Group> group_list_update_callback) { m_group_list_update_callback = group_list_update_callback; }

	/**
	 * Modifie la callback appelée si un utilisateur quitte ou rejoint le groupe dans lequel l'utilisateur est présent (permet de mettre à jour la vue affichant la liste des utilisateur du groupe)
	 * @param group_user_list_update_callback Callback appelée si un utilisateur quitte ou rejoint le groupe dans lequel l'utilisateur est présent
     */
	public void setGroupUserListCallback(BiConsumer<Boolean, String> group_user_list_update_callback) { m_group_user_list_update_callback = group_user_list_update_callback; }

	public void CreateGroup(User user, String group_name, Consumer<Group> group_callback) {
		if(m_oos != null && !m_sending_request && !m_is_disposing)
		{
			m_sending_request = true;
			m_group_creation_callback = group_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_CREATION, user, group_name);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void JoinGroup(User user, Group group, BiConsumer<Group, Pair<String[], Message[]>> group_join_callback) {
		if(m_oos != null && !m_sending_request && !m_is_disposing)
		{
			m_sending_request = true;
			m_group_join_callback = group_join_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_JOIN, user, group);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void QuitGroup(User user, Group group, Consumer<Boolean> group_quit_callback) {
		if(m_oos != null && !m_sending_request && !m_is_disposing)
		{
			m_sending_request = true;
			m_group_quit_callback = group_quit_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_QUIT, user, group);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void GetGroups(Consumer<Group[]> group_list_callback) {
		if(m_oos != null && !m_sending_request && !m_is_disposing)
		{
			m_sending_request = true;
			m_group_list_callback = group_list_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_GETTER);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void SendMessage(Message message) {
		if(m_oos != null && !m_is_disposing)
		{
			ClientRequest request = new ClientRequest(ClientRequest.Type.SEND_MESSAGE, message);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	/**
	 * Essaye de créer un nouveau compte avec le nom d'utilisateur donné en paramètre.
	 * La callback spécifiée sera appellée avec null en paramètre si l'utilisateur n'a
	 * pas pu être crée et avec l'objet User correspondant à l'utilisateur si la création a réussie.
	 * @param name Nom du nouvel utilisateur
	 * @param username_callback Callback appelée lors de la réponse du serveur
     */
	public void CreateUserName(String name, Consumer<User> username_callback) {
		if(m_oos != null && !m_sending_request && !m_is_disposing)
		{
			m_sending_request = true;
			m_username_callback = username_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.CREATE_USERNAME, name);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void SubmitCredentials(String username, String password, Consumer<User> login_callback) {
		if(m_oos != null && !m_sending_request && !m_is_disposing)
		{
			m_sending_request = true;
			m_login_callback = login_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.LOGIN, username, password);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void Logout() {
		if(m_oos != null)
			SendRequest(new ClientRequest(ClientRequest.Type.LOGOUT));
	}

	/**
	 * Méthode executée sur le thread de l'objet si la méthode start() est appelée (open() doit être appelé auparavant)
	 * Gère les requettes issue du serveur (et appele les callback correspondates pour notifier le controleur de manière asynchrone)
	 */
	@Override
	public void run() {
		while(m_socket != null && !m_is_disposing)
		{
			try {
				Object obj = m_ois.readObject();
				
				if(obj instanceof ServerRequest)
				{
					ServerRequest request = (ServerRequest)obj;
					switch(request.type) {
						case LOGIN_SUCCESS:
							if(is_valid_data(request.data, m_login_callback, User.class))
								m_login_callback.accept((User)request.data[0]);
							else if (m_login_callback != null)
								m_login_callback.accept(null);
							reset_callbacks();
							break;
						case LOGIN_ERROR:
							if (m_login_callback != null)
								m_login_callback.accept(null);
							reset_callbacks();
							break;
						case GROUP_CREATION_ERROR:
							if (m_group_creation_callback != null)
								m_group_creation_callback.accept(null);
							reset_callbacks();
							break;
						case GROUP_CREATION_SUCCESS:
							if(is_valid_data(request.data, m_group_creation_callback, Group.class))
								m_group_creation_callback.accept((Group)request.data[0]);
							else if (m_group_creation_callback != null)
								m_group_creation_callback.accept(null);
							reset_callbacks();
							break;
						case GROUP_JOIN_SUCCESS:
							if(is_valid_data(request.data, m_group_join_callback, Group.class, String[].class, Message[].class))
								m_group_join_callback.accept((Group)request.data[0], new Pair<>((String[])request.data[1], (Message[])request.data[2]));
							else if (m_group_join_callback != null)
								m_group_join_callback.accept(null, null);
							reset_callbacks();
							break;
						case GROUP_JOIN_ERROR:
							if (m_group_join_callback != null)
								m_group_join_callback.accept(null, null);
							reset_callbacks();
							break;
						case GROUP_EXIT_SUCCESS:
							if (m_group_quit_callback != null)
								m_group_quit_callback.accept(true);
							reset_callbacks();
							break;
						case GROUP_EXIT_ERROR:
							if (m_group_quit_callback != null)
								m_group_quit_callback.accept(false);
							reset_callbacks();
							break;
						case SEND_GROUP_LIST:
							if (m_group_list_callback != null && request.data != null) {
								if(request.data instanceof Group[])
									m_group_list_callback.accept((Group[])request.data);
								else
									m_group_list_callback.accept(null);
							}
							reset_callbacks();
							break;
						case SEND_MESSAGE:
							if(is_valid_data(request.data, m_message_callback, Message.class))
								m_message_callback.accept((Message)request.data[0]);
							else if (m_message_callback != null)
								m_message_callback.accept(null);
							break;
						case CREATE_USERNAME_ERROR:
							if (m_username_callback != null)
								m_username_callback.accept(null);
							reset_callbacks();
							break;
						case CREATE_USERNAME_SUCCESS:
							if(is_valid_data(request.data, m_username_callback, User.class))
								m_username_callback.accept((User)request.data[0]);
							else if (m_username_callback != null)
								m_username_callback.accept(null);
							reset_callbacks();
							break;
						case GROUP_LIST_UPDATED:
							if(is_valid_data(request.data, m_group_list_update_callback, Group.class))
								m_group_list_update_callback.accept((Group)request.data[0]);
							else if (m_group_list_update_callback != null)
								m_group_list_update_callback.accept(null);
							break;
						case GROUP_USER_LIST_UPDATED:
							if(is_valid_data(request.data, m_group_user_list_update_callback, Boolean.class, String.class))
								m_group_user_list_update_callback.accept((Boolean)request.data[0], (String)request.data[1]);
							else if (m_group_user_list_update_callback != null)
								m_group_user_list_update_callback.accept(false, null);
							break;
					}
				}
			} catch(ClassNotFoundException|IOException e) {
				/* TODO: quitter l'application ?*/
				if(m_error_callback != null)
					m_error_callback.accept(e);
				close();
			}
			
			/*TODO: sleep ?*/
		}
	}

	private void SendRequest(ClientRequest request) {
		try {
			m_oos.writeObject(request);
		} catch(IOException e) {
			if(m_error_callback != null)
				m_error_callback.accept(e);
			close();
		}
	}

	private void DisposeConnection() throws IOException {
		if(!m_is_disposing) {
			m_is_disposing = true;
			Logout();
		}
		if(m_socket != null)
			m_socket.close();
		if(m_os != null)
			m_os.close();
		if(m_oos != null)
			m_oos.close();
		if(m_is != null)
			m_is.close();
		if(m_ois != null)
			m_ois.close();
	}

	private void reset_callbacks() {
		m_group_creation_callback = null;
		m_group_join_callback = null;
		m_group_quit_callback = null;
		m_group_list_callback = null;
		m_username_callback = null;
		m_login_callback = null;

		m_sending_request = false;
	}

	private boolean is_valid_data(Object[] data, Object callback, Class<?>... types) {
		if (callback != null) {
			if (data != null && types != null) {
				if (types.length == data.length) {
					for (int idx = 0; idx < types.length; ++idx) {
						Object obj = data[idx];
						if(obj == null)
							return false;
						if (!types[idx].equals(obj.getClass()))
							return false;
					}
					return true;
				}
			}
		}
		return false;
	}

	private Socket m_socket;
	private ObjectInputStream m_ois;
	private ObjectOutputStream m_oos;
	private InputStream m_is;
	private OutputStream m_os;

	private Consumer<Exception> m_error_callback = null;
	private Consumer<Message> m_message_callback = null;
	private BiConsumer<Boolean, String> m_group_user_list_update_callback = null;
	private Consumer<Group> m_group_list_update_callback = null;

	private Consumer<Group> m_group_creation_callback;
	private BiConsumer<Group, Pair<String[], Message[]>> m_group_join_callback;
	private Consumer<Boolean> m_group_quit_callback;
	private Consumer<Group[]> m_group_list_callback;
	private Consumer<User> m_username_callback;
	private Consumer<User> m_login_callback;

	private boolean m_sending_request;
	private boolean m_is_disposing = false;
	private int m_port;
	private String m_host_name;
}
