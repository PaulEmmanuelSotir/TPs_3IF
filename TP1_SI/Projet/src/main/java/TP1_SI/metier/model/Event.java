package TP1_SI.metier.model;

import java.sql.Date;
import java.util.List;
import java.io.Serializable;
import javax.persistence.Id;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;

/**
 * @author B3330
 */
@Entity
public class Event implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private Date date;
    private Activite activite;
    private List<Adherent> adherents;
    private Lieu lieu;
    private boolean complet;

    public Event() {

    }

    public Event(Date date, Activite activite, Adherent adherent) {
        this.activite = activite;
        this.date = date;
        this.adherents.set(0, adherent);
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public Activite getActivite() {
        return activite;
    }

    public void setActivite(Activite activite) {
        this.activite = activite;
    }

    public List<Adherent> getAdherents() {
        return adherents;
    }

    public void setAdherents(List<Adherent> adherents) {
        this.adherents = adherents;
    }

    public Lieu getLieu() {
        return lieu;
    }

    public void setLieu(Lieu lieu) {
        this.lieu = lieu;
    }

    public boolean getComplet() {
        return this.complet;
    }

    public void setComplet() {
        this.complet = true;
    }

    public List<Adherent> getAdherentsEquipe1() {
        if (activite.isParEquipe()) {
            List<Adherent> equipe_1 = null;
            for (int i = 0; i < this.adherents.size(); i += 2) {
                equipe_1.add(adherents.get(i));
            }
            return equipe_1;
        }
        return null;
    }

    public List<Adherent> getAdherentsEquipe2() {
        if (activite.isParEquipe()) {
            List<Adherent> equipe_2 = null;
            for (int i = 1; i < this.adherents.size(); i += 2) {
                equipe_2.add(adherents.get(i));
            }
            return equipe_2;
        }
        return null;
    }

    @Override
    public int hashCode() {
        return (id != null ? id.hashCode() : 0);
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Event)) {
            return false;
        }
        Event other = (Event) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "Event[ id=" + id + " ]";
    }

}
