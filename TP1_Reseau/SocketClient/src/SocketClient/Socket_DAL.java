package SocketClient;

import java.util.function.Consumer;
import java.io.*;
import java.net.*;

import shared.*;

public class Socket_DAL extends IChatDAL {

	public Socket_DAL(Consumer<Exception> error_callback) {
		super(error_callback);
	}

	public void Connect(String host_name, int port)
	{
		m_socket = null;
		m_os = null;
		m_oos = null;
		
		try {
			m_socket = new Socket (host_name, port);
			m_os = m_socket.getOutputStream();
			m_oos = new ObjectOutputStream(m_os);
		} catch (IOException e) {
			m_error_callback.accept(e);
			Disconnect();
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
		} catch (IOException e) {
			//m_error_callback.accept(e);
			/* TODO: savoir quoi faire ici */
        } finally {
			m_socket = null;
			m_os = null;
			m_oos = null;
			m_error_callback = null;
		}
	}
	
	public void finalize() throws IOException
	{
		if(m_socket != null)
			m_socket.close();
		if(m_os != null)
			m_os.close();
		if(m_oos != null)
			m_oos.close();
	}

	@Override
	public void CreateGroup(User user, String group_name) {
		
		ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_CREATION, user, group_name);
		if(m_oos != null)
			SendRequest(request);
	}

	@Override
	public void JoinGroup(User user, Group group) {
		ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_JOIN, user, group);
		if(m_oos != null)
			SendRequest(request);
	}

	@Override
	public void GetGroups() {
		ClientRequest request = new ClientRequest(ClientRequest.Type.GROUP_JOIN);
		if(m_oos != null)
			SendRequest(request);
	}

	@Override
	public void SendMessage(User user, Message message){
		ClientRequest request = new ClientRequest(ClientRequest.Type.SEND_MESSAGE, user, message);
		if(m_oos != null)
			SendRequest(request);
	}

	@Override
	public void CreateUserName(String name){
		ClientRequest request = new ClientRequest(ClientRequest.Type.CREATE_USERNAME, name);
		if(m_oos != null)
			SendRequest(request);
	}
	
	public void RequestReceivingTask()
	{
		while(m_socket != null)
		{
			try {
				Object obj = m_ois.readObject();
				
				if(obj instanceof ClientRequest)
				{
					ClientRequest request = (ClientRequest)obj;
					switch(request.type)
					{
					case CREATE_USERNAME:
						/*TODO:...*/
						break;
					case GROUP_CREATION:
						/*TODO:...*/
						break;
					case GROUP_GETTER:
						/*TODO:...*/
						break;
					case GROUP_JOIN:
						/*TODO:...*/
						break;
					case SEND_MESSAGE:
						/*TODO:...*/
						break;
					}
				}
			} catch(ClassNotFoundException e) {
				/* TODO: quitter l'application ?*/
				m_error_callback.accept(e);
				Disconnect();
			} catch(IOException e) {
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
			m_error_callback.accept(e);
			Disconnect();
		}
	}
	
	Socket m_socket;
	ObjectInputStream m_ois;
	ObjectOutputStream m_oos;
	InputStream m_is;
	OutputStream m_os;
}
