package TP1_SI.DAL;

import java.util.List;
import javax.persistence.Query;
import javax.persistence.EntityManager;

import TP1_SI.metier.model.Member;

/**
 * Data Access Layer permettant d'obtenir, de créer et modifier des instances de la classe 'Member'.
 * Utilise JPA pour persiter les Membres.
 * @author B3330
 */
public class MemberDAL {

    public void create(Member member) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(member);
    }

    public Member update(Member member) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.merge(member);
    }

    public Member findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        return em.find(Member.class, id);
    }

    public Member findByMail(String mail) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Member a WHERE a.mail='" + mail + "'");
        List<Member> members = (List<Member>) q.getResultList();

        if (members.size() >= 1)
            return members.get(0);
        return null;
    }

    public List<Member> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Query q = em.createQuery("SELECT a FROM Member a");
        return (List<Member>)q.getResultList();
    }
}
