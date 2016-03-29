package TP1_SI.metier.service;

import java.sql.Date;
import java.util.List;

import TP1_SI.DAL.*;
import com.google.maps.model.LatLng;

import TP1_SI.metier.model.Event;
import TP1_SI.metier.model.Member;
import TP1_SI.metier.model.Activity;
import TP1_SI.metier.model.Location;

/**
 * Classe regroupant les services metier de l'application COLLECT'IF.
 * @author B3330
 */
public class Services {

    /**
     * Enumération des codes d'erreur pouvant se produire lors de la connexion/inscription d'un membre
     */
    public enum ConnexionError {
        OK, EMPTY_NAME, EMPTY_FIRSTNAME, EMPTY_ADDRESS, EMPTY_EMAIL, WRONG_ADDRESS, BAD_EMAIL, DATABASE_ERROR
    }

    /**
     * Enumération des codes d'erreur pouvant se produire lors de l'appel aux autres services (voir type de retour dez méthodes ci-dessous)
     */
    public enum Request_Error {
        OK, WRONG_EVENT_ID, WRONG_LIEU_ID, WRONG_MEMBER_ID, WRONG_ACTIVITY_ID, FULL_EVENT, DATABASE_ERROR
    }

    /**
     * Methode permettant la connexion d'un membre à partir de son email
     * @param mail email du membre
     * @return retourne le membre connecté ou un code d'erreur détaillant les raisons de l'echec de la connexion (OK, DATABASE_ERROR ou BAD_EMAIL)
     */
    public static ServiceResult<Member, ConnexionError> Connexion(String mail) {
        try {
            MemberDAL adherent_dao = new MemberDAL();
            Member member = adherent_dao.findByMail(mail);
            if (member == null)
                return new ServiceResult<Member, ConnexionError>(null, ConnexionError.BAD_EMAIL);
            return new ServiceResult<Member, ConnexionError>(member, ConnexionError.OK);
        } catch (Throwable e) {
            return new ServiceResult<Member, ConnexionError>(null, ConnexionError.DATABASE_ERROR);
        }
    }

    /**
     * Inscrit un membre si possible.
     * @param nom nom du membre
     * @param prenom prénom du membre
     * @param mail email du nouveau membre (doit être unique)
     * @param address addresse du nouveau membre. L'API google maps doit pouvoir trouver les coordonées de l'addresse pour que l'inscription ait lieu
     * @return retourne le membre connecté ou un code d'erreur détaillant les raisons de l'echec de l'inscription (OK, EMPTY_FIRSTNAME, EMPTY_ADDRESS,
     * EMPTY_EMAIL, WRONG_ADDRESS, BAD_EMAIL, DATABASE_ERROR ou WRONG_ADDRESS).
     */
    public static ServiceResult<Member, ConnexionError> Inscription(String nom, String prenom, String mail, String address) {
        if(prenom == null || prenom.isEmpty())
            return new ServiceResult<Member, ConnexionError>(null, ConnexionError.EMPTY_FIRSTNAME);
        if(mail == null || mail.isEmpty())
            return new ServiceResult<Member, ConnexionError>(null, ConnexionError.EMPTY_EMAIL);
        if(nom == null || nom.isEmpty())
            return new ServiceResult<Member, ConnexionError>(null, ConnexionError.EMPTY_NAME);
        if(address == null || address.isEmpty())
            return new ServiceResult<Member, ConnexionError>(null, ConnexionError.EMPTY_ADDRESS);

        try {
            LatLng coords = ServiceTechnique.GetLatLngFromAddress(address);
            Member member = new Member(nom, prenom, address, mail, coords);
            JpaUtil.ouvrirTransaction();
            MemberDAL adherent_dao = new MemberDAL();

            try {
                if (adherent_dao.findByMail(mail) != null) {
                    JpaUtil.annulerTransaction();
                    return new ServiceResult<Member, ConnexionError>(null, ConnexionError.BAD_EMAIL);
                }
                adherent_dao.create(member);
                JpaUtil.validerTransaction();
                ServiceTechnique.SendSuccessfullInscriptionMail(member);
                return new ServiceResult<Member, ConnexionError>(member, ConnexionError.OK);
            } catch (Throwable e) {
                ServiceTechnique.SendFailedInscriptionMail(member);
                JpaUtil.annulerTransaction();
                return new ServiceResult<Member, ConnexionError>(null, ConnexionError.DATABASE_ERROR);
            }
        } catch (Exception e) {
            JpaUtil.annulerTransaction();
            return new ServiceResult<Member, ConnexionError>(null, ConnexionError.WRONG_ADDRESS);
        }
    }

    /**
     * Liste les événements d'une date données
     * @param date date, au jour près, à la quelle ont cherche les événements
     * @return la liste des événements ou un code d'erreur détaillant les raison pour les quelles la méthode a échouée (OK, DATABASE_ERROR)
     */
    public static ServiceResult<List<Event>, Request_Error> ListEventsOfDate(Date date) {
        EventDAL event_dao = new EventDAL();
        try {
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findByDate(date), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    /**
     * Liste tout les évenements
     * @return la liste des événements ou un code d'erreur détaillant les raison pour les quelles la méthode a échouée (OK, DATABASE_ERROR)
     */
    public static ServiceResult<List<Event>, Request_Error> ListAllEvents() {
        try {
            EventDAL event_dao = new EventDAL();
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findAll(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    /**
     * Assigne un lieu (location) à un évenement
     * @param location_id id du lieu
     * @param event_id id de l'évenement au quel assigner le lieu
     * @return Un code d'erreur indiquant si l'assignation s'est déroullée correctement (DATABASE_ERROR, WRONG_LIEU_ID, WRONG_EVENT_ID ou OK)
     */
    public static Request_Error AssignLocationToEvent(long location_id, long event_id) {
        try {
            EventDAL event_dao = new EventDAL();
            Event event = event_dao.findById(event_id);
            if (event == null)
                return Request_Error.WRONG_EVENT_ID;

            LocationDAL lieu_dao = new LocationDAL();
            Location location = lieu_dao.findById(location_id);
            if (location == null)
                return Request_Error.WRONG_LIEU_ID;

            JpaUtil.ouvrirTransaction();
            event.setLocation(location);
            event_dao.update(event);
            if (event.getComplet())
                ServiceTechnique.SendEventMail(event);

            JpaUtil.validerTransaction();
            return Request_Error.OK;
        } catch (Throwable e) {
            JpaUtil.annulerTransaction();
            return Request_Error.DATABASE_ERROR;
        }
    }

    /**
     * Methode permettant à un membre de rejoindre un évenement
     * @param member_id id du membre
     * @param event_id id de l'évenement à rejoindre
     * @return Un code d'erreur indiquant si le membre a pû rejoindre l'évenement (DATABASE_ERROR, FULL_EVENT, WRONG_EVENT_ID, WRONG_MEMBER_ID ou OK)
     */
    public static Request_Error JoinEvent(long member_id, long event_id) {
        try {
            EventDAL event_dao = new EventDAL();
            Event event = event_dao.findById(event_id);
            if (event == null)
                return Request_Error.WRONG_EVENT_ID;
            if (event.getComplet())
                return Request_Error.FULL_EVENT;

            MemberDAL member_dao = new MemberDAL();
            Member member = member_dao.findById(member_id);
            if (member == null)
                return Request_Error.WRONG_MEMBER_ID;

            JpaUtil.ouvrirTransaction();
            event_dao.AddAdherentToEvent(event, member);
            if (event.getComplet())
                ServiceTechnique.SendEventMail(event);

            JpaUtil.validerTransaction();
            return Request_Error.OK;
        } catch (Throwable e) {
            JpaUtil.annulerTransaction();
            return Request_Error.DATABASE_ERROR;
        }
    }

    /**
     * Crée un évenement au quel participera son créateur
     * @param member_id id du créateur de l'évenement
     * @param activity_id id de l'activité de l'évenement à creer
     * @param date data à laquelle auras lieu l'evenement
     * @return L'évenement crée ou un code d'erreur (OK, WRONG_ACTIVITY_ID, WRONG_MEMBER_ID ou DATABASE_ERROR)
     */
    public static ServiceResult<Event, Request_Error> CreateEvent(long member_id, long activity_id, Date date) {
        try {
            ActivityDAL activity_dao = new ActivityDAL();
            Activity activity = activity_dao.findById(activity_id);
            if (activity == null)
                return new ServiceResult<Event, Request_Error>(null, Request_Error.WRONG_ACTIVITY_ID);

            MemberDAL member_dao = new MemberDAL();
            Member member = member_dao.findById(member_id);
            if (member == null)
                return new ServiceResult<Event, Request_Error>(null, Request_Error.WRONG_MEMBER_ID);

            JpaUtil.ouvrirTransaction();
            EventDAL event_dao = new EventDAL();
            Event event = new Event(date, activity, member);
            event_dao.create(event);
            JpaUtil.validerTransaction();

            return new ServiceResult<Event, Request_Error>(event, Request_Error.OK);
        } catch (Throwable e) {
            JpaUtil.annulerTransaction();
            return new ServiceResult<Event, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    /**
     * Liste les évenements aux quels participe un membre donné en paramètre
     * @param member_id id du membre
     * @return La liste des évnenements ou un code d'erreur (OK ou DATABASE_ERROR) (renvoie DATABASE_ERROR si l'id du membre est mauvais)
     */
    public static ServiceResult<List<Event>, Request_Error> ListEventsOfMember(long member_id) {
        try {
            EventDAL event_dao = new EventDAL();
            List<Event> events = event_dao.findByMember(member_id);
            return new ServiceResult<List<Event>, Request_Error>(events, Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    /**
     * Liste les évenements qui ne sont pas complets (évenements pouvant acceuillir encore des participants)
     * @return La liste des évnenements ou un code d'erreur (OK ou DATABASE_ERROR)
     */
    public static ServiceResult<List<Event>, Request_Error> ListAvailableEvents() {
        try {
            EventDAL event_dao = new EventDAL();
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findDispo(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    /**
     * Donne la liste des activitées possibles
     * @return La liste de toutes les activitées ou un code d'erreur (OK ou DATABASE_ERROR)
     */
    public static ServiceResult<List<Activity>, Request_Error> ListActivities() {
        try {
            ActivityDAL activity_dao = new ActivityDAL();
            return new ServiceResult<List<Activity>, Request_Error>(activity_dao.findAll(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Activity>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    /**
     * Donne la liste de tout les lieux possibles
     */
    public static ServiceResult<List<Location>, Request_Error> ListLocations() {
        try {
            LocationDAL Location_dao = new LocationDAL();
            return new ServiceResult<List<Location>, Request_Error>(Location_dao.findAll(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Location>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }
}
