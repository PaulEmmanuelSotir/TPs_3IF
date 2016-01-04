package Server;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.List;
import java.util.UUID;

import shared.*;

public class ClientConnection extends Thread {
	ClientConnection(Socket socket, UUID temporaryId, Server server)
	{
		m_server = server;
		m_socket = socket;
		m_user_id = temporaryId;
	}

	public void close()
	{
		try
		{
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
		} catch(IOException e) { }
		finally 
		{
			m_socket = null;
			m_os = null;
			m_oos = null;
			m_os = null;
			m_oos = null;
		}
	}
	
	public void SendRequest(ServerRequest request)
	{
		if(m_oos != null) {
			try {
				m_oos.writeObject(request);
			} catch (IOException e) {
			/* TODO: remove user from server? */
				close();
			}
		}
	}

	public void open() throws IOException
	{
		if(m_socket != null)
		{
			m_is = m_socket.getInputStream();
			m_ois = new ObjectInputStream(m_is);
			m_os = m_socket.getOutputStream();
			m_oos = new ObjectOutputStream(m_os);
		}
	}

	@Override
	public void run()
	{
		while(m_socket != null)
		{
			Object obj;
			
			try {
				obj = m_ois.readObject();
			} catch (ClassNotFoundException|IOException e) {
				/* TODO: remove user from server */
				close();
				return;
			}
			
			if(obj instanceof ClientRequest)
			{
				try {
					handleIncommingRequest((ClientRequest)obj);
				} catch (IOException e) {
					/*TODO: handle...*/
					close();
				}
				
			}
			else
				close();
			/*TODO: sleep?*/
		}

		m_server.on_user_disconnected(m_user_id, m_username, m_last_joined_group);
	}

	private boolean is_valid_data(Object[] data, Class<?>... types) {
		if(data != null && types != null)
		{
			if(types.length == data.length)
			{
				for(int idx = 0; idx < types.length; ++idx) {
					Object obj = data[idx];
					if(obj == null)
						return false;
					if(!types[idx].equals(obj.getClass()))
						return false;
				}
				return true;
			}
		}
		return false;
	}
	
	private void handleIncommingRequest(ClientRequest request) throws IOException {
		switch(request.type)
		{
		case LOGIN:
			if(is_valid_data(request.data, String.class, String.class)) {
				String username = (String)request.data[0];
				String password = (String)request.data[1];
				if(password != null && username != null) {
					if(!password.equals("") && !username.equals("")) {
						try {
							UUID pass = UUID.fromString(password);
							if(m_server.Login(username, pass, m_user_id)) {
								m_user_id = pass; // Update connection's id to be user password
								m_username = username;
								m_oos.writeObject(new ServerRequest(ServerRequest.Type.LOGIN_SUCCESS, new User(pass, username)));
								break;
							}
						} catch (IllegalArgumentException e) { }
					}
				}
			}
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.LOGIN_ERROR));
			break;
		case GROUP_CREATION:
			if(is_valid_data(request.data, User.class, String.class)) {
				User user = (User)request.data[0];
				if(user.Id != null && m_user_id != null && user.Name != null && m_username != null) {
					if(user.Id.equals(m_user_id) && user.Name.equals(m_username)) {
						Group new_group = m_server.CreateGroup(user, (String) request.data[1]);
						if (new_group != null) {
							m_last_joined_group = new_group;
							m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_CREATION_SUCCESS, new_group));
							break;
						}
					}
				}
			}
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_CREATION_ERROR));
			break;
		case GROUP_QUIT:
			if(is_valid_data(request.data, User.class, Group.class) && m_last_joined_group != null) {
				User user = (User)request.data[0];
				Group group = (Group)request.data[1];
				if(user.Id != null && m_user_id != null && user.Name != null && m_username != null) {
					if(user.Id.equals(m_user_id) && user.Name.equals(m_username) && m_last_joined_group.equals(group)) {
						if (m_server.QuitGroup(user, group)) {
							m_last_joined_group = null;
							m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_EXIT_SUCCESS));
							break;
						}
					}
				}
			}
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_EXIT_ERROR));
			break;
		case GROUP_JOIN:
			if(is_valid_data(request.data, User.class, Group.class) && m_last_joined_group == null)
			{
				User user = (User)request.data[0];
				if(user.Id != null && m_user_id != null && user.Name != null && m_username != null) {
					if(user.Id.equals(m_user_id) &&  user.Name.equals(m_username)) {
						Group joined_group = (Group)request.data[1];
						Pair<String[], List<Message>> group_data = m_server.JoinGroup(user, joined_group);
						if(group_data != null && joined_group != null) {
							m_last_joined_group = joined_group;
							m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_JOIN_SUCCESS, joined_group, group_data.first, group_data.second.toArray(new Message[group_data.second.size()])));
							break;
						}
					}
				}
			}
			m_last_joined_group = null;
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_JOIN_ERROR));
			break;
		case GROUP_GETTER:
			// TODO: savoir si ça donne le tableau sous la forme d'un seul argument de la fonction variadic (constructeur de ServerRequest)
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.SEND_GROUP_LIST, m_server.GetGroups()));
			break;
		case SEND_MESSAGE:
			if(is_valid_data(request.data, Message.class)) {
				Message message = (Message)request.data[0];
				if(message.userName != null && m_username != null && m_last_joined_group != null) {
					if(message.userName.equals(m_username))
						m_server.SendMessageToGroup(new User(m_user_id, m_username), m_last_joined_group, message);
				}
			}
			break;
		case CREATE_USERNAME:
			if(is_valid_data(request.data, String.class) && m_username == null)
			{
				String username = (String)request.data[0];
				if(m_server.CreateUser(username, m_user_id)) {
					m_username = username;
					m_oos.writeObject(new ServerRequest(ServerRequest.Type.CREATE_USERNAME_SUCCESS, new User(m_user_id, m_username)));
					break;
				}
			}
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.CREATE_USERNAME_ERROR));
			break;
		case LOGOUT:
			close();
			break;
		}
	}

	UUID m_user_id;
	String m_username = null;
	Group m_last_joined_group = null;

	Server m_server;
	Socket m_socket;
	ObjectInputStream m_ois = null;
	ObjectOutputStream m_oos = null;
	InputStream m_is = null;
	OutputStream m_os = null;
}
