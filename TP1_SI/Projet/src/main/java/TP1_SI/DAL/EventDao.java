package TP1_SI.DAL;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import TP1_SI.metier.model.Event;

public class EventDao {
    
    public void create(Event event) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(event);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Event update(Event event) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            event = em.merge(event);
        }
        catch(Exception e){
            throw e;
        }
        return event;
    }
    
    public Event findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Event event = null;
        try {
            event = em.find(Event.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return event;
    }
    
    public List<Event> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Event> events = null;
        try {
            Query q = em.createQuery("SELECT a FROM Event a");
            events = (List<Event>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return events;
    }
}
