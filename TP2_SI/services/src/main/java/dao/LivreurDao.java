/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Livreur;

/**
 *
 * @author Hugues
 */
public class LivreurDao {
    public void create(Livreur livreur) throws Throwable {
           EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(livreur);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Livreur update(Livreur livreur) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            livreur = em.merge(livreur);
        }
        catch(Exception e){
            throw e;
        }
        return livreur;
    }

    public Livreur findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Livreur livreur = null;
        try {
            livreur = em.find(Livreur.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return livreur;
    }
    /**
     *
     * @param isFreeCnd
     * @param poidMaxCnd
     * @return
     */
    public List<Livreur> find(boolean isFreeCnd, Float poidMaxCnd ) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        String conditaion = "";
        if (isFreeCnd) conditaion+= "l.IsFree=True AND ";
        conditaion+= "l.poidMax>="+poidMaxCnd;  
        List<Livreur> toReturn;
        try {
            toReturn = em.createQuery("Select l from Livreur l Where "+conditaion).getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return toReturn;
    }
    
    public List<Livreur> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Livreur> livreurs = null;
        try {
            Query q = em.createQuery("SELECT l FROM Livreur l");
            livreurs = (List<Livreur>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        return livreurs;
    }
}

