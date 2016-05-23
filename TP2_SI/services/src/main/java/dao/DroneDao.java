/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Drone;

/**
 *
 * @author quentinvecchio
 */
public class DroneDao {

    public void create(Drone drone) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(drone);
    }

    public Drone update(Drone drone) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        drone = em.merge(drone);
        return drone;
    }

    public List<Drone> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Drone> livreurs = null;
        Query q = em.createQuery("SELECT l FROM Livreur l");
        livreurs = (List<Drone>) q.getResultList();
        return livreurs;
    }
}
