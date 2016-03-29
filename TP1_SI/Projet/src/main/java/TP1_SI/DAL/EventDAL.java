package TP1_SI.DAL;

import javax.persistence.EntityManager;
import javax.persistence.Query;
import java.util.List;
import java.sql.Date;

import TP1_SI.metier.model.Member;
import TP1_SI.metier.model.Event;

/**
 * Data Access Layer permettant d'obtenir, de créer et modifier des instances de la classe 'Event'.
 * Utilise JPA pour persiter les Evenements.
 * @author B3330
 */
public class EventDAL {

    public void create(Event event) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(event);
    }

    public Event update(Event event) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.merge(event);
    }

    public Event findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.find(Event.class, id);
    }

    public void AddAdherentToEvent(Event event, Member member) throws Throwable {
        event.getMembers().add(member);
        update(event);
        if (event.getMembers().size() == event.getActivity().getNbParticipants())
            event.setComplet();
    }

    public List<Event> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Event a");
        return (List<Event>)q.getResultList();
    }

    public List<Event> findDispo() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Event a WHERE a.complet = FALSE");
        return (List<Event>)q.getResultList();
    }

    public List<Event> findByMember(long member_id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT e FROM Event e INNER JOIN e.members event_member WHERE event_member.id = " + member_id);
        return (List<Event>)q.getResultList();
    }

    public List<Event> findByDate(Date date) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Event a WHERE a.date = " + date);
        return (List<Event>)q.getResultList();
    }

}
