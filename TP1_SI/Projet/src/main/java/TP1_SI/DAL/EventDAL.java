package TP1_SI.DAL;

import javax.persistence.EntityManager;
import javax.persistence.Query;
import java.util.List;
import java.sql.Date;

import TP1_SI.metier.model.Member;
import TP1_SI.metier.model.Event;

/**
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
        List<Member> members = event.getMembers();
        members.add(member);
        event.setMembers(members);
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

    public List<Event> findByMember(long adherent_id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Event a, Event_Member c WHERE a.id = c.event_id AND b.id = " + adherent_id);
        return (List<Event>)q.getResultList();
    }

    public List<Event> findByDate(Date date) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Event a WHERE a.date = " + date);
        return (List<Event>)q.getResultList();
    }

}
