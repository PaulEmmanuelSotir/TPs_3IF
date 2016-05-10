/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;

import java.util.Scanner;
import metier.modele.Client;
import metier.service.Service;
import metier.modele.Commande;
import metier.modele.Restaurant;

/**
 *
 * @author qvecchio
 */
public class Main {
    public static void main(String[] args) {
        Service service = new Service();
        Scanner sc = new Scanner(System.in);
        String cmd;
        ClientView viewC = new ClientView();
        RestaurantView viewR = new RestaurantView();
        Client client;
        do {
            System.out.println("Connexion : c, Inscription : i ou Quitter : q");
            cmd = sc.nextLine();
            if(cmd.equals("i")) {
                viewC.createAccount();
            } else if(cmd.equals("c")) {
                client = viewC.connection();
                if(client != null) {
                    System.out.println("Bonjour " + client.getPseudo());
                    Restaurant restaurant = viewR.chooseRestaurant();
                    if(restaurant == null)
                        break;
                    Commande commande = viewR.chooseProduct(client, restaurant);
                    if(commande == null) 
                        break;
                    System.out.println("Félicitation, la commande a été enregistré");
                }
            }
        }while(cmd.equals("q") == false);
    }
}
