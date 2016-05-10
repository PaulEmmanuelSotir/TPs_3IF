/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.sql.Date;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Commande;
import metier.modele.Livreur;
import metier.modele.ProduitCommande;

/**
 *
 * @author qvecchio
 */
public class CommandeDao {
    public void create(Commande cmd) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            for(ProduitCommande c : cmd.getContenues()) {
                em.persist(c);
            }
            em.persist(cmd);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Commande update(Commande cmd) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            cmd = em.merge(cmd);
        }
        catch(Exception e){
            throw e;
        }
        return cmd;
    }
    
    public Commande findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Commande cmd = null;
        try {
            cmd = em.find(Commande.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return cmd;
    }
    
    public List<Commande> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Commande> commandes = null;
        try {
            Query q = em.createQuery("SELECT c FROM Commande c");
            commandes = (List<Commande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }     
        return commandes;
    }
    
    public List<Commande> findAllEnCours() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Commande> commandes = null;
        try {
            Query q = em.createQuery("SELECT c FROM Commande c WHERE c.dateFin IS NULL");
            commandes = (List<Commande>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }     
        return commandes;
    }
    
    public Commande valideCommande(Commande cmd) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        cmd.setDateFin(new Date(System.currentTimeMillis()));
        cmd.getLivreur().setIsFree(true);
        Commande c = update(cmd);
        return c;
    }
}
