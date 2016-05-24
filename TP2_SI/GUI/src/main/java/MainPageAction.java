import metier.modele.Client;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Main page controller
 * @author B3330
 */
public class MainPageAction extends ControllerBase
{
    public void register_client(HttpServletRequest request, HttpServletResponse response) {
        String pseudo = request.getParameter("client[username]");
        if(pseudo != null && !m_service.clientExist(pseudo))
        {
            Client client = new Client();
            client.setPseudo(pseudo);
            client.setPrenom(request.getParameter("client[first_name]"));
            client.setNom(request.getParameter("client[last_name]"));
            client.setPassword(request.getParameter("client[password]"));
            client.setAdresse(request.getParameter("client[postal_address]"));
            client.setMail(request.getParameter("client[email]"));
            client.setTelephone(request.getParameter("client[phone]"));

            m_service.createClient(client);
            client = m_service.connectClient(client.getPseudo(), client.getPassword());

            send_json_to_response(response, m_serializer.toJson(client.getId()));
        }
    }

    public void login_client(HttpServletRequest request, HttpServletResponse response) {
        Client client = m_service.connectClient(request.getParameter("username"), request.getParameter("password"));
        send_json_to_response(response, m_serializer.toJson(client));
    }
}
