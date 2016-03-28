package TP1_SI.View;

import java.util.List;

import TP1_SI.DAL.*;
import TP1_SI.metier.model.*;

/**
 * @author B3330
 */
public class Main {

    public static void main(String[] arg) {
        JpaUtil.creerEntityManager();

        ConsoleConnexionView connexion_view = new ConsoleConnexionView();
        connexion_view.run();
        
        /*
        MemberDAL adherent_dao = new MemberDAL();
        Member adherent = new Member("joey", "tim", "3 avenue Albert Einstein, 69100 VILLEURBANNE, FRANCE", "xdgszg@sdgs.com");
        Member adherent2 = new Member("joeyf8", "tsdim", "484 avenue Albert Einstein, 691500 VILLEURBANNE, FRANCE", "xdgsfzg@sdgs.com");
        
        LocationDAL lieu_dao = new LocationDAL();
        Location l = new Location("insa", "insa", "3 avenue Albert Einstein, 69100 VILLEURBANNE, FRANCE");
        Location dfg = new Location("truc", "dsds", "77 avenue Albert Einstein, 69100 VILLEURBANNE, FRANCE");
        
        ActivityDAL ativite_dao = new ActivityDAL();
        Activity act = new Activity("gkjpq", true, 456);
        
        try
        {
            JpaUtil.ouvrirTransaction();
            adherent_dao.create(adherent);
            adherent_dao.create(adherent2);
            lieu_dao.create(l);
            lieu_dao.create(dfg);
            ativite_dao.create(act);
            JpaUtil.validerTransaction();
            
            JpaUtil.ouvrirTransaction();
            Member ad2 = adherent_dao.findById(1);
            ad2.setMail("truc truc");
            adherent_dao.update(ad2);
            
            JpaUtil.validerTransaction();
            
            //List<Member> ads = adherent_dao.findAll();
            System.out.println("Lieux: ");
            System.out.println(lieu_dao.findAll());
            
            System.out.println("Adherents: ");
            System.out.println(adherent_dao.findAll());
            
            System.out.println("Activity: ");
            System.out.println(ativite_dao.findAll());
        }
        catch(Throwable e)
        {
            
        }*/

        JpaUtil.fermerEntityManager();
    }
}
