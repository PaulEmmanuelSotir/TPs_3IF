package SocketServer;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.UUID;

import shared.*;

public class Server {
	
	public static void main(String[] args) {
		// TODO: ...	AcceptConnection(1001)...	
	}
	
	public void AcceptConnection(int port)
	{
		m_server_socket = null;
		
		try {
			m_server_socket = new ServerSocket(port);
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
	
	public Group CreateGroup(User creator, String name)
	{
		Group new_group = new Group(new Date(), name);
		if(m_groups.containsKey(new_group))
			return null;
		else
		{
			List<User> users = new ArrayList<User>();
			users.add(creator);
			m_groups.put(new_group, users);
			return new_group;
		}
	}
	
	public void SendMessageToGroup(User user, Group group, Message message){
		ServerRequest request = new ServerRequest(ServerRequest.Type.SEND_MESSAGE, message);
		List<User> group_users = m_groups.get(group);
		
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
	HashMap<Group, List<User>> m_groups;
	
	ServerSocket m_server_socket;
}
