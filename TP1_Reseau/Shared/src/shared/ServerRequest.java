package shared;

import java.io.Serializable;

public class ServerRequest implements Serializable {
	public enum Type {
		GROUP_CREATION_ERROR,
		GROUP_CREATION_SUCCESS,
		GROUP_JOIN_ERROR,
		SEND_GROUP_LIST,
		SEND_MESSAGE,
		CREATE_USERNAME_ERROR,
		CREATE_USERNAME_SUCCESS };
		
	public ServerRequest(Type request_type, Object... values)
	{
		type = request_type;
		data = values;
	}
	
	public ServerRequest(Type request_type)
	{
		type = request_type;
		data = null;
	}
	
	public final Type type;
	public final Object[] data;
	
	// Numéro identifiant la classe lors de la serialisation (utilisé pour verifier la présence de la classe lors de la déserialisation)
	private static final long serialVersionUID = 5215608498221700206L;
}
