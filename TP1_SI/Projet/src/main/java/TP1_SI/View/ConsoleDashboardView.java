/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TP1_SI.View;

/**
 *
 * @author pesotir
 */
public class ConsoleDashboardView extends ConsoleViewBase {
    
     public static void run() {
        System.out.println("Bonjour !");
        String nom = ConsoleConnexionView.lireChaine("Entrez votre nom: ");
        System.out.println("Bonjour, " + nom + " !");
        Integer age = ConsoleConnexionView.lireInteger("Entrez votre âge: ");
        System.out.println("Vous avez " + age + " ans.");
        System.out.println("Au revoir !");
    }
}
