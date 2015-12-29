package shared;

import java.io.Serializable;

public class ClientRequest implements Serializable {	
	public enum Type { GROUP_CREATION, GROUP_JOIN, GROUP_GETTER, SEND_MESSAGE, CREATE_USERNAME, GROUP_QUIT };

	public ClientRequest(Type request_type, Object... values)
	{
		type = request_type;
		data = values;
	}
	
	public ClientRequest(Type request_type)
	{
		type = request_type;
		data = null;
	}
	
	public final Type type;
	public final Object[] data;
	
	// Num�ro identifiant la classe lors de la serialization (utilis� pour verifier la pr�sence de la classe lors de la d�serialization)
	private static final long serialVersionUID = 4776000025458443341L;
}
