package metier.service;

import dao.ClientDao;
import dao.CommandeDao;
import dao.DroneDao;
import dao.JpaUtil;
import dao.LivreurCyclisteDao;
import dao.LivreurDao;
import dao.ProduitDao;
import dao.RestaurantDao;
import java.sql.Date;
import java.util.List;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import metier.modele.Client;
import metier.modele.Commande;
import metier.modele.Drone;
import metier.modele.Livreur;
import metier.modele.LivreurCycliste;
import metier.modele.Produit;
import metier.modele.ProduitCommande;
import metier.modele.Restaurant;

/**
 * @author qvecchio
 */
public class Service {
    private final ClientDao clientDao = new ClientDao();
    private final RestaurantDao restaurantDao = new RestaurantDao();
    private final ProduitDao produitDao = new ProduitDao();
    private final CommandeDao commandeDao = new CommandeDao();
    private final DroneDao droneDao = new DroneDao();
    private final LivreurDao livreurDao = new LivreurDao();
    private final LivreurCyclisteDao livreurCyclisteDao = new LivreurCyclisteDao();
    private final ServiceTechnique serviceTechnique = new ServiceTechnique();
    
    public boolean clientExist(String pseudo) {
        JpaUtil.creerEntityManager();
        try {
            return (clientDao.findByPseudo(pseudo) != null);
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return false;
    }
    
    public boolean createClient(Client client) {
        JpaUtil.creerEntityManager();
        try {
            JpaUtil.ouvrirTransaction();
            clientDao.create(client);
            JpaUtil.validerTransaction();
            String contenu = "Bonjour " + client.getPseudo();
            contenu += "\n\nVotre compte a bien été créé";
            contenu += "\n\nVos informations : \n" + client.getNom() + " " + client.getPrenom() + "\n";
            contenu += client.getAdresse();
            contenu += "\n" + client.getMail();
            serviceTechnique.sendMail(client.getMail(),"Confirmation création du compte ", contenu);
            JpaUtil.fermerEntityManager();
            return true;
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.annulerTransaction();
        JpaUtil.fermerEntityManager();
        return false;
    }
    
    public Client updateClient(Client client) {
        JpaUtil.creerEntityManager();
        try {
            return clientDao.update(client);
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
     
    public Client connectClient(String pseudo, String password) {
        JpaUtil.creerEntityManager();
        try {
            return clientDao.findClientByPseudoAndPassword(pseudo, password);
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public List<Client> findAllClient() {
        JpaUtil.creerEntityManager();
        try {
            return clientDao.findAll();
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }

    public Restaurant findRestaurantById(Long id) {
        JpaUtil.creerEntityManager();
        try {
            return restaurantDao.findById(id);
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
       
    public List<Restaurant> findAllRestaurant() {
        JpaUtil.creerEntityManager();
        try {
            return restaurantDao.findAll();
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public Produit findProduitById(Long id) {
        JpaUtil.creerEntityManager();
        try {
            return produitDao.findById(id);
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public List<Produit> findAllProduit() {
        JpaUtil.creerEntityManager();
        try {
            return produitDao.findAll();
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public List<Livreur> findAllLivreur() {
        JpaUtil.creerEntityManager();
        try {
            return livreurDao.findAll();
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public boolean createCommande(Commande cmd) {
        JpaUtil.creerEntityManager();
        try {
            //Chercher un livreur
            float poidT = 0;
            for(ProduitCommande p : cmd.getContenues())
                poidT += p.getQuantite();
            List<Livreur> list = livreurDao.find(true, poidT);
            if(list.size() > 0) {
                Livreur l = serviceTechnique.findBestLivreur(list, cmd.getClient().getLatitude(), cmd.getClient().getLongitude());
                if(l == null) {
                    JpaUtil.fermerEntityManager();
                    return false;
                } else {            
                    JpaUtil.ouvrirTransaction();
                    Livreur l2 = livreurDao.findById(l.getId());
                    if(l2.getIsFree())
                    {
                        l2.setIsFree(false);
                        cmd.setLivreur(livreurDao.update(l2));
                        JpaUtil.validerTransaction();
                    } else {
                        JpaUtil.annulerTransaction();
                        JpaUtil.fermerEntityManager();
                        return false;
                    }
                    JpaUtil.ouvrirTransaction();
                    System.out.println("Veullez tapper sur une touche du clavier pour continuer...");
                    cmd.setDateDebut(new Date(System.currentTimeMillis()));
                    cmd.setDateFin(null);
                    Scanner s = new Scanner(System.in);
                    s.nextLine();
                    commandeDao.create(cmd);
                    JpaUtil.validerTransaction();
                    //Envoyer un mail
                    serviceTechnique.sendMail(l2.getMail(),"Livraison commande " + cmd.getId(), cmd.toString());
                    JpaUtil.fermerEntityManager();
                    return true;
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.annulerTransaction();
        JpaUtil.fermerEntityManager();
        return false;
    }
    
    public void createLivreurCycliste(LivreurCycliste livreur) {
        JpaUtil.creerEntityManager();
        try {
            JpaUtil.ouvrirTransaction();
            livreurCyclisteDao.create(livreur);
            JpaUtil.validerTransaction();
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.annulerTransaction();
        JpaUtil.fermerEntityManager();
    }
    
    public void createDrone(Drone drone) {
        JpaUtil.creerEntityManager();
        try {
            JpaUtil.ouvrirTransaction();
            droneDao.create(drone);
            JpaUtil.validerTransaction();
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.annulerTransaction();
        JpaUtil.fermerEntityManager();
    }
    
    public Livreur findLivreurById(Long id) {
        JpaUtil.creerEntityManager();
        try {
            Livreur l = livreurDao.findById(id);
            JpaUtil.fermerEntityManager();
            return l;
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public Commande valideCommande(String mail, Long num) {
        JpaUtil.creerEntityManager();
        try {
            JpaUtil.ouvrirTransaction();
            Commande cmd = commandeDao.findById(num);
            if(cmd != null) {
                if(cmd.getLivreur().getMail().equals(mail) == false)
                    return null;
                else
                    cmd = commandeDao.valideCommande(cmd);
            }
            JpaUtil.validerTransaction();
            JpaUtil.fermerEntityManager();
            return cmd;
        } catch (Exception e) {
            
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.annulerTransaction();
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public List<Commande> findAllCommande() {
        JpaUtil.creerEntityManager();
        try {
            List<Commande> cmds = commandeDao.findAll();
            JpaUtil.fermerEntityManager();
            return cmds;
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
    
    public List<Commande> findAllCommandeEnCours() {
        JpaUtil.creerEntityManager();
        try {
            List<Commande> cmds = commandeDao.findAllEnCours();
            JpaUtil.fermerEntityManager();
            return cmds;
        } catch (Exception e) {
            System.out.println(e);
        } catch (Throwable ex) {
            Logger.getLogger(Service.class.getName()).log(Level.SEVERE, null, ex);
        }
        JpaUtil.fermerEntityManager();
        return null;
    }
}
