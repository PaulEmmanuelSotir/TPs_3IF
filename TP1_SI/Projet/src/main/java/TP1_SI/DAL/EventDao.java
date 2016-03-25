package TP1_SI.DAL;

import TP1_SI.metier.model.Adherent;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import TP1_SI.metier.model.Event;
import java.sql.Date;

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
    
    public void AddAdherentToEvent(Event event, Adherent adherent) throws Throwable
    {
        List<Adherent> adherents =  event.getAdherents();
        adherents.add(adherent);
        event.setAdherents(adherents);
        if(event.getAdherents().size() == event.getActivite().getNbParticipants())
            event.setComplet();
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
    
    public List<Event> findDispo() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Event> events = null;
        try {
            Query q = em.createQuery("SELECT a FROM Event a WHERE a.complet = 'false'");
            events = (List<Event>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return events;
    }
    
    public List<Event> findByAdherent(long adherent_id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Event> events = null;
        try {
            Query q = em.createQuery("SELECT a FROM Event a, Event_Adherent c WHERE a.id = c.event_id AND b.id =" +adherent_id);
            events = (List<Event>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return events;
    }
    
     public List<Event> findByDate(Date date) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Event> events = null;
        try {
            Query q = em.createQuery("SELECT a FROM Event a WHERE a.date =" +date);
            events = (List<Event>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return events;
    }
    
}
