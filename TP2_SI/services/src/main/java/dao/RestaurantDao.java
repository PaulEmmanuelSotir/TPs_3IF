package dao;


import metier.modele.Restaurant;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;


public class RestaurantDao {
    
    public void create(Restaurant restaurant) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(restaurant);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Restaurant update(Restaurant restaurant) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            restaurant = em.merge(restaurant);
        }
        catch(Exception e){
            throw e;
        }
        return restaurant;
    }
    
    public Restaurant findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Restaurant restaurant = null;
        try {
            restaurant = em.find(Restaurant.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return restaurant;
    }
    
    public List<Restaurant> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Restaurant> restaurants = null;
        try {
            Query q = em.createQuery("SELECT r FROM Restaurant r order by r.id");
            restaurants = (List<Restaurant>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return restaurants;
    }
}
