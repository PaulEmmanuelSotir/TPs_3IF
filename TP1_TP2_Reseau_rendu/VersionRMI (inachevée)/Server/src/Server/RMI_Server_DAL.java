package Server;

import java.util.function.Consumer;

import shared.*;

/**
 * Classe dont les méthodes sont applées à distance par le client.
 * Conserve également une référence vers le DAL du client pour le notifier.
 * NON FINIE
 */
public class RMI_Server_DAL implements IRemoteServerDAL {

	public RMI_Server_DAL(Consumer<Exception> error_callback) {

	}

	@Override
	public void connect(IRemoteClientDAL clientDAL) {
		// TODO: créate clientConnection with this clientDAL
	}

	@Override
	public void CreateGroup(User user, String name) {

	}

	@Override
	public void JoinGroup(User user, Group group) {

	}
	
	@Override
	public void GetGroups() {

	}
	
	@Override
	public void SendMessage(User user, Message message) {

	}
	
	@Override
	public void CreateUserName(String name) {

	}
}
