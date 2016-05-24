
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


/**
 * @author B3330
 */
public class DashboardAction extends ControllerBase
{
    public void get_all_restaurants(HttpServletRequest request, HttpServletResponse response) {
        send_json_to_response(response, m_serializer.toJson(m_service.findAllRestaurant()));
    }
    
    public void get_all_clients(HttpServletRequest request, HttpServletResponse response) {
        send_json_to_response(response, m_serializer.toJson(m_service.findAllClient()));
    }
    
    public void get_all_deliveries(HttpServletRequest request, HttpServletResponse response) {
        send_json_to_response(response, m_serializer.toJson(m_service.findAllLivreur()));
    }
}
