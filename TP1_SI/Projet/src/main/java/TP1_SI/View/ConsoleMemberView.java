package TP1_SI.View;

import TP1_SI.Utils.Callable;
import TP1_SI.Utils.ConsoleMenu;
import TP1_SI.Utils.ConsoleUtils;
import TP1_SI.metier.model.Activity;
import TP1_SI.metier.model.Event;
import TP1_SI.metier.model.Member;
import TP1_SI.metier.service.Services;
import TP1_SI.metier.service.ServiceResult;
import TP1_SI.metier.service.Services.Request_Error;

import java.sql.Date;
import java.util.List;

/**
 * @author B3330
 */
public class ConsoleMemberView {
    public ConsoleMemberView(Member logged_member) {
        this.logged_member = logged_member;
    }

    /**
     * Lance la vue
     */
    public void run() {
        ConsoleMenu connexion_menu = new ConsoleMenu("ESPACE ADHERENT", new Logout());

        connexion_menu.addChoice(new SeeEventsList(), "Voir la liste des événements");
        connexion_menu.addChoice(new CreateEvent(), "Créer un événement");
        connexion_menu.addChoice(new JoinEvent(), "Rejoindre un événement");

        connexion_menu.runMenu();
    }

    /**
     * Callback permettant d'afficher la liste des événements qui ne sont pas complets et la liste des événements aux quels participe le membre courant
     */
    private class SeeEventsList implements Callable {
        @Override
        public void call() {
            ServiceResult<List<Event>, Request_Error> available_events_rslt = Services.ListAvailableEvents();
            ServiceResult<List<Event>, Request_Error> member_events_rslt = Services.ListEventsOfMember(logged_member.getId());

            if(available_events_rslt.error == Request_Error.OK && member_events_rslt.error == Request_Error.OK) {
                System.out.println("### Evenements que vous avez rejoint ###");
                List<Event> member_events = member_events_rslt.result;
                for(int i = 0; i < member_events.size(); ++i)
                    System.out.println("\t- " + member_events.get(i));

                System.out.println("### Evenements disponnibles (pas encore complets) ###");
                List<Event> available_events = available_events_rslt.result;
                for(int i = 0; i < available_events.size(); ++i)
                    System.out.println("\t- " + available_events.get(i));
            }
            else
                // TODO: gèrer l'erreur en fonction de 'available_events_rslt.error' ou 'member_events_rslt.error'
                System.out.println("Erreur lors de l'execution du service : " + (member_events_rslt.error == Request_Error.OK ? available_events_rslt.error : member_events_rslt.error));
        }
    }

    /**
     * Callback permetant au membre de crer un événement
     */
    private class CreateEvent implements Callable {
        @Override
        public void call() {
            System.out.println("### Création d'événement ###");

            // Affiche la liste des activités disponnibles
            ServiceResult<List<Activity>, Request_Error> activities_list_rslt = Services.ListActivities();
            if(activities_list_rslt.error == Request_Error.OK)
            {
                List<Activity> activities = activities_list_rslt.result;
                for(int i = 0; i < activities.size(); ++i)
                    System.out.print((i == 0 ? "\tActivités disponnibles : " : ", \n\t\t") + activities.get(i));
            }
            else
                // TODO: gèrer l'erreur en fonction de 'activities_list_rslt.error'
                System.out.println("Erreur lors de l'execution du service : " + activities_list_rslt.error);

            // Demmande l'activité de l'événement et crée l'évenement
            long activity_id = ConsoleUtils.lireInteger("\nEntrez l'id de l'activité : ");
            Date today = new java.sql.Date((new java.util.Date()).getTime()); // La date de l'évenement est la date actuelle
            ServiceResult<Event, Request_Error> event_creation_rslt = Services.CreateEvent(logged_member.getId(), activity_id, today);

            if(event_creation_rslt.error == Request_Error.OK)
                System.out.println("Evenement créé avec succès : " + event_creation_rslt.result);
            else
                // TODO: gèrer l'erreur en fonction de 'event_creation_rslt.error'
                System.out.println("Erreur lors de l'execution du service : " + event_creation_rslt.error);
        }
    }

    /**
     * Callback permettant au membre de rejoindre un événement
     */
    private class JoinEvent implements Callable {
        @Override
        public void call() {
            long id = ConsoleUtils.lireInteger("Entrez l'id de l'évenement que vous voulez rejoindre : ");

            Request_Error join_event_rslt = Services.JoinEvent(logged_member.getId(), id);

            if(join_event_rslt == Request_Error.OK)
                System.out.println("Evenement rejoint avec succès.");
            else
                // TODO: gèrer l'erreur en fonction de 'join_event_rslt'
                System.out.println("Erreur lors de l'execution du service : " + join_event_rslt);
        }
    }

    /**
     * Callback appelée si l'utilisateur veux se déconnecter (retourner à la vue de connexion)
     */
    private class Logout implements Callable {
        @Override
        public void call() {

        }
    }

    private Member logged_member;
}
