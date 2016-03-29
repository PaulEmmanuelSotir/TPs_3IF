package TP1_SI.View;

import TP1_SI.Utils.Callable;
import TP1_SI.Utils.ConsoleMenu;
import TP1_SI.Utils.ConsoleUtils;
import TP1_SI.metier.model.Member;
import TP1_SI.metier.service.Services;
import TP1_SI.metier.service.ServiceResult;
import TP1_SI.metier.service.Services.ConnexionError;

import java.util.Scanner;

/**
 * Classe gèrant la vue console de connexion.
 * L'utilisateur peut y creer un compte ou se connecter avec une compte existant.
 * @author B3330
 */
public class ConsoleConnexionView {
    static final String admin_email = "admin.collectif@insa-lyon.fr";

    /**
     * Lance la vue
     */
    public void run() {
        ConsoleMenu connexion_menu = new ConsoleMenu("CONNEXION MENU", new Quit());
        connexion_menu.addChoice(new Login(), "Log in");
        connexion_menu.addChoice(new Signin(), "Sign in");

        connexion_menu.runMenu();
    }

    /**
     * Callback gèrant la connexion avezc un coimpte existant
     */
    private static class Login implements Callable
    {
        @Override
        public void call() {
            System.out.println("### Connexion ###");
            String email = ConsoleUtils.lireChaine("Entrez votre mail : ");
            if(!admin_email.equals(email))
            {
                ServiceResult<Member, ConnexionError> newConnexion = Services.Connexion(email);
                if (newConnexion.error == ConnexionError.OK)
                    goto_espace_adherents(newConnexion.result);
                else
                    // TODO: gèrer l'erreur en fonction de 'newConnexion.error'
                    System.out.println("Erreur de connexion : " + newConnexion.error);
            }
            else
                goto_dashboard();
        }
    }

    /**
     * Callback gèrant la création de comptes
     */
    private static class Signin implements Callable
    {
        @Override
        public void call() {
            System.out.println("### Inscription ###");
            String nom = ConsoleUtils.lireChaine("Entrez votre Nom : ");
            String prenom = ConsoleUtils.lireChaine("Entrez votre Prenom : ");
            String email = ConsoleUtils.lireChaine("Entrez votre Email : ");
            String address = ConsoleUtils.lireChaine("Entrez votre Adresse : ");
            if(!admin_email.equals(email))
            {
                ServiceResult<Member, ConnexionError> newInscription = Services.Inscription(nom, prenom, email, address);
                if (newInscription.error == ConnexionError.OK)
                    goto_espace_adherents(newInscription.result);
                else
                    // TODO: gèrer l'erreur en fonction de 'newInscription.error'
                    System.out.println("Erreur d'inscription : " + newInscription.error);
            }
            else
                System.out.println("Erreur d'inscription : " + ConnexionError.BAD_EMAIL);
        }
    }

    /**
     * Callback appelée si l'utilisateur veux quitter l'application
     */
    private static class Quit implements Callable {
        @Override
        public void call() {
            System.out.println("\n\nExiting application...");
        }
    }

    /**
     * Navigue vers la vue 'espace adherent' (MemberView)
     * @param logged_member Membre s'étant coinnecté avec succès
     */
    private static void goto_espace_adherents(Member logged_member) {
        System.out.println("##########################################\n");
        ConsoleMemberView new_view = new ConsoleMemberView(logged_member);
        new_view.run();
    }

    /**
     * Navigue vers la vue dashboard de l'administrateur
     */
    private static void goto_dashboard() {
        System.out.println("##########################################\n");
        ConsoleDashboardView new_view = new ConsoleDashboardView();
        new_view.run();
    }
}
