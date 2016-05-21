import com.google.gson.Gson;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import metier.modele.Client;
import metier.modele.Commande;
import metier.service.Service;

/**
 *
 * @author B3330
 */
public class DeliveryAction {
    
    enum status {OK, ERREUR};
    
    public DeliveryAction() {
        m_service = new Service();
        
    }
    
    @SuppressWarnings("empty-statement")
    public void validateDelivery(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        Commande commande = m_service.valideCommande(request.getParameter("email"),Long.parseLong(request.getParameter("num")));
        Gson gson = new Gson();
        
        if (commande == null){
            String json = gson.toJson(status.ERREUR);
            try (PrintWriter out = response.getWriter()) {
            out.println(json);
            }
        } else {
            String json = gson.toJson(status.OK);
            try (PrintWriter out = response.getWriter()) {
            out.println(json);
            }
        }
        
    }
    private Service m_service;
}
