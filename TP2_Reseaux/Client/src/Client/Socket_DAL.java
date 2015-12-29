package Client;

import java.util.function.Consumer;
import java.io.*;
import java.net.*;

import shared.*;

public class Socket_DAL {
	public Socket_DAL(Consumer<Exception> connection_error_callback, Consumer<Message> message_callback) {
		m_message_callback = message_callback;
		m_error_callback = connection_error_callback;
		m_sending_request = false;
	}

	public void Connect(String host_name, int port) {
		m_socket = null;
		m_os = null;
		m_oos = null;
		m_is = null;
		m_ois = null;
		reset_callbacks();
		
		try {
			m_socket = new Socket (host_name, port);
			m_os = m_socket.getOutputStream();
			m_oos = new ObjectOutputStream(m_os);
			m_is = m_socket.getInputStream();
			m_ois = new ObjectInputStream(m_is);
		} catch (IOException e) {
			m_error_callback.accept(e);
			Disconnect();
        }
	}
	
	public void Disconnect() {
		try
		{
			DisposeConnection();
		} catch (IOException e) {
			//m_error_callback.accept(e);
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

	public void CreateGroup(User user, String group_name, Consumer<Group> group_callback) {
		if(m_oos != null && !m_sending_request)
		{
			m_sending_request = true;
			m_group_creation_callback = group_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_CREATION, user, group_name);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void JoinGroup(User user, Group group, Consumer<Group> group_join_callback) {
		if(m_oos != null && !m_sending_request)
		{
			m_sending_request = true;
			m_group_join_callback = group_join_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_JOIN, user, group);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void QuitGroup(User user, Group group, Consumer<Boolean> group_quit_callback) {
		if(m_oos != null && !m_sending_request)
		{
			m_sending_request = true;
			m_group_quit_callback = group_quit_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_QUIT, user, group);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void GetGroups(Consumer<Group[]> group_list_callback) {
		if(m_oos != null && !m_sending_request)
		{
			m_sending_request = true;
			m_group_list_callback = group_list_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_JOIN);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void SendMessage(Message message) {
		if(m_oos != null)
		{
			ClientRequest request = new ClientRequest(ClientRequest.Type.SEND_MESSAGE, message);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void CreateUserName(String name, Consumer<User> username_callback) {
		if(m_oos != null && !m_sending_request)
		{
			m_sending_request = true;
			m_username_callback = username_callback;
			ClientRequest request = new ClientRequest(ClientRequest.Type.CREATE_USERNAME, name);
			SendRequest(request);
		}
		//TODO: else m_error_callback ??
	}

	public void RequestReceivingTask() {
		while(m_socket != null)
		{
			try {
				Object obj = m_ois.readObject();
				
				if(obj instanceof ServerRequest)
				{
					ServerRequest request = (ServerRequest)obj;
					switch(request.type) {
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
							if(is_valid_data(request.data, m_group_join_callback, Group.class))
										m_group_join_callback.accept((Group)request.data[0]);
							else if (m_group_join_callback != null)
								m_group_join_callback.accept(null);
							reset_callbacks();
							break;
						case GROUP_JOIN_ERROR:
							if (m_group_join_callback != null)
								m_group_join_callback.accept(null);
							reset_callbacks();
							break;
						case GROUP_EXIT_SUCCESS:
							if (m_group_quit_callback != null)
								m_group_quit_callback.accept(true);
						case GROUP_EXIT_ERROR:
							if (m_group_quit_callback != null)
								m_group_quit_callback.accept(false);
						case SEND_GROUP_LIST:
							if(is_valid_data(request.data, m_group_list_callback, Group[].class))
								m_group_list_callback.accept((Group[])request.data[0]);
							else if (m_group_list_callback != null)
								m_group_list_callback.accept(null);
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
					}
				}
			} catch(ClassNotFoundException|IOException e) {
				/* TODO: quitter l'application ?*/
				if(m_error_callback != null)
					m_error_callback.accept(e);
				Disconnect();
			}
			
			/*TODO: sleep ou trouver un moyen de faire de facon evenmentielle*/
		}
	}

	private void SendRequest(ClientRequest request) {
		try {
			m_oos.writeObject(request);
		} catch(IOException e) {
			if(m_error_callback != null)
				m_error_callback.accept(e);
			Disconnect();
		}
	}

	private void DisposeConnection() throws IOException {
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
		m_group_list_callback = null;
		m_username_callback = null;
		m_sending_request = false;
	}

	private boolean is_valid_data(Object[] data, Consumer<?> callback, Class<?>... types) {
		if (callback != null) {
			if (data != null && types != null) {
				if (types.length == data.length) {
					for (int idx = 0; idx < types.length; ++idx) {
						if (types[idx] != data.getClass())
							return false;
					}
					return true;
				}
			}
		}
		return false;
	}

	Socket m_socket;
	ObjectInputStream m_ois;
	ObjectOutputStream m_oos;
	InputStream m_is;
	OutputStream m_os;

	Consumer<Exception> m_error_callback;
	Consumer<Message> m_message_callback;

	// TODO: on suppose qu'il n'y aura q'une seule requette de faite à la fois... Comment faire sinon?
	Consumer<Group> m_group_creation_callback;
	Consumer<Group> m_group_join_callback;
	Consumer<Boolean> m_group_quit_callback;
	Consumer<Group[]> m_group_list_callback;
	Consumer<User> m_username_callback;

	boolean m_sending_request;
}
