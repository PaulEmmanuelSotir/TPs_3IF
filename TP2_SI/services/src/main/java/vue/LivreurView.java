/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;

import java.util.Scanner;
import metier.modele.Commande;
import metier.service.Service;

/**
 *
 * @author quentinvecchio
 */
public class LivreurView {
    public static void main(String[] args) {
        Service service = new Service();
        Scanner sc = new Scanner(System.in);
        while(true) {
            System.out.println("Mail : ");
            String mail = sc.nextLine();
            System.out.println("Numéro de commande : ");
            Long numCmd = sc.nextLong();
            sc.nextLine();
            Commande cmd = service.valideCommande(mail, numCmd);
            if(cmd != null) {
                System.out.println("Commande " + cmd.getId() + " validée à " + cmd.getDateFin());
                System.out.println("Récapitulatif : \n");
                System.out.println(cmd);
            } else {
                System.out.println("Erreur : Commande inexistante");
            }
        }
    }
}
