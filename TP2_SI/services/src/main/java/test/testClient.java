/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;

import metier.modele.Client;
import metier.service.Service;

/**
 *
 * @author quentinvecchio
 */
public class testClient {
    public static void main(String[] args) {
        Service service = new Service();
        Client c = new Client("Quentin", "Quentin", "Vecchio", "Quentin", "20 Avenue Albert Einstein Villeurbanne 69100", "vecchioquentin@hotmail;fr", "0689626235");
        service.createClient(c);
    }
}
