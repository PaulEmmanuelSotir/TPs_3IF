package dao;

import metier.modele.Restaurant;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class RestaurantDao {

    public void create(Restaurant restaurant) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(restaurant);
    }

    public Restaurant update(Restaurant restaurant) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        restaurant = em.merge(restaurant);
        return restaurant;
    }

    public Restaurant findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Restaurant restaurant = null;
        restaurant = em.find(Restaurant.class, id);
        return restaurant;
    }

    public List<Restaurant> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Restaurant> restaurants = null;
        Query q = em.createQuery("SELECT r FROM Restaurant r order by r.id");
        restaurants = (List<Restaurant>) q.getResultList();

        return restaurants;
    }
}
