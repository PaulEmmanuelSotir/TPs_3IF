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
        for (ProduitCommande c : cmd.getContenues()) {
            em.persist(c);
        }
        em.persist(cmd);
    }

    public Commande update(Commande cmd) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        cmd = em.merge(cmd);
        return cmd;
    }

    public Commande findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Commande cmd = null;
        cmd = em.find(Commande.class, id);
        return cmd;
    }

    public List<Commande> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Commande> commandes = null;
        Query q = em.createQuery("SELECT c FROM Commande c");
        commandes = (List<Commande>) q.getResultList();
        return commandes;
    }

    public List<Commande> findAllEnCours() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Commande> commandes = null;
        Query q = em.createQuery("SELECT c FROM Commande c WHERE c.dateFin IS NULL");
        commandes = (List<Commande>) q.getResultList();
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
