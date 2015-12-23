package shared;

import java.rmi.Remote;

public interface IRemoteChatDAL extends Remote { 
	public void CreateGroup(User user, String name);
	public void JoinGroup(User user, Group group);
	public void GetGroups();
	public void SendMessage(User user, Message message);
	public void CreateUserName(String name);
	/*TOOD: add quitGroup et logout*/
}
