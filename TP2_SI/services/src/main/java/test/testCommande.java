/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;

import java.sql.Date;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import metier.modele.Client;
import metier.modele.Commande;
import metier.modele.Produit;
import metier.modele.ProduitCommande;
import metier.modele.Restaurant;
import metier.service.Service;

/**
 *
 * @author quentinvecchio
 */
public class testCommande {
    public static void main(String[] args) {
        Service service = new Service();
        Client c = service.connection("qvecchio", "qvecchio");
        Restaurant r = service.findRestaurantById(new Long(1));
        List<ProduitCommande> contenues = new ArrayList<>();
        System.out.println(c);
        System.out.println(r);
        contenues.add(new ProduitCommande(r.getProduits().get(0),1));
        Commande c1 = new Commande(c, r, contenues);
        service.createCommande(c1);
    }
}
