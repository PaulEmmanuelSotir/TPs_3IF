package dao;

import java.util.List;
import metier.modele.Client;
import javax.persistence.EntityManager;
import javax.persistence.Query;

/**
 * @author qvecchio
 */
public class ClientDao {
   public void create(Client client) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(client);
    }
    
    public Client update(Client client) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        client = em.merge(client);
        return client;
    }
    
    public Client findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Client client = null;
        client = em.find(Client.class, id);
        return client;
    }
    
    public Client findByPseudo(String pseudo) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Client client = null;
        Query q = em.createQuery("SELECT c FROM Client c WHERE c.pseudo = :n");
        q.setParameter("n",  pseudo);
        client = (Client) q.getSingleResult();
        return client;
    }
    
    public Client findClientByPseudoAndPassword(String pseudo, String password) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Client client = null;
        Query q = em.createQuery("SELECT c FROM Client c WHERE c.pseudo = :n and c.password = :p");
        q.setParameter("n",  pseudo);
        q.setParameter("p",  password);
        client = (Client) q.getSingleResult();
        return client;
    }
    
    public List<Client> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Client> clients = null;
        Query q = em.createQuery("SELECT c FROM Client c ORDER BY c.nom");
        clients = (List<Client>) q.getResultList();
        return clients;
    }
}
