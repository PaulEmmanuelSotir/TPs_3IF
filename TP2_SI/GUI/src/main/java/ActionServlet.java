/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
 * @author vchapelle
 */
@WebServlet(urlPatterns = {"/ActionServlet"})
public class ActionServlet extends HttpServlet {

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
            /*Enumeration names = request.getParameterNames();
            
            while(names.hasMoreElements())
            {
                String name = (String)names.nextElement();
                String[] values = request.getParameterValues(name);
                System.out.println("name : " + name + "  , values : " + values);
            }*/
            
            if("gotoRestaurants".equals(request.getParameter("action"))) {
                response.sendRedirect("listeRestaurants.html");
            }
            if("findAllRestaurant".equals(request.getParameter("action"))) {
                response.setContentType("json;charset=UTF-8");
                try (PrintWriter out = response.getWriter()) {
                    out.println("{ restaurants: [");
                    List<Restaurant> rests = service.findAllRestaurant();
                    for(Restaurant r : rests)
                        out.println(r.getId());
                    out.println("] }");
                }
            }
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

}
