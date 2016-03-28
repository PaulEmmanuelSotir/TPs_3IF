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
    private Activity activity;
    private List<Member> members;
    private Location location;
    private boolean complet;

    public Event() { }

    public Event(Date date, Activity activity, Member member) {
        this.activity = activity;
        this.date = date;
        this.members.set(0, member);
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

    public Activity getActivity() {
        return activity;
    }

    public void setActivity(Activity activity) {
        this.activity = activity;
    }

    public List<Member> getMembers() {
        return members;
    }

    public void setMembers(List<Member> members) {
        this.members = members;
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location location) {
        this.location = location;
    }

    public boolean getComplet() {
        return this.complet;
    }

    public void setComplet() {
        this.complet = true;
    }

    public List<Member> getAdherentsEquipe1() {
        if (activity.isByTeam()) {
            List<Member> equipe_1 = null;
            for (int i = 0; i < this.members.size(); i += 2) {
                equipe_1.add(members.get(i));
            }
            return equipe_1;
        }
        return null;
    }

    public List<Member> getAdherentsEquipe2() {
        if (activity.isByTeam()) {
            List<Member> equipe_2 = null;
            for (int i = 1; i < this.members.size(); i += 2) {
                equipe_2.add(members.get(i));
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
