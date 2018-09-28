/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 03 2018
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package dbi.mgr.report;

import dbi.utils.DBIDataExchange;
import dbi.utils.DataValidation;
import dbi.utils.Debug;
import dbi.utils.GlobeVar;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author kanch
 */
@WebServlet(name = "servletGetReport", urlPatterns = {"/getReport"})
public class servletGetReport extends HttpServlet {

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
        Boolean status = false;
        String sid = request.getSession().getId();
        // check if user login first, if not, return error
        if (!GlobeVar.OBJ_MANAGER_USER.validateSession(sid)) {
            try (PrintWriter out = response.getWriter()) {
                out.println(DBIDataExchange.makeupStatusCode(false, " No authentication."));
            }
            return;
        }
        String gtype = request.getParameter("gtype");
        String strrepid = request.getParameter("repid");
        Report rp = new Report();
        String repliststr = "";
        if (DataValidation.containsNULL(gtype)) {   // get 1
            if (!DataValidation.containsNULL(strrepid)) {
                rp = GlobeVar.OBJ_MANAGER_REPORT.getReport(Integer.parseInt(strrepid));
                status = true;
            }
        } else {    // get multi
            ArrayList<Report> rps = GlobeVar.OBJ_MANAGER_REPORT.getUserReportsList(GlobeVar.OBJ_MANAGER_USER.getUIDbySessionID(sid));
            ReportBean rb = new ReportBean();
            repliststr = rb.generateReportTable(rps);
            status = true;
            Debug.log("multi-report.length=", rps.size());
        }

        try (PrintWriter out = response.getWriter()) {
            if (status) {
                if (null == gtype) {
                    out.println(DBIDataExchange.makeupReturnData(status, "success", rp));
                } else {
                    out.println(DBIDataExchange.makeupReturnData(status, "success", repliststr));
                }
            } else {
                out.println(DBIDataExchange.makeupStatusCode(status, "error"));
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
