package Server;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.UUID;

import shared.*;

public class ClientConnection {
	ClientConnection(Socket socket, UUID client_id, Server server)
	{
		m_server = server;
		m_socket = socket;
		m_user_id = client_id;
		m_username = null;
		m_last_joined_group = null;

		if(m_socket != null)
		{
			try {
				m_is = m_socket.getInputStream();
				m_ois = new ObjectInputStream(m_is);
				m_os = m_socket.getOutputStream();
				m_oos = new ObjectOutputStream(m_os);
				
			} catch (IOException e) {
				Disconnect();
	        }
		}
	}

	public void Disconnect()
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
		try {
			m_oos.writeObject(request);
		} catch (IOException e) {
			/* TODO: remove user from server */
			Disconnect();
		}
	}
	
	public void RequestReceivingTask()
	{
		while(m_socket != null)
		{
			Object obj;
			
			try {
				obj = m_ois.readObject();
			} catch (ClassNotFoundException|IOException e) {
				/* TODO: remove user from server */
				Disconnect();
				return;
			}
			
			if(obj instanceof ClientRequest)
			{
				try {
					handleIncommingRequest((ClientRequest)obj);
				} catch (IOException e) {
					/*TODO: handle...*/
					Disconnect();
				}
				
			}
			else
				Disconnect();
			/*TODO: sleep ou gerer de maniere evenementiel*/
		}

		m_server.on_user_disconnected(m_user_id, m_username, m_last_joined_group);
	}

	private boolean is_valid_data(Object[] data, Class<?>... types) {
		if(data != null && types != null)
		{
			if(types.length == data.length)
			{
				for(int idx = 0; idx < types.length; ++idx)
				{
					if(types[idx] != data.getClass())
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
		case GROUP_CREATION:
			if(is_valid_data(request.data, User.class, String.class)) {
				User user = (User)request.data[0];
				if(user.Id == m_user_id && user.Name == m_username && m_username != null) {
					Group new_group = m_server.CreateGroup(user, (String)request.data[1]);
					if (new_group != null) {
						m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_CREATION_SUCCESS, new_group));
						break;
					}
				}
			}
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_CREATION_ERROR));
			break;
		case GROUP_QUIT:
			if(is_valid_data(request.data, User.class, Group.class) && m_last_joined_group != null) {
				User user = (User)request.data[0];
				Group group = (Group)request.data[1];
				if(user.Id == m_user_id && user.Name == m_username && m_username != null && m_last_joined_group == group) {
					//TODO... + ajouter GROUP_QUIT_SUCCESS et ERROR
					if(m_server.QuitGroup(user, group))
					{
						m_last_joined_group = null;
						m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_EXIT_SUCCESS));
						break;
					}
				}
			}
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_EXIT_ERROR));
			break;
		case GROUP_JOIN:
			if(is_valid_data(request.data, User.class, Group.class) && m_last_joined_group == null)
			{
				User user = (User)request.data[0];
				if(user.Id == m_user_id && user.Name == m_username && m_username != null) {
					Group joined_group = m_server.JoinGroup(user, (Group)request.data[1]);
					if(joined_group != null) {
						m_last_joined_group = joined_group;
						m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_JOIN_SUCCESS, joined_group));
						break;
					}
				}
			}
			m_last_joined_group = null;
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_JOIN_ERROR));
			break;
		case GROUP_GETTER:
			if(is_valid_data(request.data))
				// TODO: savoir si ça donne le tableau sous la forme d'un seul argument de la fonction variadic (constructeur de ServerRequest)
				m_oos.writeObject(new ServerRequest(ServerRequest.Type.SEND_GROUP_LIST, m_server.GetGroups()));
			break;
		case SEND_MESSAGE:
			if(is_valid_data(request.data, User.class, Group.class, Message.class)) {
				User user = (User)request.data[0];
				if(user.Id == m_user_id && user.Name == m_username && m_username != null)
					m_server.SendMessageToGroup(user, (Group)request.data[1], (Message)request.data[2]);
			}
			break;
		case CREATE_USERNAME:
			if(is_valid_data(request.data, String.class) && m_username == null)
			{
				String username = (String)request.data[0];
				if(m_server.CreateUser(username)) {
					m_username = username;
					m_oos.writeObject(new ServerRequest(ServerRequest.Type.CREATE_USERNAME_SUCCESS, new User(m_user_id, username)));
				}
				else
					m_oos.writeObject(new ServerRequest(ServerRequest.Type.CREATE_USERNAME_ERROR));

				/*TODO:... new User(m_user_id, request.data[0])*/
			}
			break;
		}
	}

	UUID m_user_id;
	String m_username;
	Group m_last_joined_group;

	Server m_server;
	Socket m_socket;
	ObjectInputStream m_ois = null;
	ObjectOutputStream m_oos = null;
	InputStream m_is = null;
	OutputStream m_os = null;
}
