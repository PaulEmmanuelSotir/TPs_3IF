/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;

import com.google.maps.GeoApiContext;
import com.google.maps.GeocodingApi;
import com.google.maps.model.GeocodingResult;
import metier.modele.Drone;
import metier.modele.LivreurCycliste;
import metier.service.Service;

/**
 *
 * @author quentinvecchio
 */
public class testLivreur {
    public static void main(String[] args) {
        Service service = new Service();
        GeoApiContext monGeoApi = new GeoApiContext().setApiKey("AIzaSyDcVVJjfmxsNdbdUYeg9MjQoJJ6THPuap4");
        try {
            GeocodingResult[] results = GeocodingApi.geocode(monGeoApi, "129 Rue Servient, 69003 Lyon").await();
            service.createDrone(new Drone(20.0, results[0].geometry.location.lat, results[0].geometry.location.lng, true, 2000, "admin_drone@gustatif.fr"));
            results = GeocodingApi.geocode(monGeoApi, "129 Rue Servient, 69003 Lyon").await();
            service.createDrone(new Drone(20.0, results[0].geometry.location.lat, results[0].geometry.location.lng, true, 2000, "admin_drone@gustatif.fr"));
            results = GeocodingApi.geocode(monGeoApi, "129 Rue Servient, 69003 Lyon").await();
            service.createDrone(new Drone(20.0, results[0].geometry.location.lat, results[0].geometry.location.lng, true, 2000, "admin_drone@gustatif.fr"));
            results = GeocodingApi.geocode(monGeoApi, "129 Rue Servient, 69003 Lyon").await();
            service.createDrone(new Drone(20.0, results[0].geometry.location.lat, results[0].geometry.location.lng, true, 2000, "admin_drone@gustatif.fr"));
            results = GeocodingApi.geocode(monGeoApi, "129 Rue Servient, 69003 Lyon").await();
            service.createDrone(new Drone(20.0, results[0].geometry.location.lat, results[0].geometry.location.lng, true, 2000, "admin_drone@gustatif.fr"));
            results = GeocodingApi.geocode(monGeoApi, "129 Rue Servient, 69003 Lyon").await();
            service.createDrone(new Drone(20.0, results[0].geometry.location.lat, results[0].geometry.location.lng, true, 2000, "admin_drone@gustatif.fr"));
 
            results = GeocodingApi.geocode(monGeoApi, "26 Rue Louis Blanc, 69006 Lyon").await();
            service.createLivreurCycliste(new LivreurCycliste("Quentn", "Vecchio", "vecchioquentin@hotmail.fr", results[0].geometry.location.lat, results[0].geometry.location.lng, true, 6000));
            results = GeocodingApi.geocode(monGeoApi, "38 Avenue Maréchal de Saxe, 69006 Lyon").await();
            service.createLivreurCycliste(new LivreurCycliste("Henri", "Dupont", "henridupont@hotmail.fr", results[0].geometry.location.lat, results[0].geometry.location.lng, true, 6000));
            results = GeocodingApi.geocode(monGeoApi, "20 Avenue Maréchal de Saxe, 69006 Lyon").await();
            service.createLivreurCycliste(new LivreurCycliste("Martin", "Dupont", "martindupont@hotmail.fr", results[0].geometry.location.lat, results[0].geometry.location.lng, true, 6000));
            results = GeocodingApi.geocode(monGeoApi, "5 Rue du Commandant Faurax, 69006 Lyon").await();
            service.createLivreurCycliste(new LivreurCycliste("Louis", "Durant", "louisdurant@hotmail.fr", results[0].geometry.location.lat, results[0].geometry.location.lng, true, 6000));
            results = GeocodingApi.geocode(monGeoApi, "200 Quai Charles de Gaulle, 69006 Lyon").await();
            service.createLivreurCycliste(new LivreurCycliste("Joseph", "Jacob", "josephjacob@hotmail.fr", results[0].geometry.location.lat, results[0].geometry.location.lng, true, 6000));
        
        } catch(Exception e) {
            System.out.println("Erreur : " + e.getMessage());
        }
    }
}
