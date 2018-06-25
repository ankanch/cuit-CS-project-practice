/*
 * The MIT License
 *
 * *** Copyright © ChengShiyi (Miss Zhang)
 * *** Code created on  五月 03 2018
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

import dbi.db.adaptor.DatabaseHelper;
import dbi.mgr.user.UserManager;
import dbi.utils.DBIDataExchange;
import dbi.utils.DBIResultSet;
import dbi.utils.Debug;
import dbi.utils.GlobeVar;
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
@WebServlet(name = "servletGetTableFields", urlPatterns = {"/api/GetTableFields"})
public class servletGetTableFields extends HttpServlet {

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
        DBIResultSet ret = new DBIResultSet();
        //取出列名和列的类型在一个DBIResultSet中，再根据其具体类型把它分为三类（和主页上的类一致）
        //根据数据库名和表名取出其列的信息，取出列名和类型
        DatabaseHelper helper = new DatabaseHelper(GlobeVar.VAR_DATABASE_CONFIG);
        helper.Connect();
        String[] tables = {"T_DATABASE_COLUMN", "T_DATABASE_TABLE", "T_DATABASE_INFO","T_DI_USER"};
        ret = helper.runJoinSelect("columnname,datatype", tables, " T_DATABASE_COLUMN.tid=T_DATABASE_TABLE.tid "
                + "and T_DATABASE_INFO.did=T_DATABASE_COLUMN.DID and T_DATABASE_COLUMN.USERID=T_DI_USER.USERID "
                + "and tname='"+table+"' and name='"+database+"' "
                + "and T_DI_USER.USESSION='"+sid+"'");
        //根据上面DBIResultSet的内容，生成表，并返回主界面
        String str = "<tr>"
                + "                            <th scope=\"row\" id=\"row_{0}\">{0}</th>"
                + "                            <td  style=\"width: 30%\">"
                + "                                    <input type=\"text\" class=\"form-control\" value=\"{1}\" id=\"field_{0}\">"
                + "                                    <input type=\"text\" value=\"{1}\" id=\"lastfield_{0}\" style=\"display:none;\">"
                + "                            </td>"
                + "                            <td>"
                + "                                <button class=\"btn btn-outline-secondary dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\""
                + "                                aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" id=\"btn_selecttype_{0}\" data-poolf=\"type_text\">文本</button>"
                + "                                <div class=\"dropdown-menu\">"
                + "                                    <a class=\"dropdown-item\" href=\"javascript:chooseNumber({0})\">数字</a>"
                + "                                    <a class=\"dropdown-item\" href=\"javascript:chooseText({0})\">文本</a>"
                + "                                    <a class=\"dropdown-item\" href=\"javascript:chooseBoolean({0})\">布尔值</a>"
                + "                                </div>"
                + "                            </td>"
                + "                            <td id=\"choosetype_{0}\">"
                + "                                <button id=\"buttonnames_{0}\" class=\"btn btn-outline-secondary dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\""
                + "                                     aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf='pf_none'>无</button>"
                + "                                     <div class=\"dropdown-menu\">"
                + "                                         <a class=\"dropdown-item\" href='javascript:' onclick=''choosetypename(this,{0}) '' data-poolf=\"pf_none\">无</a>"
                + "                                         <a class=\"dropdown-item\" href='javascript:' onclick=''choosetypename(this,{0}) '' data-poolf=\"pf_count\">计数</a>"
                + "                                         <a class=\"dropdown-item\" href='javascript:' onclick=''choosetypename(this,{0}) '' data-poolf=\"pf_count_norepeat\">非重复计数</a>"
                + "                                     </div>"
                + "                            </td>"
                + "                            <td>"
                + "                               <input type=\"text\" class=\"form-control\" style=\"width: 80%;\" id=\"instructions_{0}\">"
                + "                            </td>"
                + "                            <td>"
                + "                               <button type=\"button\" id=\"antibutton_{0}\" class=\"btn btn-primary\" onclick=\"disabledcolumn(''{0}'')\">禁用</button>"
                + "                            </td>"
                + "                        </tr>";
        StringBuilder a = new StringBuilder();
        System.out.println("ret.rowCount()" + ret.rowCount());
        for (int i = 1; i <= ret.rowCount(); i++) {
            a.append(MessageFormat.format(str, String.valueOf(i), ret.getData(i, 1)));
        }
        Debug.log(a);
        //- | --> ADD YOUR COE ABOVE
        // return status ,you may change to other functions of 
        // DBIDataExchange in order to return data to display frontend
        try (PrintWriter out = response.getWriter()) {
            if (ret.rowCount() < 1) {
                out.println(DBIDataExchange.makeupStatusCode(status, "No column!"));
            } else {
                status = true;
                out.println(DBIDataExchange.makeupReturnData(status, "the table field is:", a+"***"+ret.rowCount()));
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
