/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.service;

import com.google.maps.GeoApiContext;
import com.google.maps.model.LatLng;
import java.util.List;
import metier.modele.Drone;
import metier.modele.Livreur;
import metier.modele.LivreurCycliste;
import util.GeoTest;
import static util.GeoTest.getFlightDistanceInKm;
import static util.GeoTest.getTripDurationByBicycleInMinute;

/**
 *
 * @author quentinvecchio
 */
public class ServiceTechnique {
    
    public void sendMail(String destinataire, String objet, String corps) {
        System.out.println("Envoie du mail :");
        System.out.println("Dest : " + destinataire);
        System.out.println("Objet : " + objet);
        System.out.println(corps);
    }
    public Livreur findBestLivreur (List <Livreur> livreurs , Double longitude, Double latitude){
        Double TimeMin = Double.MAX_VALUE;
        Livreur nirestLivrer = null; 
        Double currentTime; 
        int i=0;
        for (Livreur currenteLivreur : livreurs){

            LatLng[] step = new LatLng[0];
            LatLng livreurPosition  = new LatLng(currenteLivreur.getLatitude(),currenteLivreur.getLatitude());
            
            // livreur est un drone 
            if (Drone.class == currenteLivreur.getClass()){
                Drone curDrone = (Drone) currenteLivreur;
                currentTime = getFlightDistanceInKm(livreurPosition , new LatLng(latitude,longitude) ) * curDrone.getVitesse();
            }
            
            // livreur est un Cycliste
            else  if (LivreurCycliste.class == currenteLivreur.getClass()){
                currentTime = getTripDurationByBicycleInMinute(livreurPosition ,new LatLng(latitude,longitude), step );
                if(currentTime == null)
                    currentTime = Double.MAX_VALUE;
            } 
            
            //en cas d'érreurs 
            else {
                System.out.println("erreur : ServiceTechnique.findBestLivreur"); //TODO sup 
                currentTime = Double.MAX_VALUE;
            }
            
            //recherche max Val : 
            if (currentTime<TimeMin){
                TimeMin = currentTime; 
                nirestLivrer = currenteLivreur;
            }
            i++;
        }
        return nirestLivrer; 
    }
}
