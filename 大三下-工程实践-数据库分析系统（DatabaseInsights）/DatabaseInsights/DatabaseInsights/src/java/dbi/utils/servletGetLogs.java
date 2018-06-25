/*
 * The MIT License
 *
 * *** Copyright © ChengShiyi (Miss Zhang)
 * *** Code created on  五月 31 2018
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
package dbi.utils;

import dbi.mgr.user.UserManager;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.MessageFormat;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Miss Zhang
 */
@WebServlet(name = "servletGetLogs", urlPatterns = {"/getLogs"})
public class servletGetLogs extends HttpServlet {

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

        String time = request.getParameter("time");
        String sid = request.getSession().getId();
        UserManager manager = new UserManager();
        String uid = String.valueOf(manager.getUIDbySessionID(sid));
        DBILog log = new DBILog();
        DBIResultSet result = log.searchlog(uid, time);
        String allhtml = "";
        String html = "<tr>\n"
                + "                    <th>{0}</th>\n"
                + "                    <td>{1}</td>\n"
                + "                    <td>{2}</td>\n"
                + "                    <td>{3}</td>\n"
                + "                    <td>{4}</td>\n"
                + "                </tr>";
        System.out.println("result.rowCount():" + result.rowCount());
        for (int i = 1; i <= result.rowCount(); i++) {
            allhtml = allhtml + MessageFormat.format(html, result.getData(i, 4), result.getData(i, 3), result.getData(i, 5),
                     result.getData(i, 6), result.getData(i, 7));
        }
        String div = "<table class=\"table table-striped\">\n"
                + "            <thead>\n"
                + "                <tr>\n"
                + "                    <th scope=\"col\">日志日期</th>\n"
                + "                    <th scope=\"col\">日志类型</th>\n"
                + "                    <th scope=\"col\">相关数据库</th>\n"
                + "                    <th scope=\"col\">相关表</th>\n"
                + "                    <th scope=\"col\">日志内容</th>\n"
                + "                </tr>\n"
                + "            </thead>\n"
                + "            <tbody>{0}\n"
                + "            </tbody>\n"
                + "        </table>";
        String htmlresult = MessageFormat.format(div, allhtml);
        try (PrintWriter out = response.getWriter()) {
            out.println(DBIDataExchange.makeupReturnData(true, "sucess", htmlresult));
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
