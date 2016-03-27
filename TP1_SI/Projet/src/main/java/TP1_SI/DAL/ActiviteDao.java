package TP1_SI.DAL;

import java.util.List;
import javax.persistence.Query;
import javax.persistence.EntityManager;

import TP1_SI.metier.model.Activite;

/**
 * @author B3330
 */
public class ActiviteDao {

    public void create(Activite activite) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(activite);
        } catch (Exception e) {
            throw e;
        }
    }

    public Activite update(Activite activite) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            activite = em.merge(activite);
        } catch (Exception e) {
            throw e;
        }
        return activite;
    }

    public Activite findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Activite activite = null;
        try {
            activite = em.find(Activite.class, id);
        } catch (Exception e) {
            throw e;
        }
        return activite;
    }

    public List<Activite> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Activite> activites = null;
        try {
            Query q = em.createQuery("SELECT a FROM Activite a");
            activites = (List<Activite>) q.getResultList();
        } catch (Exception e) {
            throw e;
        }

        return activites;
    }
}
