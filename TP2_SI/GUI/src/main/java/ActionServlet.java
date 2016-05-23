import javax.servlet.http.*;
import javax.servlet.annotation.*;

/**
 * Main server class (java servlet)
 * @author B3330
 */
@WebServlet(urlPatterns = {"/ActionServlet"})
public class ActionServlet extends HttpServlet {
    
    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     * @param request servlet request
     * @param response servlet response
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response) {
        if(request != null)
        {
            if("register_client".equals(request.getParameter("action")))
                m_main_page_controller.register_client(request, response);
            if("login_client".equals(request.getParameter("action")))
                m_main_page_controller.login_client(request, response);
            if("validateDelivery".equals(request.getParameter("action")))
                m_delivery_page_controller.validateDelivery(request, response);
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Gustatif web service controller servlet";
    }

    private MainPageAction m_main_page_controller = new MainPageAction();
    private DashboardAction m_dashboard_controller= new DashboardAction();
    private ClientPageAction m_client_page_controllerr = new ClientPageAction();
    private DeliveryAction m_delivery_page_controller = new DeliveryAction();
}
