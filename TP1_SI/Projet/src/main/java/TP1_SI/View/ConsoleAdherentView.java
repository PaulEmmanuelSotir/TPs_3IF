package TP1_SI.View;

/**
 * @author B3330
 */
public class ConsoleAdherentView extends ConsoleViewBase {

    public static void run() {
        System.out.println("Bonjour !");
        String nom = ConsoleConnexionView.lireChaine("Entrez votre nom: ");
        System.out.println("Bonjour, " + nom + " !");
        Integer age = ConsoleConnexionView.lireInteger("Entrez votre âge: ");
        System.out.println("Vous avez " + age + " ans.");
        System.out.println("Au revoir !");
    }


}
