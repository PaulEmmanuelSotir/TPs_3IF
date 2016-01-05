package shared;

import java.io.Serializable;

/**
 * Classe représentant une requette du serveur vers un client.
 * Cette classe est utilisée pour définir le protocole basé sur les sockets: la classe contient un attribut type indiquant
 * le type de requette faite et un tableau d'objets représentant les données associées à la requette (devant être serialisables).
 */
public class ServerRequest implements Serializable {
	/**
	 * Enumération des types de requettes serveur
	 */
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

	/**
	 * Constructeur initialisant la requette avec son type et les données qu'elle contient
	 * @param request_type Le type de la requette serveur
	 * @param values Les objets associés à la requette serveur
	 */
	public ServerRequest(Type request_type, Object... values)
	{
		type = request_type;
		data = values;
	}

	/**
	 * Constructeur initialisant la requette avec son type et sans données associées
	 * @param request_type Le type de la requette serveur
	 */
	public ServerRequest(Type request_type)
	{
		type = request_type;
		data = null;
	}

	/**
	 * Vérifie l'égalitée (basée sur l'égalité du type et des objets contenus) entre l'objet donné en paramètre et l'instance courante.
	 * @param other L'objet avec le quel l'instance courante est comparée.
	 * @return      Un booléen indiquant l'égalité
	 */
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

	/**
	 * Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	 */
	private static final long serialVersionUID = 5215608498221700206L;
}
