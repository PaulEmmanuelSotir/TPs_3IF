package shared;

import java.io.Serializable;
import java.util.UUID;

public class User implements Serializable {
	
	public User(UUID id, String name) {
		Id = id;
		Name = name;
	}

	@Override
	public int hashCode() {
		return Id.hashCode();
	}

	@Override
	public boolean equals(Object other) {
		if(other instanceof User)
			return ((User)other).Id.equals(Id);
		return false;
	}

	public final UUID Id;
	public String Name;
	
	// Num�ro identifiant la classe lors de la serialization (utilis� pour verifier la pr�sence de la classe lors de la d�serialization)
	private static final long serialVersionUID = 4900438272231148693L;
}
