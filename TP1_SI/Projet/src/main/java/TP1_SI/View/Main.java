package TP1_SI.View;

import TP1_SI.DAL.*;

/**
 * Fonction principale démarant la vue de connexion
 * @author B3330
 */
public class Main {

    public static void main(String[] arg) {
        JpaUtil.init();
        JpaUtil.creerEntityManager();

        ConsoleConnexionView connexion_view = new ConsoleConnexionView();
        connexion_view.run();

        JpaUtil.fermerEntityManager();
        JpaUtil.destroy();
    }
}
