package shared;
import java.io.Serializable;
import java.util.*;

public class Message implements Serializable {
	public String data;
	public String userName;
	public Date timestamp;
	
	public Message (String message, Date date, String userName) {
		this.data = message;
		this.timestamp = date;
		this.userName = userName;
	}

	//TODO: override equals...

	// Num�ro identifiant la classe lors de la serialization (utilis� pour verifier la pr�sence de la classe lors de la d�serialization)
	private static final long serialVersionUID = -39456554774699643L;
}
