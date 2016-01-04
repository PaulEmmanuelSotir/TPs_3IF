package shared;

import java.io.Serializable;

public class ClientRequest implements Serializable {	
	public enum Type { GROUP_CREATION, GROUP_JOIN, GROUP_GETTER, SEND_MESSAGE, CREATE_USERNAME, GROUP_QUIT, LOGIN, LOGOUT };

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

	@Override
	public boolean equals(Object other) {
		if(other instanceof  ServerRequest) {
			ClientRequest request = (ClientRequest)other;
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
	
	// Num�ro identifiant la classe lors de la serialization (utilis� pour verifier la pr�sence de la classe lors de la d�serialization)
	private static final long serialVersionUID = 4776000025458443341L;
}
