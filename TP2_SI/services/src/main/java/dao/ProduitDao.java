package dao;

import metier.modele.Produit;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;

public class ProduitDao {

    public void create(Produit produit) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        em.persist(produit);
    }

    public Produit update(Produit produit) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        produit = em.merge(produit);
        return produit;
    }

    public Produit findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Produit produit = null;
        produit = em.find(Produit.class, id);
        return produit;
    }

    public List<Produit> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Produit> produits = null;

        Query q = em.createQuery("SELECT p FROM Produit p order by p.id");
        produits = (List<Produit>) q.getResultList();

        return produits;
    }
}
