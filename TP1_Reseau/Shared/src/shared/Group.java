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

	// Num�ro identifiant la classe lors de la serialization (utilis� pour verifier la pr�sence de la classe lors de la d�serialization)
	private static final long serialVersionUID = 4964625258033421772L;
}
