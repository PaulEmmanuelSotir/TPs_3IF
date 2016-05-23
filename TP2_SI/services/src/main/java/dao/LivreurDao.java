package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Livreur;

/**
 * @author Hugues
 */
public class LivreurDao {

    public void create(Livreur livreur) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(livreur);
    }

    public Livreur update(Livreur livreur) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        livreur = em.merge(livreur);
        return livreur;
    }

    public Livreur findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Livreur livreur = null;
        livreur = em.find(Livreur.class, id);
        return livreur;
    }

    /**
     * @param isFreeCnd
     * @param poidMaxCnd
     * @return
     */
    public List<Livreur> find(boolean isFreeCnd, Float poidMaxCnd) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        String conditaion = "";
        if (isFreeCnd) {
            conditaion += "l.IsFree=True AND ";
        }
        conditaion += "l.poidMax>=" + poidMaxCnd;
        List<Livreur> toReturn;
        toReturn = em.createQuery("Select l from Livreur l Where " + conditaion).getResultList();
        return toReturn;
    }

    public List<Livreur> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Livreur> livreurs = null;
        Query q = em.createQuery("SELECT l FROM Livreur l");
        livreurs = (List<Livreur>) q.getResultList();
        return livreurs;
    }
}
