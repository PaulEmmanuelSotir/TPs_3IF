
import java.util.AbstractList;
import java.util.ArrayList;
import java.util.List;
import metier.modele.Client;
import metier.modele.Commande;
import metier.modele.Restaurant;
import metier.modele.ProduitCommande;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Clients page controller
 *
 * @author B3330
 */
public class ClientPageAction extends ControllerBase {

    public void get_client_by_id(HttpServletRequest request, HttpServletResponse response) {
        try {
            Long id = Long.parseLong(request.getParameter("id"));

            send_json_to_response(response, m_serializer.toJson(m_service.findClientById(id)));
            return;
        } catch (java.lang.NumberFormatException e) {
        }
        send_json_to_response(response, m_serializer.toJson(null));
    }

    public void list_restaurants(HttpServletRequest request, HttpServletResponse response) {
        send_json_to_response(response, m_serializer.toJson(m_service.findAllRestaurant()));
    }

    public void list_products(HttpServletRequest request, HttpServletResponse response) {
        send_json_to_response(response, m_serializer.toJson(m_service.findAllProduit()));
    }

    public void checkout_order(HttpServletRequest request, HttpServletResponse response) {
        try {
            long client_id = Long.parseLong(request.getParameter("client_id"));
            long restaurant_id = Long.parseLong(request.getParameter("restaurant_id"));
            int product_coiunt = Integer.parseInt(request.getParameter("product_count"));

            // Parse product ids list with their quantities
            List<ProduitCommande> ordered_products = new ArrayList(product_coiunt);
            for (int i = 0; i < product_coiunt; ++i) {
                long product_id = Long.parseLong(request.getParameter("order[" + i + "][product_id]"));
                int quantity = Integer.parseInt(request.getParameter("order[" + i + "][quantity]"));
                ordered_products.add(new ProduitCommande(m_service.findProduitById(product_id), quantity));
            }

            Restaurant restaurant = m_service.findRestaurantById(restaurant_id);
            Client client = m_service.findClientById(client_id);
            Commande cmd = new Commande(client, restaurant, ordered_products);

            if (m_service.createCommande(cmd)) {
                send_json_to_response(response, m_serializer.toJson("OK"));
            } else {
                send_json_to_response(response, m_serializer.toJson("ERROR"));
            }
        } catch (java.lang.NumberFormatException e) {
            send_json_to_response(response, m_serializer.toJson("ERROR"));
        }
    }
}
