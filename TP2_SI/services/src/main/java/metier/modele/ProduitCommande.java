/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.modele;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

/**
 *
 * @author quentinvecchio
 */

@Entity
public class ProduitCommande implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private Produit produit;
    private Integer quantite;

    public ProduitCommande() {
    }

    public ProduitCommande(Produit produit, Integer quantite) {
        this.produit = produit;
        this.quantite = quantite;
    }

    public Long getId() {
        return id;
    }

    public Produit getProduit() {
        return produit;
    }

    public void setProduit(Produit produit) {
        this.produit = produit;
    }

    public Integer getQuantite() {
        return quantite;
    }

    public void setQuantite(Integer quantite) {
        this.quantite = quantite;
    }

    @Override
    public String toString() {
        return "ProduitCommande{" + "id=" + id + ", produit=" + produit + ", quantite=" + quantite + '}';
    }
}
