package TP1_SI.metier.model;

import java.io.Serializable;
import javax.persistence.Id;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;

/**
 * @author B3330
 */
@Entity
public class Activity implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
    private String name;
    private Boolean byTeam;
    private Integer nbParticipants;

    public Activity() { }

    public Activity(String name, Boolean byTeam, Integer nbParticipants) {
        this.name = name;
        this.byTeam = byTeam;
        this.nbParticipants = nbParticipants;
    }

    public Integer getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public Boolean isByTeam() {
        return byTeam;
    }

    public Integer getNbParticipants() {
        return nbParticipants;
    }

    public void setName(String denomination) {
        this.name = denomination;
    }

    public void setByTeam(Boolean parEquipe) {
        this.byTeam = parEquipe;
    }

    public void setNbParticipants(Integer nbParticipants) {
        this.nbParticipants = nbParticipants;
    }

    @Override
    public int hashCode() {
        return (id != null ? id.hashCode() : 0);
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof Activity))
            return false;

        Activity other = (Activity) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id)))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "Activity{" + "id=" + id + ", denomination=" + name + ", byTeam=" + byTeam + ", nbParticipants=" + nbParticipants + '}';
    }
}
