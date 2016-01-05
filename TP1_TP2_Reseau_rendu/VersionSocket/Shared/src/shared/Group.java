package shared;

import java.util.*;
import java.io.Serializable;

/**
 * Classe représentant un groupe ou une room ayant un nom et une date de création.
 * Un groupe est une room regroupant des utilisateurs pouvant chatter ensembles.
 * La classe est serialisable et peut gènerer un hash.
 */
public class Group implements Serializable {

	/**
	 * Constructeur créant un Group à partir de son nom et de sa date de création.
	 * @param creation Date de création
	 * @param groupName Nom du groupe
	 */
	public Group(Date creation, String groupName) {
		this.creation = creation;
		this.groupName = groupName;
	}

	/**
	 * Génère un hash pour un instance de la classe Group.
	 * @return      Un int pouvant être utilisé comme hash.
	 */
	@Override
	public int hashCode() {
		return groupName.hashCode();
	}

	/**
	 * Vérifie l'égalitée entre l'objet donné en paramètre et l'instance courante.
	 * @param other L'objet avec le quel l'instance courante est comparée.
	 * @return      Un booléen indiquant l'égalité
	 */
	@Override
	public boolean equals(Object other) {
		if(other instanceof Group)
			return ((Group)other).groupName.equals(groupName);
		return false;
	}
	
	public final Date creation;
	public final String groupName;

	/**
	 * Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	 */
	private static final long serialVersionUID = 4964625258033421772L;
}
