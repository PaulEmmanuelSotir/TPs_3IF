package SocketServer;

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
			} catch (ClassNotFoundException e) {
				/* TODO: remove user from server */
				Disconnect();
				return;
			} catch (IOException e) {
				/* TODO: remove user from server */
				Disconnect();
				return;
			}
			
			if(obj instanceof ClientRequest)
			{
				try {
					handleIncommingRequest((ClientRequest)obj);
				}
				catch (IOException e) {
					/*TODO: handle...*/
				}
				
			}
			/*TODO: sleep ou gerer de manière evenementiel*/
		}
	}
	
	private boolean is_valid_data(Object[] data, Class<?>... types)
	{
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
				Group new_group = m_server.CreateGroup((User)request.data[0], (String)request.data[1]);
				if(new_group != null) {
					m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_CREATION_SUCCESS, new_group));
					break;
				}
			}
			m_oos.writeObject(new ServerRequest(ServerRequest.Type.GROUP_CREATION_ERROR));
			break;
		case GROUP_JOIN:
			if(is_valid_data(request.data, User.class, Group.class))
			{
				/*TODO:...*/
			}
			break;
		case GROUP_GETTER:
			if(is_valid_data(request.data))
			{
				//m_oos.writeObject(new ServerRequest(ServerRequest.Type.SEND_GROUP_LIST, m_server.GetGroups()));
				/*TODO:...*/
			}
			break;
		case SEND_MESSAGE:
			if(is_valid_data(request.data, User.class, Group.class, Message.class))
				m_server.SendMessageToGroup((User)request.data[0], (Group)request.data[1], (Message)request.data[2]);
			break;
		case CREATE_USERNAME:
			if(is_valid_data(request.data, String.class))
			{
				/*TODO:... new User(m_user_id, request.data[0])*/
			}
			break;
		}
	}
	
	UUID m_user_id;
	Server m_server;
	Socket m_socket;
	ObjectInputStream m_ois = null;
	ObjectOutputStream m_oos = null;
	InputStream m_is = null;
	OutputStream m_os = null;
}
