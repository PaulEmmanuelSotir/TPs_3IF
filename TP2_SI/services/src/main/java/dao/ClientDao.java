/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import metier.modele.Client;
import javax.persistence.EntityManager;
import javax.persistence.Query;

/**
 *
 * @author qvecchio
 */
public class ClientDao {
   public void create(Client client) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(client);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Client update(Client client) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            client = em.merge(client);
        }
        catch(Exception e){
            throw e;
        }
        return client;
    }
    
    public Client findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Client client = null;
        try {
            client = em.find(Client.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return client;
    }
    
    public Client findByPseudo(String pseudo) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Client client = null;
        try {
            Query q = em.createQuery("SELECT c FROM Client c WHERE c.pseudo = :n");
            q.setParameter("n",  pseudo);
            client = (Client) q.getSingleResult();
        }
        catch(Exception e) {
            throw e;
        }
        return client;
    }
    
    public Client findClientByPseudoAndPassword(String pseudo, String password) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Client client = null;
        try {
            Query q = em.createQuery("SELECT c FROM Client c WHERE c.pseudo = :n and c.password = :p");
            q.setParameter("n",  pseudo);
            q.setParameter("p",  password);
            client = (Client) q.getSingleResult();
        }
        catch(Exception e) {
            throw e;
        }
        return client;
    }
    
    public List<Client> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Client> clients = null;
        try {
            Query q = em.createQuery("SELECT c FROM Client c ORDER BY c.nom");
            clients = (List<Client>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }     
        return clients;
    }
}
