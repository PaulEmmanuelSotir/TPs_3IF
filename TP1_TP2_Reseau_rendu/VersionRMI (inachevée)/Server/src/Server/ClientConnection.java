package Server;

import java.util.UUID;

import shared.*;

/**
 * NON FINIE
 * Conserve une référence vers le DAL du client pour le notifier.
 * Chaque appelle RMI se fait dans son propre thread. (wrapper de RMI_server_DAL pour chaque connection)
 */
public class ClientConnection {
	ClientConnection(IRemoteClientDAL client_dal, UUID temporaryId, Server server) {
		m_server = server;
		m_client_dal = client_dal;
		m_user_id = temporaryId;
	}

	public void close() {

	}

	public void open() {

	}

	UUID m_user_id;
	String m_username = null;
	Group m_last_joined_group = null;

	Server m_server;
	IRemoteClientDAL m_client_dal;
}
