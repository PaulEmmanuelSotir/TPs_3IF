/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.modele;
import java.io.Serializable;
import javax.persistence.Id;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Inheritance;
import javax.persistence.InheritanceType;
/**
 *
 * @author qvecchio
 */

    @Entity
    @Inheritance (strategy = InheritanceType.JOINED)
public abstract class Livreur implements Serializable{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private Double longitude;
    private Double latitude;
    private boolean IsFree;
    private double poidMax; 
    private String mail; 

    public Livreur() {
    }
    
    public Livreur(Double longitude, Double latitude, boolean IsFree, double poidMax, String mail) {
        this.longitude = longitude;
        this.latitude = latitude;
        this.IsFree = IsFree;
        this.poidMax = poidMax;
        this.mail = mail;
    }

    public Long getId() {
        return id;
    }
    
    public Double getLongitude() {
        return longitude;
    }

    public void setLongitude(Double longitude) {
        this.longitude = longitude;
    }

    public Double getLatitude() {
        return latitude;
    }

    public void setLatitude(Double latitude) {
        this.latitude = latitude;
    }

    public boolean getIsFree() {
        return IsFree;
    }

    public void setIsFree(boolean IsFree) {
        this.IsFree = IsFree;
    }

    public double getPoidMax() {
        return poidMax;
    }

    public void setPoidMax(int poidMax) {
        this.poidMax = poidMax;
    }

    public String getMail() {
        return mail;
    }

    public void setMail(String mail) {
        this.mail = mail;
    }
    
    @Override
    public String toString() {
        return "Livreur{" + "longitude=" + longitude + ", latitude=" + latitude + ", IsFree=" + IsFree + ", poidMax=" + poidMax + '}';
    } 
}
