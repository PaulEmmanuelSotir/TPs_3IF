/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;

import java.util.List;
import metier.modele.Commande;
import metier.service.Service;

/**
 *
 * @author quentinvecchio
 */
public class testCommandeEnCours {
   public static void main(String[] args) {
        Service service = new Service();
        List<Commande> c = service.findAllCommandeEnCours();
        System.out.print(c);
    } 
}
