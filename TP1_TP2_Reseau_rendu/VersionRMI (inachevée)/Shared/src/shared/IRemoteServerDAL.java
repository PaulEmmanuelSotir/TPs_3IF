package shared;

import java.rmi.Remote;

/**
 * Interface utilisée pour contacter le serveur depuis le client (par RMI)
 */
public interface IRemoteServerDAL extends Remote {
	public void connect(IRemoteClientDAL clientDAL);
	public void CreateGroup(User user, String name);
	public void JoinGroup(User user, Group group);
	public void GetGroups();
	public void SendMessage(User user, Message message);
	public void CreateUserName(String name);
	/*TOOD: add quitGroup et logout*/
}
