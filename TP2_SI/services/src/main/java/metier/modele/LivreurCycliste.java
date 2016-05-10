/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.modele;

import javax.persistence.Entity;
/**
 *
 * @author qvecchio
 */
    @Entity
public class LivreurCycliste extends Livreur  {
    private String nom; 
    private String prenom; 

    public LivreurCycliste() {
        super();
    }

    public LivreurCycliste(String nom, String prenom, String mail, Double longitude, Double latitude, boolean IsFree, int poidMax) {
        super(longitude, latitude, IsFree, poidMax, mail);
        this.nom = nom;
        this.prenom = prenom;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    @Override
    public String toString() {
        return super.toString() + " && LivreurCycliste{" + ", nom=" + nom + ", prenom=" + prenom + '}';
    }
}
