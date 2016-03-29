package TP1_SI.metier.model;

import com.google.maps.model.LatLng;

import javax.persistence.Id;
import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;

/**
 * Classe représentant un membre de l'association pouvant rejoindre ou créer des événements
 * @author B3330
 */
@Entity
public class Member implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String address;
    private Double lat;
    private Double lng;
    private String mail;
    private String nom;
    private String prenom;

    public Member() { }

    public Member(String nom, String prenom, String address, String mail, LatLng coordonnees) {
        this.nom = nom;
        this.prenom = prenom;
        this.mail = mail;
        this.address = address;
        this.lat = coordonnees.lat;
        this.lng = coordonnees.lng;
    }

    public Long getId() {
        return id;
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public String getMail() {
        return mail;
    }

    public String getAddress() {
        return address;
    }

    public Double getLatitude() {
        return lat;
    }

    public Double getLongitude() {
        return lng;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }

    public void setAddress(String adresse) {
        this.address = adresse;
    }

    public void setCoordonnees(LatLng latLng) {
        this.lat = latLng.lat;
        this.lng = latLng.lng;
    }

    @Override
    public int hashCode() {
        return (id != null ? id.hashCode() : 0);
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof Member))
            return false;

        Member other = (Member) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id)))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "Member{" + "id=" + id + ", nom=" + nom + ", prenom=" + prenom + ", mail=" + mail + ", adresse=" + address + ", longitude=" + lng + ", latitude=" + lat + '}';
    }
}
