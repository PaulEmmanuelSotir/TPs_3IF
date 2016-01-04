package shared;

import java.io.Serializable;

public class ServerRequest implements Serializable {
	public enum Type {
		LOGIN_SUCCESS,
		LOGIN_ERROR,
		GROUP_CREATION_ERROR,
		GROUP_CREATION_SUCCESS,
		GROUP_JOIN_ERROR,
		GROUP_JOIN_SUCCESS,
		GROUP_EXIT_SUCCESS,
		GROUP_EXIT_ERROR,
		SEND_GROUP_LIST,
		SEND_MESSAGE,
		CREATE_USERNAME_ERROR,
		CREATE_USERNAME_SUCCESS,
		GROUP_LIST_UPDATED,
		GROUP_USER_LIST_UPDATED};

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

	@Override
	public boolean equals(Object other) {
		if(other instanceof  ServerRequest) {
			ServerRequest request = (ServerRequest)other;
			if(type.equals(request.type)) {
				if (data == null && request.data == null)
					return true;
				if (data.length == request.data.length) {
					for (int i = 0; i < data.length; ++i)
						if(data[i] != null) {
							if (!data[i].equals(request.data[i]))
								return false;
						}
						else {
							if(request.data[i] != null)
								return false;
						}
					return true;
				}
			}
		}
		return false;
	}
	
	public final Type type;
	public final Object[] data;
	
	// Num�ro identifiant la classe lors de la serialisation (utilis� pour verifier la pr�sence de la classe lors de la d�serialisation)
	private static final long serialVersionUID = 5215608498221700206L;
}
