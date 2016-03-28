package TP1_SI.metier.service;

import TP1_SI.metier.model.Member;
import TP1_SI.metier.model.Event;

import com.google.maps.DistanceMatrixApi;
import com.google.maps.GeoApiContext;
import com.google.maps.GeocodingApi;
import com.google.maps.model.DistanceMatrix;
import com.google.maps.model.GeocodingResult;
import com.google.maps.model.LatLng;

import java.util.List;

/**
 * @author B3330
 */
public class ServiceTechnique {

    /*private static final String SMTP_HOST1 = "";
    private static final String LOGIN_SMTP1 = "paul-emmanuel.sotir@insa-lyon.fr";
    private static final String IMAP_ACCOUNT1 = "";*/
    private static final String GeoAPIKey = "AIzaSyDcVVJjfmxsNdbdUYeg9MjQoJJ6THPuap4";

    public static void SendSuccessfullInscriptionMail(Member member) {
        /*Properties properties = new Properties(); 
        properties.setProperty("mail.transport.protocol", "smtp"); 
        properties.setProperty("mail.smtp.host", SMTP_HOST1); 
        properties.setProperty("mail.smtp.user", LOGIN_SMTP1); 
        properties.setProperty("mail.from", IMAP_ACCOUNT1); 
        Session session = Session.getInstance(properties);*/
        String corps = "Bonjour " + member.getPrenom() + ",\n" +
                "Nous vous confirmons votre adhésion à l'association COLLECT’IF. Votre numéro d'adhérent est : " + member.getId();

        System.out.println(corps);
    }

    public static void SendFailedInscriptionMail(Member member) {
        String corps = "Bonjour " + member.getPrenom() + ",\n" +
                "Votre adhésion à l'association COLLECT’IF a malencontreusement échoué... Merci de recommencer ultérieurement.";

        System.out.println(corps);
    }

    public static void SendEventMail(Event event) {
        final LatLng coord = new LatLng(event.getLocation().getLatitude(), event.getLocation().getLongitude());
        List<Member> members = event.getMembers();

        for (int i = 0; i < members.size(); i++) {
            try {
                long distance = Distance(coord, new LatLng(members.get(i).getLatitude(), members.get(i).getLongitude()));

                String corps = "Bonjour" + members.get(i).getPrenom() + ",\n" +
                        "Comme vous l'aviez souhaité, COLLECT’IF organise un évènement de " + event.getActivity().getName() + " le " + event.getDate() + ".\n" +
                        "Vous trouverez ci-dessous les détails de cet évènement.\n" +
                        "Associativement vôtre,\n" +
                        "Le Responsable de l'Association\n" +
                        "Evénement : " + event.getActivity().getName() + "\n" +
                        "Date : " + event.getDate() + "\n" +
                        "Location : " + event.getLocation().getDenomination() + ", " + event.getLocation().getAddress() + "\n" +
                        "(à " + distance + " km de chez vous)\n" +
                        "Vous jouerez avec :\n";
                if (event.getActivity().isByTeam()) {
                    List<Member> equipe_1 = event.getAdherentsEquipe1();
                    for (int j = 0; j < equipe_1.size(); j++) {
                        if (equipe_1.get(j) != members.get(i))
                            corps += equipe_1.get(j).getPrenom() + " " + equipe_1.get(j).getNom() + "\n";
                    }
                    corps += "Contre :\n";

                    List<Member> equipe_2 = event.getAdherentsEquipe2();
                    for (int j = 0; j < equipe_2.size(); j++) {
                        if (equipe_2.get(j) != members.get(i))
                            corps += equipe_2.get(j).getPrenom() + " " + equipe_2.get(j).getNom() + "\n";
                    }

                } else {
                    for (int j = 0; j < members.size(); j++) {
                        if (j != i)
                            corps += members.get(j).getPrenom() + " " + members.get(j).getNom() + "\n";
                    }
                }

                // TODO: afficher plus d'infos avec une mise en forme
                System.out.println(corps);
            } catch (Exception e) {
                //TODO: gerer ca
            }
        }
    }

    public static long Distance(LatLng position1, LatLng position2) throws Exception {
        GeoApiContext context = new GeoApiContext().setApiKey(GeoAPIKey);

        String[] origins = {position1.toUrlValue()};
        String[] dest = {position2.toUrlValue()};
        DistanceMatrix result = DistanceMatrixApi.getDistanceMatrix(context, origins, dest).await();

        return result.rows[0].elements[0].distance.inMeters;
    }

    public static LatLng GetLatLngFromAddress(String address) throws Exception {
        GeoApiContext context = new GeoApiContext().setApiKey(GeoAPIKey);
        GeocodingResult[] results = GeocodingApi.geocode(context, address).await();

        return results[0].geometry.location;
    }
}
