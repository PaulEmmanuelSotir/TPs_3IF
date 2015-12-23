package shared;

import java.util.function.Consumer;

public abstract class IChatDAL implements IRemoteChatDAL {
	public IChatDAL(Consumer<Exception> error_callback)
	{
		m_error_callback = error_callback;
	}
	
	protected Consumer<Exception> m_error_callback;
}
