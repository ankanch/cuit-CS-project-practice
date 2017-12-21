/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.annotation.WebInitParam;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author kanch
 */
@WebServlet(urlPatterns = {"/getIncidents"}, initParams = {
    @WebInitParam(name = "latlng", value = "0")
    , @WebInitParam(name = "vsum", value = "30")})
public class getIncidents extends HttpServlet {

    private IncidentsManager incidentsManager = new IncidentsManager();

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
            //获取地理位置和显示的个数
            String vloc = request.getParameter("latlng");
            String vsum = request.getParameter("vsum");
            if (vloc == null || vsum == null) {
                out.println("ERROR<br/>");
            } else {
                System.out.println("Retriving...");
                System.out.println(vloc + "," + vsum);
                //
                String result = "";
                ArrayList<Incident> al = incidentsManager.getIncidents(vloc, vsum);
                for (Incident i : al) {
                    result += Integer.toString(i.id) + "@" + i.type + "@" + i.credit + "@"
                            + i.description + "@" + i.latlng  + "@" + i.roughLocation + "@" + i.reportTime + "$";
                }
                out.println("OK<br/>" + result);
                System.out.println("done.");
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
