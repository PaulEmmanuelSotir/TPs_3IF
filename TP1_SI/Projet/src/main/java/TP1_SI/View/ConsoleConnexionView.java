package TP1_SI.View;

import TP1_SI.metier.model.Member;
import TP1_SI.metier.service.Services;
import TP1_SI.metier.service.ServiceResult;
import TP1_SI.metier.service.Services.ConnexionError;

import java.util.Scanner;

/**
 * @author B3330
 */
public class ConsoleConnexionView extends ConsoleViewBase {

    public void run() {
        String selected_choice = "";
        if (selected_choice.equals("Connexion")) {
            Services services = new Services();
            System.out.println("Entrez votre mail : ");
            Scanner terminalInput = new Scanner(System.in);
            String mail = terminalInput.nextLine();
            ServiceResult<Member, ConnexionError> nouvelleConnexion = services.Connexion(mail);
            if (nouvelleConnexion.error == ConnexionError.OK)
                goto_espace_adherents();
            else
                System.out.println("Erreur de connexion");
        } else if (selected_choice.equals("Inscription")) {
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
            ServiceResult<Member, ConnexionError> nouvelleInscription = services.Inscription(nom, prenom, mail, adresse);
            if (nouvelleInscription.error == ConnexionError.OK)
                goto_espace_adherents();
            else
                System.out.println("Erreur d'inscription");
        }
    }

    public void goto_espace_adherents() {
        ConsoleMemberView new_view = new ConsoleMemberView();
        new_view.run();
    }

    public void goto_dashboard() {
        ConsoleDashboardView new_view = new ConsoleDashboardView();
        new_view.run();
    }
}
