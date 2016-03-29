package TP1_SI.DAL;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.RollbackException;

/**
 * Cette classe fournit des méthodes statiques utiles pour accéder aux
 * fonctionnalités de JPA (Entity Manager, Entity Transaction). Le nom de
 * l'unité de persistance (PERSISTENCE_UNIT_NAME) doit être conforme à la
 * configuration indiquée dans le fichier persistence.xml du projet.
 *
 * Version du 22 Mars 2016
 *
 * @author DASI Team
 */
public class JpaUtil {

    // *************************************************************************************
    // * TODO: IMPORTANT -- Adapter le nom de l'Unité de Persistance (cf. persistence.xml) *
    // *************************************************************************************
    /**
     * Nom de l'unité de persistance utilisée par la Factory de Entity Manager.
     * <br/><strong>Vérifier le nom de l'unité de persistance
     * (cf.&nbsp;persistence.xml)</strong>
     */
    public static final String PERSISTENCE_UNIT_NAME = "B3330_TP1_SI_jar_1.0-SNAPSHOTPU";
    /**
     * Factory de Entity Manager liée à l'unité de persistance.
     * <br/><strong>Vérifier le nom de l'unité de persistance indiquée dans
     * l'attribut statique PERSISTENCE_UNIT_NAME
     * (cf.&nbsp;persistence.xml)</strong>
     */
    private static EntityManagerFactory entityManagerFactory = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT_NAME);
    /**
     * Gère les instances courantes de Entity Manager liées aux Threads.
     * L'utilisation de ThreadLocal garantie une unique instance courante par
     * Thread.
     */
    private static final ThreadLocal<EntityManager> threadLocalEntityManager = new ThreadLocal<EntityManager>() {

        @Override
        protected EntityManager initialValue() {
            return null;
        }
    };

    // Pause (sans exception)
    private static void pause(long milliseconds) {
        try {
            Thread.sleep(milliseconds);
        } catch (InterruptedException ex) {
        }
    }

    // Log sur la console
    // Les flush & pause sont là pour (tenter de) synchroniser les sorties sur la console
    private static void log(String message) {
        System.out.flush();
        pause(5);
        System.err.println("[JpaUtil:Log] " + message);
        System.err.flush();
        pause(5);
    }

    /**
     * Initialise la Factory de Entity Manager (nécessaire au fonctionnement de
     * JpaUtil dans une Application Web sous Glassfish).
     * <br/><strong>À utiliser uniquement dans la méthode init() de la Servlet
     * Contrôleur (ActionServlet).</strong>
     */
    public static synchronized void init() {
        log("Initialisation de la factory de contexte de persistance");
        if (entityManagerFactory != null) {
            entityManagerFactory.close();
        }
        entityManagerFactory = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT_NAME);
    }

    /**
     * Libère la Factory de Entity Manager (pour permettre un futur rechargement
     * propre d'une Application Web sous Glassfish).
     * <br/><strong>À utiliser uniquement dans la méthode destroy() de la
     * Servlet Contrôleur (ActionServlet).</strong>
     */
    public static synchronized void destroy() {
        log("Libération de la factory de contexte de persistance");
        if (entityManagerFactory != null) {
            entityManagerFactory.close();
            entityManagerFactory = null;
        }
    }

    /**
     * Créée l'instance courante de Entity Manager (liée à ce Thread).
     * <br/><strong>À utiliser uniquement au niveau Service.</strong>
     */
    public static void creerEntityManager() {
        log("Création du contexte de persistance");
        threadLocalEntityManager.set(entityManagerFactory.createEntityManager());
    }

    /**
     * Ferme l'instance courante de Entity Manager (liée à ce Thread).
     * <br/><strong>À utiliser uniquement au niveau Service.</strong>
     */
    public static void fermerEntityManager() {
        log("Fermeture du contexte de persistance");
        EntityManager em = threadLocalEntityManager.get();
        em.close();
        threadLocalEntityManager.set(null);
    }

    /**
     * Démarre une transaction sur l'instance courante de Entity Manager.
     * <br/><strong>À utiliser uniquement au niveau Service.</strong>
     */
    public static void ouvrirTransaction() {
        log("Début de la transaction");
        EntityManager em = threadLocalEntityManager.get();
        if (em.getTransaction().isActive()) {
            log("ATTENTION: la transaction est déjà ouverte");
        }
        em.getTransaction().begin();
    }

    /**
     * Valide la transaction courante sur l'instance courante de Entity Manager.
     * <br/><strong>À utiliser uniquement au niveau Service.</strong>
     *
     * @exception RollbackException lorsque le <em>commit</em> n'a pas réussi.
     */
    public static void validerTransaction() throws RollbackException {
        log("Validation (commit) de la transaction");
        EntityManager em = threadLocalEntityManager.get();
        if (!em.getTransaction().isActive()) {
            log("ATTENTION: la transaction N'est PAS ouverte");
        }
        em.getTransaction().commit();
    }

    /**
     * Annule la transaction courante sur l'instance courante de Entity Manager.
     * Si la transaction courante n'est pas démarrée, cette méthode n'effectue
     * aucune opération.
     * <br/><strong>À utiliser uniquement au niveau Service.</strong>
     */
    public static void annulerTransaction() {
        log("Annulation (rollback) de la transaction");
        EntityManager em = threadLocalEntityManager.get();
        if (!em.getTransaction().isActive()) {
            log("ATTENTION: la transaction N'est PAS ouverte => annulation ignorée par JpaUtil");
        } else {
            em.getTransaction().rollback();
        }
    }

    /**
     * Retourne l'instance courante de Entity Manager.
     * <br/><strong>À utiliser uniquement au niveau DAO.</strong>
     *
     * @return instance de Entity Manager
     */
    public static EntityManager obtenirEntityManager() {
        log("Obtention du contexte de persistance");
        return threadLocalEntityManager.get();
    }

}
