import com.google.gson.Gson;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import metier.modele.Client;
import metier.modele.Restaurant;
import metier.service.Service;

/**
 *
 * @author B3330
 */
public class MainPageAction {
    public MainPageAction() {
        m_service = new Service();
    }
    
    public void createClient(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        response.setContentType("json;charset=UTF-8");

        Client client = new Client();
        client.setNom(request.getParameter("nom"));
        client.setPseudo(request.getParameter("pseudo"));
        client.setPrenom(request.getParameter("prenom"));
        client.setAdresse(request.getParameter("adresse"));
        client.setMail(request.getParameter("email"));
        client.setTelephone(request.getParameter("phone"));
        client.setPassword(request.getParameter("password1"));
        
        m_service.createClient(client);
        client = m_service.connectClient(client.getPseudo(), client.getPassword());
        
        Gson gson = new Gson();
        String json = gson.toJson(client.getId());

        try (PrintWriter out = response.getWriter()) {
            out.println(json);
        }
    }
    
    public void connectClient(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        Client client = m_service.connectClient(request.getParameter("pseudo"), request.getParameter("password"));
        
        Gson gson = new Gson();
        String json = gson.toJson(client);

        try (PrintWriter out = response.getWriter()) {
            out.println(json);
        }
    }
    
    private Service m_service;
}
