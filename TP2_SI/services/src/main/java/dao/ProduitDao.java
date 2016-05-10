package dao;

import metier.modele.Produit;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;



public class ProduitDao {
    
    public void create(Produit produit) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(produit);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Produit update(Produit produit) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            produit = em.merge(produit);
        }
        catch(Exception e){
            throw e;
        }
        return produit;
    }
    
    public Produit findById(Long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Produit produit = null;
        try {
            produit = em.find(Produit.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return produit;
    }
    
    public List<Produit> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Produit> produits = null;
        try {
            Query q = em.createQuery("SELECT p FROM Produit p order by p.id");
            produits = (List<Produit>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return produits;
    }
}
