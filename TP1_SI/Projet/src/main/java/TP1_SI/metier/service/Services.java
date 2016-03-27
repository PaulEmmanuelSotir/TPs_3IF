package TP1_SI.metier.service;

import com.google.maps.model.LatLng;

import TP1_SI.metier.model.Activite;
import TP1_SI.metier.model.Adherent;
import TP1_SI.metier.model.Event;
import TP1_SI.metier.model.Lieu;
import TP1_SI.DAL.ActiviteDao;
import TP1_SI.DAL.AdherentDao;
import TP1_SI.DAL.EventDao;
import TP1_SI.DAL.LieuDao;

import java.sql.Date;
import java.util.List;

/**
 * @author B3330
 */
public class Services {

    public ServiceResult<Adherent, ConnexionError> Connexion(String mail) {
        try {
            AdherentDao adherent_dao = new AdherentDao();
            Adherent adherent = adherent_dao.findByMail(mail);
            if (adherent == null)
                return new ServiceResult<Adherent, ConnexionError>(null, ConnexionError.BAD_EMAIL);
            return new ServiceResult<Adherent, ConnexionError>(adherent, ConnexionError.OK);
        } catch (Throwable e) {
            return new ServiceResult<Adherent, ConnexionError>(null, ConnexionError.DATABASE_ERROR);
        }
    }

    public ServiceResult<Adherent, ConnexionError> Inscription(String nom, String prenom, String mail, String adresse) {

        try {
            LatLng coordonnees = ServiceTechnique.GetLatLngFromAddress(adresse);
            Adherent adherent = new Adherent(nom, prenom, adresse, mail, coordonnees);
            AdherentDao adherent_dao = new AdherentDao();

            try {
                if (adherent_dao.findByMail(mail) != null) {
                    ServiceTechnique.SendFailedInscriptionMail(adherent);
                    return new ServiceResult<Adherent, ConnexionError>(null, ConnexionError.BAD_EMAIL);
                }
                adherent_dao.create(adherent);
                ServiceTechnique.SendSuccessfullInscriptionMail(adherent);
                return new ServiceResult<Adherent, ConnexionError>(adherent, ConnexionError.OK);
            } catch (Throwable e) {
                ServiceTechnique.SendFailedInscriptionMail(adherent);
                return new ServiceResult<Adherent, ConnexionError>(null, ConnexionError.DATABASE_ERROR);
            }
        } catch (Exception e) {
            return new ServiceResult<Adherent, ConnexionError>(null, ConnexionError.WRONG_ADDRESS);
        }
    }

    public ServiceResult<List<Event>, Request_Error> ListeEventDate(Date date) {
        EventDao event_dao = new EventDao();
        try {
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findByDate(date), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public ServiceResult<List<Event>, Request_Error> ListeEvent() {
        try {
            EventDao event_dao = new EventDao();
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findAll(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public Request_Error AssigneLieu(int lieu_id, long event_id) {
        try {
            EventDao event_dao = new EventDao();
            Event event = event_dao.findById(event_id);
            if (event == null)
                return Request_Error.WRONG_EVENT_ID;

            LieuDao lieu_dao = new LieuDao();
            Lieu lieu = lieu_dao.findById(lieu_id);
            if (lieu == null)
                return Request_Error.WRONG_LIEU_ID;
            event.setLieu(lieu);
            if (event.getComplet())
                ServiceTechnique.SendEventMail(event);

            return Request_Error.OK;
        } catch (Throwable e) {
            return Request_Error.DATABASE_ERROR;
        }
    }

    public Request_Error RejoindreEvent(long adherent_id, long event_id) {
        try {
            EventDao event_dao = new EventDao();
            Event event = event_dao.findById(event_id);
            if (event == null)
                return Request_Error.WRONG_EVENT_ID;
            if (event.getComplet())
                return Request_Error.FULL_EVENT;

            AdherentDao adherent_dao = new AdherentDao();
            Adherent adherent = adherent_dao.findById(adherent_id);
            if (adherent == null)
                return Request_Error.WRONG_ADHERENT_ID;

            event_dao.AddAdherentToEvent(event, adherent);
            if (event.getComplet())
                ServiceTechnique.SendEventMail(event);

            return Request_Error.OK;
        } catch (Throwable e) {
            return Request_Error.DATABASE_ERROR;
        }
    }

    public ServiceResult<Event, Request_Error> CreerEvent(long adherent_id, int activite_id, Date date) {
        try {
            EventDao event_dao = new EventDao();
            ActiviteDao activite_dao = new ActiviteDao();
            Activite activite = activite_dao.findById(activite_id);
            if (activite == null)
                return new ServiceResult<Event, Request_Error>(null, Request_Error.WRONG_ACTIVITE_ID);

            AdherentDao adherent_dao = new AdherentDao();
            Adherent adherent = adherent_dao.findById(adherent_id);
            if (adherent == null)
                return new ServiceResult<Event, Request_Error>(null, Request_Error.WRONG_ADHERENT_ID);

            Event event = new Event(date, activite, adherent);
            return new ServiceResult<Event, Request_Error>(event, Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<Event, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }

    }

    public ServiceResult<List<Event>, Request_Error> ListeEventAdherent(long adherent_id) {
        try {
            EventDao event_dao = new EventDao();
            List<Event> liste = event_dao.findByAdherent(adherent_id);
            return new ServiceResult<List<Event>, Request_Error>(liste, Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public ServiceResult<List<Event>, Request_Error> ListeEventDispo() {
        try {
            EventDao event_dao = new EventDao();
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findDispo(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public ServiceResult<List<Activite>, Request_Error> ListeActivite() {
        try {
            ActiviteDao activite_dao = new ActiviteDao();
            return new ServiceResult<List<Activite>, Request_Error>(activite_dao.findAll(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Activite>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }


    public enum ConnexionError {
        OK, EMPTY_NAME, EMPTY_FIRSTNAME, EMPTY_ADDRESS, EMPTY_EMAIL, WRONG_ADDRESS, BAD_EMAIL, DATABASE_ERROR
    }

    public enum Request_Error {
        OK, WRONG_EVENT_ID, WRONG_LIEU_ID, WRONG_ADHERENT_ID, WRONG_ACTIVITE_ID, FULL_EVENT, DATABASE_ERROR
    }
}
