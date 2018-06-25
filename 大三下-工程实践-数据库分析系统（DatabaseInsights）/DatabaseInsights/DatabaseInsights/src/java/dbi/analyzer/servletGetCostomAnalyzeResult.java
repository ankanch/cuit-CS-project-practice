/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on May 05 2018
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
package dbi.analyzer;

import dbi.mgr.user.UserManager;
import dbi.utils.DBIDataExchange;
import dbi.utils.DBIResultSet;
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
@WebServlet(name = "servletGetCostomAnalyzeResult", urlPatterns = {"/api/getCostomAnalyzeResult"})
public class servletGetCostomAnalyzeResult extends HttpServlet {

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
        UserManager um = GlobeVar.OBJ_MANAGER_USER;
        // check if user login first, if not, return error
        if (!um.validateSession(sid)) {
            try (PrintWriter out = response.getWriter()) {
                out.println(DBIDataExchange.makeupStatusCode(false, " No authentication."));
            }
            return;
        }
        //- | --> ADD YOUR CODE BELOW
        String tname = request.getParameter("tname");
        String lastfields = request.getParameter("lastfields");
        String newfields = request.getParameter("fields");
        String dname= request.getParameter("dbname");
        String type = request.getParameter("type");
        String summary = request.getParameter("summary");
        String instructions = request.getParameter("instructions");
        DBIResultSet ret = new DBIResultSet();
        //Debug.log("parameters=",tname, lastfields, newfields, type, summary, instructions);
        if (!DataValidation.containsNULL(tname, lastfields, newfields, type, summary, instructions)) {
            DBIResultSet jobs = new DBIResultSet();
            String[] lastf = lastfields.split(",");
            String[] newf = newfields.split(",");
            String[] types = type.split(",");
            String[] pools = summary.split(",");
            String[] comments = instructions.split(",");
            for (int i = 0; i < lastf.length; i++) {
                //Debug.log("parse parameters=",lastf[i], newf[i], types[i], pools[i], comments[i]);
                CustomizeJob cj = new CustomizeJob(lastf[i], newf[i], types[i], pools[i], comments[i]);
                jobs.addToRow(cj);
            }
            jobs.finishRow();
            CustomizeAnalyzer ca = new CustomizeAnalyzer(GlobeVar.OBJ_MANAGER_USER.getUIDbySessionID(sid),dname, tname);
            ArrayList<Chart> charts = ca.generateCharts(jobs.toArray1D(CustomizeJob.class));
            ret.addToRow(charts.size());
            ret.finishRow();
            ArrayList<Object> chtids = new ArrayList<>();
            charts.forEach((cht) -> {
                ret.addToRow(cht.toString());
                chtids.add(cht.id);
            });
            ret.addRow(chtids);
            ret.finishRow();
            status = true;
        } else {
            status = false;
        }

        //- | --> ADD YOUR COE ABOVE
        // return status ,you may change to other functions of 
        // DBIDataExchange in order to return data to display frontend
        try (PrintWriter out = response.getWriter()) {
            if (status) {
                out.println(DBIDataExchange.makeupReturnData(status, "charts generated successful:", ret.getRows()));
            }else{
                out.println(DBIDataExchange.makeupStatusCode(status, "error!"));
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
