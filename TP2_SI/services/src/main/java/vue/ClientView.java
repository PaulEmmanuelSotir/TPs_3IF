/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vue;

import dao.JpaUtil;
import java.util.Scanner;
import metier.modele.Client;
import metier.service.Service;

/**
 *
 * @author qvecchio
 */
public class ClientView {
    private final Service service = new Service();
    private final Scanner sc = new Scanner(System.in);
    
    public ClientView() {
        
    }
    
    public Client connection() {
        Client c = null;
        do {
            System.out.println("Entrez votre pseudo : ");
            String name = sc.nextLine();
            if(name.equals("q")) {
                break;
            }
            System.out.println("Entrez votre mot de passe : ");
            String pw = sc.nextLine();
            c = service.connectClient(name, pw);
            if(c == null) {
                System.out.println("Ce client n'existe pas");
            }
        }while(c == null);
        return c;
    }
    
    public void createAccount() {
        Client c = new Client();
        boolean exist;
        do {
            System.out.println("Entrez votre pseudo : ");
            c.setPseudo(sc.nextLine());
            exist = service.clientExist(c.getPseudo());
            if(exist) {
                System.out.println("Le pseudo existe déjà");
            }
        }while(exist);
        System.out.println("Entrez votre mot de passe : ");
        c.setPassword(sc.nextLine());
        System.out.println("Entrez votre prénom : ");
        c.setPrenom(sc.nextLine());
        System.out.println("Entrez votre nom : ");
        c.setNom(sc.nextLine());
        System.out.println("Entrez votre mail : ");
        c.setMail(sc.nextLine());
        System.out.println("Entrez votre adresse : ");
        c.setAdresse(sc.nextLine());
        System.out.println("Entrez votre telephone : ");
        c.setTelephone(sc.nextLine());
        service.createClient(c);
    }
}
