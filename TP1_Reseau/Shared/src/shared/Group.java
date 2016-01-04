package shared;

import java.io.Serializable;
import java.util.*;

public class Group implements Serializable {
	public Group(Date creation, String groupName)
	{
		this.creation = creation;
		this.groupName = groupName;
	}

	@Override
	public int hashCode() {
		return groupName.hashCode();
	}

	@Override
	public boolean equals(Object other) {
		if(other instanceof Group)
			return ((Group)other).groupName.equals(groupName);
		return false;
	}
	
	public final Date creation;
	public final String groupName;

	// Num�ro identifiant la classe lors de la serialization (utilis� pour verifier la pr�sence de la classe lors de la d�serialization)
	private static final long serialVersionUID = 4964625258033421772L;
}
