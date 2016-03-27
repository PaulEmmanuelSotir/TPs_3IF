package TP1_SI.metier.model;

import com.google.maps.model.LatLng;

import javax.persistence.Id;
import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;

/**
 * @author B3330
 */
@Entity
public class Lieu implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
    private String denomination;
    private String description;
    private String adresse;
    private Double longitude;
    private Double latitude;

    public Lieu() {
    }

    public Lieu(String denomination, String description, String adresse) {
        this.denomination = denomination;
        this.description = description;
        this.adresse = adresse;
    }


    public Integer getId() {
        return id;
    }

    public String getDenomination() {
        return denomination;
    }


    public String getDescription() {
        return description;
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

    public void setCoordonnees(LatLng latLng) {
        this.longitude = latLng.lng;
        this.latitude = latLng.lat;
    }

    public void setDenomination(String denomination) {
        this.denomination = denomination;
    }


    public void setDescription(String description) {
        this.description = description;
    }

    public void setAdresse(String adresse) {
        this.adresse = adresse;
    }

    public void setLongitude(Double longitude) {
        this.longitude = longitude;
    }

    public void setLatitude(Double latitude) {
        this.latitude = latitude;
    }

    @Override
    public int hashCode() {
        return (id != null ? id.hashCode() : 0);
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof Lieu))
            return false;

        Lieu other = (Lieu) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id)))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "Lieu{" + "id=" + id + ", denomination=" + denomination + ", description=" + description + ", adresse=" + adresse + ", longitude=" + longitude + ", latitude=" + latitude + '}';
    }
}
