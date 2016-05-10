/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;

import java.sql.Date;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import metier.modele.Client;
import metier.modele.Commande;
import metier.modele.Produit;
import metier.modele.ProduitCommande;
import metier.modele.Restaurant;
import metier.service.Service;

/**
 *
 * @author qvecchio
 */
public class RestaurantView {
    private Service service = new Service();
    private Scanner sc = new Scanner(System.in);
    
    public RestaurantView() {
        
    }
    
    public Restaurant chooseRestaurant() {
        Restaurant r = null;
        do {
            System.out.println("Liste des restaurants : ");
            List<Restaurant> restaurants = service.findAllRestaurant();
            if(restaurants == null)
                   System.out.println("");
            for(Restaurant res : restaurants) {
                System.out.println(res.getId() + " - " + res.getDenomination());
                System.out.println("\t" + res.getDescription());
            }
            System.out.println("Choix restaurant (id) : ");
            long id = sc.nextLong();
            if(id < 0)
                break;
            r = service.findRestaurantById(id);
        }while(r == null);
        return r;
    }
    
    public Commande chooseProduct(Client client, Restaurant restaurant) {
       Commande c = new Commande();
       c.setClient(client);
       c.setRestaurant(restaurant);
       List<ProduitCommande> contenues = new ArrayList<>();
       String cmd = null;
       do {
            sc = new Scanner(System.in);
            System.out.println("Liste des produits du restaurant " + restaurant.getDenomination() + " : ");
            for(Produit prod : restaurant.getProduits()) {
                System.out.println(prod.getId() + " - " + prod.getDenomination());
                System.out.println("\t" + prod.getDescription());
            }
            System.out.println("Choix produit (id) (f pour finaliser la commande) : ");
            cmd = sc.nextLine();
            try {
                Produit p = service.findProduitById(Long.parseLong(cmd));
                System.out.println(p.getId() + " - " + p.getDenomination());
                System.out.println("\t" + p.getDescription());
                System.out.println("Quantité : ");
                int qt = sc.nextInt();
            contenues.add(new ProduitCommande(p, qt));
            } catch (Exception e) {
                if(cmd.equals("f") == false)
                    System.out.println("Cet id n'est pas bon" + cmd);
            }    
        }while(!cmd.equals("f") && !cmd.equals("q"));
       if(cmd.equals("q"))
           return null;
       System.out.println("Récapitulatif : ");
       for(ProduitCommande p : contenues)
       {
           System.out.println("\t" + p.getProduit().getDenomination() + "\t" + p.getQuantite());
       } 
       c.setContenues(contenues);
       c.setClient(client);
       if(service.createCommande(c) == false)
           System.out.println("Votre commande ne peut être prise en charge pour le moment.");
       else
           System.out.println("Votre commande est bien prise en charge.");
       return c; 
    }
    
}
