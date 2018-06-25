/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Apr 23 2018
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

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import dbi.utils.GlobeVar;
import dbi.utils.DBIDataExchange;
import dbi.mgr.user.UserManager;
import dbi.utils.DBIResultSet;
import java.util.ArrayList;

/**
 *
 * @author kanch
 */
@WebServlet(name = "servletGetAutoAnalysisResult", urlPatterns = {"/api/getAutoAnalysisResult"})
public class servletGetAutoAnalysisResult extends HttpServlet {

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
        String database = request.getParameter("dbname");
        String table = request.getParameter("tbname");
        String charttype = request.getParameter("chart");
        DBIResultSet ret = new DBIResultSet();

        int ichttype = Chart.switchChart(charttype);
        if (ichttype > -1) {
            AutoAnalyzer aa = new AutoAnalyzer(GlobeVar.OBJ_MANAGER_USER.getUIDbySessionID(sid), database, table);
            ArrayList<Chart> charts = aa.getAutoCharts(ichttype);
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
            try (PrintWriter out = response.getWriter()) {
                out.println(DBIDataExchange.makeupStatusCode(status, "unknow chart type"));
                return;
            }
        }
        //- | --> ADD YOUR COE ABOVE
        // return status ,you may change to other functions of 
        // DBIDataExchange in order to return data to display frontend
        try (PrintWriter out = response.getWriter()) {
            // return data format, row 1 : charts count
            //                row 2 : charts ID
            //                row 3 : charts options
            if (ret.rowCount() < 1) {
                out.println(DBIDataExchange.makeupStatusCode(status, "selected table can't generate barcharts!"));
            }
            out.println(DBIDataExchange.makeupReturnData(status, "no message", ret.getRows()));
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
