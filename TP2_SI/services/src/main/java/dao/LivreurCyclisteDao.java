package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.LivreurCycliste;

/**
 * @author quentinvecchio
 */
public class LivreurCyclisteDao {

    public void create(LivreurCycliste livreur) throws Throwable {
        EntityManager em;
        em = JpaUtil.obtenirEntityManager();
        em.persist(livreur);
    }

    public LivreurCycliste update(LivreurCycliste livreur) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        livreur = em.merge(livreur);
        return livreur;
    }

    public List<LivreurCycliste> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<LivreurCycliste> livreurs = null;
        Query q = em.createQuery("SELECT l FROM Livreur l");
        livreurs = (List<LivreurCycliste>) q.getResultList();
        return livreurs;
    }
}
