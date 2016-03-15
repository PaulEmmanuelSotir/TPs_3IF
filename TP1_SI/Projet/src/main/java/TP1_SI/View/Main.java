/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TP1_SI.View;

import TP1_SI.DAL.*;
import TP1_SI.metier.model.*;
import java.util.List;
/**
 *
 * @author B3330
 */
public class Main {
    public static void main(String[] arg)
    {
        JpaUtil.creerEntityManager();
         
        AdherentDao adherent_dao = new AdherentDao();
        Adherent adherent = new Adherent("joey", "tim", "3 avenue Albert Einstein, 69100 VILLEURBANNE, FRANCE", "xdgszg@sdgs.com");
        Adherent adherent2 = new Adherent("joeyf8", "tsdim", "484 avenue Albert Einstein, 691500 VILLEURBANNE, FRANCE", "xdgsfzg@sdgs.com");
        
        LieuDao lieu_dao = new LieuDao();
        Lieu l = new Lieu("insa", "insa", "3 avenue Albert Einstein, 69100 VILLEURBANNE, FRANCE");
        Lieu dfg = new Lieu("truc", "dsds", "77 avenue Albert Einstein, 69100 VILLEURBANNE, FRANCE");
        
        ActiviteDao ativite_dao = new ActiviteDao();
        Activite act = new Activite("gkjpq", true, 456);
        
        try
        {
            /*JpaUtil.ouvrirTransaction();
            adherent_dao.create(adherent);
            adherent_dao.create(adherent2);
            lieu_dao.create(l);
            lieu_dao.create(dfg);
            ativite_dao.create(act);
            JpaUtil.validerTransaction();
            
            JpaUtil.ouvrirTransaction();
            Adherent ad2 = adherent_dao.findById(1);
            ad2.setMail("truc truc");
            adherent_dao.update(ad2);
            
            JpaUtil.validerTransaction();
            
            //List<Adherent> ads = adherent_dao.findAll();
            System.out.println("Lieux: ");
            System.out.println(lieu_dao.findAll());
            
            System.out.println("Adherents: ");
            System.out.println(adherent_dao.findAll());
            
            System.out.println("Activite: ");
            System.out.println(ativite_dao.findAll());*/
        }
        catch(Throwable e)
        {
            
        }
        
        JpaUtil.fermerEntityManager();
    }
}
