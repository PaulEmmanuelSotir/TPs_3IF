import metier.modele.Commande;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Dashboard page controller
 * @author B3330
 */
public class DeliveryAction extends ControllerBase
{
    enum status {OK, ERREUR};
    
    public void validateDelivery(HttpServletRequest request, HttpServletResponse response)
    {
        try
        {
            Commande commande = m_service.valideCommande(request.getParameter("email"), Long.parseLong(request.getParameter("num")));

            if (commande != null) {
                send_json_to_response(response, m_serializer.toJson(status.OK));
                return;
            }
        }
        catch(java.lang.NumberFormatException e) { }
        send_json_to_response(response, m_serializer.toJson(status.ERREUR));
    }
}
