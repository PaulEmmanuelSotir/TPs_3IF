/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.modele;

import java.io.Serializable;
import java.util.Date;
import java.util.List;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToMany;
import javax.persistence.OneToOne;
import javax.persistence.Temporal;
import javax.persistence.Version;

/**
 *
 * @author qvecchio
 */
@Entity
public class Commande implements Serializable{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    @Temporal(javax.persistence.TemporalType.TIMESTAMP)
    private Date dateDebut;
    @Temporal(javax.persistence.TemporalType.TIMESTAMP)
    private Date dateFin;
    @ManyToMany
    private List<ProduitCommande> contenues;
    @OneToOne
    private Client client;
    @OneToOne
    private Restaurant restaurant;
    @OneToOne
    private Livreur livreur;
    
    public Commande() {
    }

    public Commande(Client client, Restaurant restaurant, Livreur livreur, Date dateDebut, Date dateFin, List<ProduitCommande> contenues) {
        this.client = client;
        this.restaurant = restaurant;
        this.livreur = livreur;
        this.dateDebut = dateDebut;
        this.dateFin = dateFin;
        this.contenues = contenues;
    }
    
    public Commande(Client client, Restaurant restaurant, List<ProduitCommande> contenues) {
        this.client = client;
        this.restaurant = restaurant;
        this.livreur = null;
        this.dateDebut = null;
        this.dateFin = null;
        this.contenues = contenues;
    }

    public Long getId() {
        return id;
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public Restaurant getRestaurant() {
        return restaurant;
    }

    public void setRestaurant(Restaurant restaurant) {
        this.restaurant = restaurant;
    }

    public Livreur getLivreur() {
        return livreur;
    }

    public void setLivreur(Livreur livreur) {
        this.livreur = livreur;
    }

    public Date getDateDebut() {
        return dateDebut;
    }

    public void setDateDebut(Date dateDebut) {
        this.dateDebut = dateDebut;
    }

    public Date getDateFin() {
        return dateFin;
    }

    public void setDateFin(Date dateFin) {
        this.dateFin = dateFin;
    }

    public List<ProduitCommande> getContenues() {
        return contenues;
    }

    public void setContenues(List<ProduitCommande> contenues) {
        this.contenues = contenues;
    }

    @Override
    public String toString() {
        if(contenues.isEmpty()) {
            return "Commande vide";
        } else {
            String str = "Commande " + id + "\n";
            str += "Livré par livreur n°" + livreur.getId() + "\n";
            Float poidT = new Float(0); 
            Float prixT = new Float(0);
            str += "Restaurant " + restaurant.getDenomination() + "\n";
            str += restaurant.getAdresse() + "\n\n";//Adresse 
            str += "A livrer chez " + client.getNom() + " " + client.getPrenom() + "\n" + client.getMail() + "\n";
            str += "Contenues de la commande : \n";
            for(ProduitCommande p : contenues) {
                str += "\t" + p.getProduit().getDenomination() + " : " + p.getQuantite() + "\n";
                poidT += p.getProduit().getPoids();
                prixT += p.getProduit().getPrix();
            }
            str += "\n\n";
            str += "Prix totale de la commande : " + prixT + "€\n";
            str += "Poids totale de la commande : " + poidT + "g\n";
            return str;
        }
    }
}
