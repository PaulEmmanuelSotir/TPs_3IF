package metier.modele;

import java.io.Serializable;
import java.util.Objects;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Produit implements Serializable {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String denomination;
    private String description;
    private Float prix;
    private Float poids;

    public Produit() {
    }

    public Produit(String denomination, String description, Float prix, Float poids) {
        this.denomination = denomination;
        this.description = description;
        this.prix = prix;
        this.poids = poids;
    }

    public Long getId() {
        return id;
    }

    public String getDenomination() {
        return denomination;
    }

    public String getDescription() {
        return description;
    }

    public Float getPoids() {
        return poids;
    }

    public Float getPrix() {
        return prix;
    }

    public void setPrix(Float prix) {
        this.prix = prix;
    }

    public void setDenomination(String denomination) {
        this.denomination = denomination;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setPoids(Float poids) {
        this.poids = poids;
    }

    @Override
    public String toString() {
        return "Produit{" + "id=" + id + ", denomination=" + denomination + ", description=" + description + ", prix=" + prix + ", poids=" + poids + '}';
    } 

    @Override
    public int hashCode() {
        int hash = 5;
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Produit other = (Produit) obj;
        if (!Objects.equals(this.id, other.id)) {
            return false;
        }
        return true;
    }  
}
