package TP1_SI.View;

import TP1_SI.Utils.Callable;
import TP1_SI.Utils.ConsoleMenu;
import TP1_SI.Utils.ConsoleUtils;
import TP1_SI.metier.model.Event;
import TP1_SI.metier.model.Location;
import TP1_SI.metier.service.ServiceResult;
import TP1_SI.metier.service.Services;

import java.util.List;

/**
 * Vue de l'administrateur assignat les lieux aux evenements
 * @author B3330
 */
public class ConsoleDashboardView {

    /**
     * Lance la vue
     */
    public void run() {
        ConsoleMenu connexion_menu = new ConsoleMenu("DASHBOARD", new Logout());
        connexion_menu.addChoice(new AssignLocationToEvent(), "Assign location to event");

        connexion_menu.runMenu();
    }

    /**
     * Callback gèrant l'assingation d'un lieu à un evenement
     */
    private static class AssignLocationToEvent implements Callable {
        @Override
        public void call() {
            ServiceResult<List<Event>, Services.Request_Error> events_rslt = Services.ListAllEvents();
            ServiceResult<List<Location>, Services.Request_Error> locations_rslt = Services.ListLocations();

            if(events_rslt.error == Services.Request_Error.OK && locations_rslt.error == Services.Request_Error.OK ) {
                System.out.println("### Liste de tout les évenements ###");
                List<Event> events = events_rslt.result;
                for(int i = 0; i < events.size(); ++i)
                    System.out.println("\t- " + events.get(i));

                System.out.println("\n### Liste de tout les lieux ###");
                List<Location> locations = locations_rslt.result;
                for(int i = 0; i < locations.size(); ++i)
                    System.out.println("\t- " + locations.get(i));

                long event_id = ConsoleUtils.lireInteger("\nEntrez l'id de l'évenement : ");
                long lieu_id = ConsoleUtils.lireInteger("Entrez l'id du lieu : ");

                Services.Request_Error error_code = Services.AssignLocationToEvent(lieu_id, event_id);
                if(error_code == Services.Request_Error.OK)
                    System.out.println("Assignation réussie.");
                else
                    System.out.println("Assignation échouée.");
            }
            else
                // TODO: gèrer l'erreur en fonction de 'events_rslt.error' ou 'locations_rslt.error'
                System.out.println("Erreur lors de l'execution du service : " + (events_rslt.error == Services.Request_Error.OK ? locations_rslt.error : events_rslt.error) );
        }
    }

    /**
     * Callback appelé si l'utilisateur veux retourner à la vue de connexion
     */
    private static class Logout implements Callable {
        @Override
        public void call() {

        }
    }
}
