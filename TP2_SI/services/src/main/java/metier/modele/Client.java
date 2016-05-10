/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.modele;

import com.google.maps.GeoApiContext;
import com.google.maps.GeocodingApi;
import com.google.maps.model.GeocodingResult;
import java.io.Serializable;
import javax.persistence.Id;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Column;
import com.google.maps.model.LatLng;

/**
 *
 * @author qvecchio
 */
@Entity
public class Client implements Serializable{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    @Column(unique=true)
    private String pseudo;
    private String password;
    private String nom;
    private String prenom;
    private String mail;
    private String adresse;
    private String telephone;
    private Double longitude;
    private Double latitude;

    public Client() {
    }

    public Client(String pseudo, String password, String nom, String prenom, String adresse, String mail, String telephone) {
        this.pseudo = pseudo;
        this.password = password;
        this.nom = nom;
        this.prenom = prenom;
        this.mail = mail;
        this.setAdresse(adresse);
        this.telephone = telephone;
    }

    public Long getId() {
        return id;
    }

    public String getPseudo() {
        return pseudo;
    }

    public String getPassword() {
        return password;
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

    public String getAdresse() {
        return adresse;
    }

    public Double getLongitude() {
        return longitude;
    }

    public Double getLatitude() {
        return latitude;
    }

    public String getTelephone() {
        return telephone;
    }

    public void setPseudo(String pseudo) {
        this.pseudo = pseudo;
    }

    public void setPassword(String password) {
        this.password = password;
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

    public void setAdresse(String adresse) {
        this.adresse = adresse;
        GeoApiContext monGeoApi = new GeoApiContext().setApiKey("AIzaSyDcVVJjfmxsNdbdUYeg9MjQoJJ6THPuap4");
        try {
            GeocodingResult[] results = GeocodingApi.geocode(monGeoApi, adresse).await();
            this.latitude = results[0].geometry.location.lat;
            this.longitude = results[0].geometry.location.lng;
        } catch(Exception e) {
            System.out.println("Erreur : " + e.getMessage());
            this.latitude = 0.0;
            this.longitude = 0.0;
        }
    }

    public void setCoordonnees(LatLng latLng) {
        this.longitude = latLng.lng;
        this.latitude = latLng.lat;
    }

    public void setTelephone(String telephone) {
        this.telephone = telephone;
    }

    @Override
    public String toString() {
        return "Client{" + "id=" + id + ", pseudo=" + pseudo + ", nom=" + nom + ", prenom=" + prenom + ", mail=" + mail + ", adresse=" + adresse + ", telephone=" + telephone + ", longitude=" + longitude + ", latitude=" + latitude + '}';
    }
}
