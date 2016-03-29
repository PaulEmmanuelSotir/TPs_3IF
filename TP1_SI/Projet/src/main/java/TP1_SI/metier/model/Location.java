package TP1_SI.metier.model;

import com.google.maps.model.LatLng;

import javax.persistence.Id;
import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;

/**
 * Classe représentant un lieux définit par des coordonées, une addresse, un nom et une description.
 * @author B3330
 */
@Entity
public class Location implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String address;
    private String description;
    private String denomination;
    private Double latitude;
    private Double longitude;

    public Location() { }

    public Location(String denomination, String description, String address) {
        this.denomination = denomination;
        this.description = description;
        this.address = address;
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

    public String getAddress() {
        return address;
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

    public void setAddress(String adresse) {
        this.address = adresse;
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
        if (!(object instanceof Location))
            return false;

        Location other = (Location) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id)))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "Location{" + "id=" + id + ", denomination=" + denomination + ", description=" + description + ", address=" + address + ", longitude=" + longitude + ", latitude=" + latitude + '}';
    }
}
