package TP1_SI.metier.service;

import java.sql.Date;
import java.util.List;
import com.google.maps.model.LatLng;

import TP1_SI.DAL.EventDAL;
import TP1_SI.DAL.MemberDAL;
import TP1_SI.DAL.LocationDAL;
import TP1_SI.DAL.ActivityDAL;
import TP1_SI.metier.model.Event;
import TP1_SI.metier.model.Member;
import TP1_SI.metier.model.Activity;
import TP1_SI.metier.model.Location;

/**
 * @author B3330
 */
public class Services {
    public enum ConnexionError {
        OK, EMPTY_NAME, EMPTY_FIRSTNAME, EMPTY_ADDRESS, EMPTY_EMAIL, WRONG_ADDRESS, BAD_EMAIL, DATABASE_ERROR
    }

    public enum Request_Error {
        OK, WRONG_EVENT_ID, WRONG_LIEU_ID, WRONG_ADHERENT_ID, WRONG_ACTIVITY_ID, FULL_EVENT, DATABASE_ERROR
    }

    public ServiceResult<Member, ConnexionError> Connexion(String mail) {
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

    public ServiceResult<Member, ConnexionError> Inscription(String nom, String prenom, String mail, String address) {
        // TODO: verifier si les champs sont vides
        try {
            LatLng coords = ServiceTechnique.GetLatLngFromAddress(address);
            Member member = new Member(nom, prenom, address, mail, coords);
            MemberDAL adherent_dao = new MemberDAL();

            try {
                if (adherent_dao.findByMail(mail) != null) {
                    ServiceTechnique.SendFailedInscriptionMail(member);
                    return new ServiceResult<Member, ConnexionError>(null, ConnexionError.BAD_EMAIL);
                }
                adherent_dao.create(member);
                ServiceTechnique.SendSuccessfullInscriptionMail(member);
                return new ServiceResult<Member, ConnexionError>(member, ConnexionError.OK);
            } catch (Throwable e) {
                ServiceTechnique.SendFailedInscriptionMail(member);
                return new ServiceResult<Member, ConnexionError>(null, ConnexionError.DATABASE_ERROR);
            }
        } catch (Exception e) {
            return new ServiceResult<Member, ConnexionError>(null, ConnexionError.WRONG_ADDRESS);
        }
    }

    public ServiceResult<List<Event>, Request_Error> ListEventsOfDate(Date date) {
        EventDAL event_dao = new EventDAL();
        try {
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findByDate(date), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public ServiceResult<List<Event>, Request_Error> ListAllEvents() {
        try {
            EventDAL event_dao = new EventDAL();
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findAll(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public Request_Error AssignLocationToEvent(int location_id, long event_id) {
        try {
            EventDAL event_dao = new EventDAL();
            Event event = event_dao.findById(event_id);
            if (event == null)
                return Request_Error.WRONG_EVENT_ID;

            LocationDAL lieu_dao = new LocationDAL();
            Location location = lieu_dao.findById(location_id);
            if (location == null)
                return Request_Error.WRONG_LIEU_ID;
            event.setLocation(location);
            if (event.getComplet())
                ServiceTechnique.SendEventMail(event);

            return Request_Error.OK;
        } catch (Throwable e) {
            return Request_Error.DATABASE_ERROR;
        }
    }

    public Request_Error JoinEvent(long member_id, long event_id) {
        try {
            EventDAL event_dao = new EventDAL();
            Event event = event_dao.findById(event_id);
            if (event == null)
                return Request_Error.WRONG_EVENT_ID;
            if (event.getComplet())
                return Request_Error.FULL_EVENT;

            MemberDAL adherent_dao = new MemberDAL();
            Member member = adherent_dao.findById(member_id);
            if (member == null)
                return Request_Error.WRONG_ADHERENT_ID;

            event_dao.AddAdherentToEvent(event, member);
            if (event.getComplet())
                ServiceTechnique.SendEventMail(event);

            return Request_Error.OK;
        } catch (Throwable e) {
            return Request_Error.DATABASE_ERROR;
        }
    }

    public ServiceResult<Event, Request_Error> CreateEvent(long member_id, int activity_id, Date date) {
        try {
            EventDAL event_dao = new EventDAL();
            ActivityDAL activity_dao = new ActivityDAL();
            Activity activity = activity_dao.findById(activity_id);
            if (activity == null)
                return new ServiceResult<Event, Request_Error>(null, Request_Error.WRONG_ACTIVITY_ID);

            MemberDAL adherent_dao = new MemberDAL();
            Member member = adherent_dao.findById(member_id);
            if (member == null)
                return new ServiceResult<Event, Request_Error>(null, Request_Error.WRONG_ADHERENT_ID);

            Event event = new Event(date, activity, member);
            return new ServiceResult<Event, Request_Error>(event, Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<Event, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public ServiceResult<List<Event>, Request_Error> ListEventsOfMember(long member_id) {
        try {
            EventDAL event_dao = new EventDAL();
            List<Event> events = event_dao.findByMember(member_id);
            return new ServiceResult<List<Event>, Request_Error>(events, Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public ServiceResult<List<Event>, Request_Error> ListAvailableEvents() {
        try {
            EventDAL event_dao = new EventDAL();
            return new ServiceResult<List<Event>, Request_Error>(event_dao.findDispo(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Event>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }

    public ServiceResult<List<Activity>, Request_Error> ListActivities() {
        try {
            ActivityDAL activity_dao = new ActivityDAL();
            return new ServiceResult<List<Activity>, Request_Error>(activity_dao.findAll(), Request_Error.OK);
        } catch (Throwable e) {
            return new ServiceResult<List<Activity>, Request_Error>(null, Request_Error.DATABASE_ERROR);
        }
    }
}
