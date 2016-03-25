/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TP1_SI.View;

import TP1_SI.metier.model.Adherent;
import TP1_SI.metier.service.ServiceResult;
import TP1_SI.metier.service.Services;
import TP1_SI.metier.service.Services.ConnexionError;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author B3330
 */
public class ConsoleConnexionView extends ConsoleViewBase {

    public void run() {
        if(selected_choice == "Connexion")
        {
            Services services = new Services();
            System.out.println("Entrez votre mail : ");
            Scanner terminalInput = new Scanner(System.in);
            String mail = terminalInput.nextLine();
            ServiceResult <Adherent, ConnexionError> nouvelleConnexion = services.Connexion(mail) ;
            if(nouvelleConnexion.error == ConnexionError.OK)
                goto_espace_adherents();
            else
            {
                System.out.println("Erreur de connexion");
            }
        } else if (selected_choice == "Inscription")
        {
            Services services = new Services();
            System.out.println("Entrez votre Nom : ");
            Scanner terminalInput = new Scanner(System.in);
            String nom = terminalInput.nextLine();
            System.out.println("\nEntrez votre Prénom : ");
            String prenom = terminalInput.nextLine();
            System.out.println("\nEntrez votre Mail : ");
            String mail = terminalInput.nextLine();
            System.out.println("\nEntrez votre Adresse : ");
            String adresse = terminalInput.nextLine();
            ServiceResult <Adherent, ConnexionError> nouvelleInscription = services.Inscription(nom, prenom, mail, adresse);
            if(nouvelleInscription.error == ConnexionError.OK)
                goto_espace_adherents();
            else
            {
                System.out.println("Erreur d'inscription");
            }
        }
    }
    
    public void goto_espace_adherents()
    {
        ConsoleAdherentView new_view = new ConsoleAdherentView();
        new_view.run();
    }
    
    public void goto_dashboard()
    {
        ConsoleDashboardView new_view = new ConsoleDashboardView();
        new_view.run();
    }
}
