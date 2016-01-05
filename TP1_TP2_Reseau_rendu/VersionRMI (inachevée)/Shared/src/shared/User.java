package shared;

import java.io.Serializable;
import java.util.UUID;

/**
 * Classe représentant un utilisateur ayant un nom et un Id (mots de passe).
 * La classe est serialisable et peut gènerer un hash.
 */
public class User implements Serializable {

	/**
	 * Constructeur créant un User à partir de son nom et de son Id (mots de passe).
	 * @param id Mots de passe de l'utilisateur
	 * @param name Nome de l'utilisateur
	 */
	public User(UUID id, String name) {
		Id = id;
		Name = name;
	}

	/**
	 * Génère un hash pour un instance de la classe User.
	 * @return      Un int pouvant être utilisé comme hash.
	 */
	@Override
	public int hashCode() {
		return Id.hashCode();
	}

	/**
	 * Vérifie l'égalitée entre l'objet donné en paramètre et l'instance courante.
	 * @param other L'objet avec le quel l'instance courante est comparée.
	 * @return      Un booléen indiquant l'égalité
	 */
	@Override
	public boolean equals(Object other) {
		if(other instanceof User)
			return ((User)other).Id.equals(Id);
		return false;
	}

	public final UUID Id;
	public String Name;

	/**
	 * Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	 */
	private static final long serialVersionUID = 4900438272231148693L;
}
