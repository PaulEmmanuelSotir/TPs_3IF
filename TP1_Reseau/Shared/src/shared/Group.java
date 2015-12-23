package shared;

import java.io.Serializable;
import java.util.*;

public class Group implements Serializable {
	public Group(Date creation, String groupName)
	{
		this.creation = creation;
		this.groupName = groupName;
	}
	
	public int hashCode() {
		return groupName.hashCode();
	}
	
	public boolean equals(Group other) {
		return other.groupName == groupName;
	}
	
	public final Date creation;
	public final String groupName;

	// Numéro identifiant la classe lors de la serialization (utilisé pour verifier la présence de la classe lors de la déserialization)
	private static final long serialVersionUID = 4964625258033421772L;
}
