package shared;

import java.io.Serializable;
import java.util.UUID;

public class User implements Serializable {
	
	public User(UUID id, String name) {
		Id = id;
		Name = name;
	}
	
	public int hashCode() {
		return Id.hashCode();
	}
	
	public boolean equals(User other) {
		return other.Id == Id;
	}

	public final UUID Id;
	public String Name;
	
	// Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	private static final long serialVersionUID = 4900438272231148693L;
}
