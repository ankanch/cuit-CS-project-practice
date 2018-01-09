

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author JakeLin
 */
@WebServlet(urlPatterns = {"/updateIncident"})
public class updateIncident extends HttpServlet {

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
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            Incident incident = new Incident(); //事件对象
            
            /* TODO output your page here. You may use following sample code. */
            //显示形式：id---type---time---credit---description---location---lat---lng    (lat,lng)
            incident.id = Integer.parseInt(request.getParameter("incidentID"));
            incident.type  = request.getParameter("type");
            incident.reportTime = request.getParameter("time");
            incident.credit = request.getParameter("credit");
            incident.description = request.getParameter("description");
            incident.roughLocation = request.getParameter("location");
            incident.latlng = request.getParameter("lat") + ", " + request.getParameter("lng");
            incident.reportedby = Integer.parseInt(request.getParameter("reportedby"));
            IncidentsManager incidentsManager = new IncidentsManager(); //事件管理类对象
            if(true == incidentsManager.updateIncident(incident)){
                out.println("OK");
            }
            else{
              out.println("ERROR");              
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
        return "Short description";
    }// </editor-fold>

}
