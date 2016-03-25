package TP1_SI.metier.service;

import TP1_SI.metier.model.Adherent;
import TP1_SI.metier.model.Event;
import com.google.maps.DistanceMatrixApi;
import static com.google.maps.DistanceMatrixApi.getDistanceMatrix;
import com.google.maps.DistanceMatrixApiRequest;
import com.google.maps.GeoApiContext;
import com.google.maps.GeocodingApi;
import com.google.maps.model.DistanceMatrix;
import com.google.maps.model.GeocodingResult;
import com.google.maps.model.LatLng;
import java.util.List;
import java.util.Properties;
import javax.mail.*;

/**
 * @author B3330
 */
public class ServiceTechnique {
    /*private static final String SMTP_HOST1 = "";
    private static final String LOGIN_SMTP1 = "paul-emmanuel.sotir@insa-lyon.fr";
    private static final String IMAP_ACCOUNT1 = "";*/
    
    public static void SendSuccessfullInscriptionMail(Adherent adherent) { 
        /*Properties properties = new Properties(); 
        properties.setProperty("mail.transport.protocol", "smtp"); 
        properties.setProperty("mail.smtp.host", SMTP_HOST1); 
        properties.setProperty("mail.smtp.user", LOGIN_SMTP1); 
        properties.setProperty("mail.from", IMAP_ACCOUNT1); 
        Session session = Session.getInstance(properties);*/
        String corps =  "Bonjour " + adherent.getPrenom() + ",\n" +
                        "Nous vous confirmons votre adhésion à l'association COLLECT’IF. Votre numéro d'adhérent est : " + adherent.getId();
        System.out.println(corps);

    }
    
     public static void SendFailedInscriptionMail(Adherent adherent) {
        String corps = "Bonjour " + adherent.getPrenom() + ",\n" +
        "Votre adhésion à l'association COLLECT’IF a malencontreusement échoué... Merci de recommencer ultérieurement.";
        
        System.out.println(corps);
     }
     
      public static void SendEventMail(Event event) {
          
          String corps = "";
          LatLng coord = new LatLng(event.getLieu().getLatitude(), event.getLieu().getLongitude());
          
          List<Adherent> adherents = event.getAdherents();
          
          for (int i = 0; i<adherents.size(); i++){
              long distance = 0;
              try
              {
                distance = Distance(coord, new LatLng(adherents.get(i).getLatitude(), adherents.get(i).getLongitude()));
              }
              catch(Exception e)
              {
                  //TODO: gerer ca
              }
            
            corps = "Bonjour" + adherents.get(i).getPrenom() +
            "Comme vous l'aviez souhaité, COLLECT’IF organise un évènement de " + event.getActivite().getDenomination()+ " le " + event.getDate() + ".\n" +
            "Vous trouverez ci-dessous les détails de cet évènement.\n" +
            "Associativement vôtre,\n" +
            "Le Responsable de l'Association\n" +
            "Evénement : " + event.getActivite().getDenomination()+ "\n" +
            "Date : " + event.getDate() + "\n" +
            "Lieu : " + event.getLieu().getDenomination() + ", " + event.getLieu().getAdresse() + "\n" +
            "(à "+ distance + " km de chez vous)\n" +
            "Vous jouerez avec :\n";
             
            if(event.getActivite().isParEquipe()){
                
                List<Adherent> equipe_1 = event.getAdherentsEquipe1();
                for (int j = 0; j<equipe_1.size(); j++) {
                    if(equipe_1.get(j) != adherents.get(i))
                    corps += equipe_1.get(j).getPrenom() + " " +equipe_1.get(j).getNom() + " \n";
                }  
                corps += "Contre :\n";
                
                List<Adherent> equipe_2 = event.getAdherentsEquipe2();
                for (int j = 0; j<equipe_2.size(); j++) {
                    if(equipe_2.get(j) != adherents.get(i))
                    corps += equipe_2.get(j).getPrenom() + " " +equipe_2.get(j).getNom() + " \n";
                }
                  
            }else{
                for (int j = 0; j<adherents.size(); j++) {
                    if(j !=i)
                    corps += adherents.get(j).getPrenom() + " " +adherents.get(j).getNom() + " \n";
                }  
            }       
          }
        System.out.println(corps);  
      }
      
      public static long Distance(LatLng position1, LatLng position2) throws Exception
      {
        GeoApiContext context = new GeoApiContext().setApiKey("AIzaSyDcVVJjfmxsNdbdUYeg9MjQoJJ6THPuap4");
        
        String[] origins = { position1.toUrlValue() };
        String[] dest = { position2.toUrlValue() };
        DistanceMatrix result = getDistanceMatrix(context, origins, dest).await();
        
        return result.rows[0].elements[0].distance.inMeters;
      }
      
    public static LatLng GetLatLngFromAddress(String address) throws Exception
    {
        GeoApiContext context = new GeoApiContext().setApiKey("AIzaSyDcVVJjfmxsNdbdUYeg9MjQoJJ6THPuap4");
        GeocodingResult[] results =  GeocodingApi.geocode(context, address).await();
        return results[0].geometry.location;
    }
}
