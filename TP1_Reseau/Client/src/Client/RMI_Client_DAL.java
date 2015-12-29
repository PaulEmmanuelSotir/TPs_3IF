package Client;

import java.util.function.Consumer;

import shared.*;

public class RMI_Client_DAL extends IRemoteChatDAL {

	public RMI_DAL(Consumer<Exception> error_callback) {
		super(error_callback);
	}
	
	@Override
	public void CreateGroup(User user, String name) {
		// TODO Auto-generated method stub
	}
	
	@Override
	public void JoinGroup(User user, Group group) {
		// TODO Auto-generated method stub
	}
	
	@Override
	public void GetGroups() {
		// TODO Auto-generated method stub
	}
	
	@Override
	public void SendMessage(User user, Message message) {
		// TODO Auto-generated method stub
	}
	
	@Override
	public void CreateUserName(String name) {
		// TODO Auto-generated method stub
	}
}
