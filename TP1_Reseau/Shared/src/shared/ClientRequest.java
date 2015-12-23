package shared;

import java.io.Serializable;

public class ClientRequest implements Serializable {	
	public enum Type { GROUP_CREATION, GROUP_JOIN, GROUP_GETTER, SEND_MESSAGE, CREATE_USERNAME };

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
	
	// Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	private static final long serialVersionUID = 4776000025458443341L;
}
