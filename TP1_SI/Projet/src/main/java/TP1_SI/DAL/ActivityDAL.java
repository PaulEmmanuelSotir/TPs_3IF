package TP1_SI.DAL;

import java.util.List;
import javax.persistence.Query;
import javax.persistence.EntityManager;

import TP1_SI.metier.model.Activity;

/**
 * Data Access Layer permettant d'obtenir, de créer et modifier des instances de la classe 'Activity'.
 * Utilise JPA pour persiter les Activitées.
 * @author B3330
 */
public class ActivityDAL {

    public void create(Activity activity) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(activity);
    }

    public Activity update(Activity activity) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.merge(activity);
    }

    public Activity findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.find(Activity.class, id);
    }

    public List<Activity> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Activity a");
        return (List<Activity>) q.getResultList();
    }
}
