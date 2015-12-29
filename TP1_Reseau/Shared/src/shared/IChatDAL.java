package shared;

import java.util.Date;
import java.util.function.Consumer;

public abstract class IChatDAL {
	public IChatDAL(Consumer<Exception> error_callback)
	{
		m_error_callback = error_callback;
	}
	
	public abstract void CreateGroup(User user, String name);
	public abstract void JoinGroup(User user, Group group);
	public abstract void GetGroups();
	public abstract void SendMessage(User user, Date timestamp, Message message);
	public abstract void CreateUserName(String name);
	/*TOOD: add quitGroup et logout*/
	
	protected Consumer<Exception> m_error_callback;
}
