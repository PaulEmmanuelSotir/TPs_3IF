package shared;
import java.io.Serializable;
import java.util.*;

/**
 * Classe représentant un message ayant une date, un nom d'utilisateur et un contenu (String).
 * La classe est serialisable.
 */
public class Message implements Serializable {
	public String data;
	public String userName;
	public Date timestamp;

	/**
	 * Constructeur créant un Message à partir de son contenus de sa date d'émission et du nom de l'utilisateur l'ayant envoyé
	 * @param message Contenus du message
	 * @param date Date de l'emission d'un message
	 * @param userName Nome de l'utilisateur
	 */
	public Message (String message, Date date, String userName) {
		this.data = message;
		this.timestamp = date;
		this.userName = userName;
	}

	/**
	 * Vérifie l'égalitée entre l'objet donné en paramètre et l'instance courante.
	 * @param other L'objet avec le quel l'instance courante est comparée.
	 * @return      Un booléen indiquant l'égalité
	 */
	@Override
	public boolean equals(Object other) {
		if(other instanceof Message) {
			Message other_message = (Message)other;
			if(other_message.data == null) {
				if (data != null)
					return false;
			}
			else if(!other_message.data.equals(data))
				return false;

			if(other_message.userName == null) {
				if (userName != null)
					return false;
			}
			else if(!other_message.userName.equals(userName))
				return false;

			if(other_message.timestamp == null) {
				if (timestamp != null)
					return false;
			}
			else if(!other_message.timestamp.equals(timestamp))
				return false;

			return true;
		}
		return false;
	}

	/**
	 * Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	 */
	private static final long serialVersionUID = -39456554774699643L;
}
