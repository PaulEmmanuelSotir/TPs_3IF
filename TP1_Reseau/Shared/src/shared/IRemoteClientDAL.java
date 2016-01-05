package shared;

import java.rmi.Remote;
import java.rmi.RemoteException;
		
public interface IRemoteClientDAL extends Remote {
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
