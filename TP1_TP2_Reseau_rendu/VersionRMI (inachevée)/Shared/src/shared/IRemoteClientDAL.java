package shared;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * Interface utilisée pour notifier le client depuis le serveur (par référence et non RMI)
 */
public interface IRemoteClientDAL {
	void OnUserLoggedIn(User user) throws RemoteException;
	void OnGroupCreated(Group group) throws RemoteException;
	void OnGroupJoined(Group group, String[] usernames, Message[] history) throws RemoteException;
	void OnGroupExit(Boolean success) throws RemoteException;
	void OnSendGroupList(Group[] groups) throws RemoteException;
	void OnSendMessage(Message message) throws RemoteException;
	void OnUserCreated(User user) throws RemoteException;
	void OnGroupListUpdated(Group new_group) throws RemoteException;
	void OnGroupUserListUpdated(Boolean is_joining, String new_username) throws RemoteException;
}
