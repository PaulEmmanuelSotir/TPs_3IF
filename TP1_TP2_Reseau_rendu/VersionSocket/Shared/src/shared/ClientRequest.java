package shared;

import java.io.Serializable;

/**
 * Classe représentant une requette du client vers le serveur.
 * Cette classe est utilisée pour définir le protocole basé sur les sockets: la classe contient un attribut type indiquant
 * le type de requette faite et un tableau d'objets représentant les données associées à la requette (devant être serialisables).
 */
public class ClientRequest implements Serializable {
	/**
	 * Enumération des types de requettes client
	 */
	public enum Type { GROUP_CREATION, GROUP_JOIN, GROUP_GETTER, SEND_MESSAGE, CREATE_USERNAME, GROUP_QUIT, LOGIN, LOGOUT };

	/**
	 * Constructeur initialisant la requette avec son type et les données qu'elle contient
	 * @param request_type Le type de la requette client
	 * @param values Les objets associés à la requette client
	 */
	public ClientRequest(Type request_type, Object... values) {
		type = request_type;
		data = values;
	}

	/**
	 * Constructeur initialisant la requette avec son type et sans données associées
	 * @param request_type Le type de la requette client
	 */
	public ClientRequest(Type request_type) {
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

	/**
	 * Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	 */
	private static final long serialVersionUID = 4776000025458443341L;
}
