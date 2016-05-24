import com.google.gson.Gson;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.http.HttpServletResponse;
import metier.service.Service;

/**
 * Base class of all controllers/actions scheduled by ActionServlet class
 * @author B3330
 */
public class ControllerBase
{
    protected void send_json_to_response(HttpServletResponse response, String data) {
        print_json_header(response);
        append_json_to_response(response, data);
    }
    
    protected void print_json_header(HttpServletResponse response) {
        response.setContentType("application/json");
        response.setHeader("Access-Control-Allow-Origin", "*");
    }
    
    protected void append_json_to_response(HttpServletResponse response, String data) {
        try {
            PrintWriter out = response.getWriter();
            out.println(data);
            out.flush();
        } catch (IOException e) {
            // TODO: handle exception: Failed to get response writer
        }
    }

    protected Gson m_serializer = new Gson();
    protected Service m_service = new Service();
}
