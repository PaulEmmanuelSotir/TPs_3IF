import com.google.gson.Gson;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.annotation.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import metier.modele.Restaurant;
import metier.service.Service;

/**
 *
 * @author B3330
 */
@WebServlet(urlPatterns = {"/ActionServlet"})
public class ActionServlet extends HttpServlet {
    /**
     * Constructor
     */
    public ActionServlet()
    {
         m_main_page_controller = new MainPageAction();
         m_dashboard_controller = new DashboardAction();
         m_client_page_controller = new ClientPageAction();
         m_delivery_page_controller = new DeliveryAction();
    }

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Service service = new Service();
        
        if(request != null)
        {
            if("findRestaurantById".equals(request.getParameter("action"))) {
                response.setContentType("json;charset=UTF-8");
                
                Restaurant rest = service.findRestaurantById(Long.parseLong(request.getParameter("id")));
                Gson gson = new Gson();
                String json = gson.toJson(rest);
                
                try (PrintWriter out = response.getWriter()) {
                    out.println(json);
                }
            }
            if("createClient".equals(request.getParameter("action")))
                m_main_page_controller.createClient(request, response);
            if("connectClient".equals(request.getParameter("action")))
                m_main_page_controller.connectClient(request, response);
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Gustatif web service controller servlet";
    }

    private MainPageAction m_main_page_controller;
    private DashboardAction m_dashboard_controller;
    private ClientPageAction m_client_page_controller;
    private DeliveryAction m_delivery_page_controller;
}
