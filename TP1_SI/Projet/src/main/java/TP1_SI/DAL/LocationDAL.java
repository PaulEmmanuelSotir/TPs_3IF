package TP1_SI.DAL;

import java.util.List;
import javax.persistence.Query;
import javax.persistence.EntityManager;

import TP1_SI.metier.model.Location;

/**
 * Data Access Layer permettant d'obtenir, de créer et modifier des instances de la classe 'Location'.
 * Utilise JPA pour persiter les Lieux.
 * @author B3330
 */
public class LocationDAL {

    public void create(Location location) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(location);
    }

    public Location update(Location location) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.merge(location);
    }

    public Location findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.find(Location.class, id);
    }

    public List<Location> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT l FROM Location l");
        return (List<Location>) q.getResultList();
    }
}
