/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.LivreurCycliste;

/**
 *
 * @author quentinvecchio
 */
public class LivreurCyclisteDao {
    public void create(LivreurCycliste livreur) throws Throwable {
           EntityManager em;
           em = JpaUtil.obtenirEntityManager();
        try {   
            em.persist(livreur);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public LivreurCycliste update(LivreurCycliste livreur) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            livreur = em.merge(livreur);
        }
        catch(Exception e){
            throw e;
        }
        return livreur;
    }
    
    public List<LivreurCycliste> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<LivreurCycliste> livreurs = null;
        try {
            Query q = em.createQuery("SELECT l FROM Livreur l");
            livreurs = (List<LivreurCycliste>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return livreurs;
    }
}
