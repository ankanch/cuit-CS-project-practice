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
 * 本接口只能使用POST调用，用于向系统提交一条新事件
 *
 * @author kanch
 */
@WebServlet(urlPatterns = {"/SubmitIncident"})
public class SubmitIncident extends HttpServlet {
    
    private IncidentsManager im = new IncidentsManager();

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
            /* TODO output your page here. You may use following sample code. */
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>ERROR</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>METHOD NOT SUPPORT! SubmitIncident at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");
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
        //processRequest(request, response);
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            /* TODO output your page here. You may use following sample code. */
            //获取用户提交的数据
            String latlng = request.getParameter("location");
            String itype = request.getParameter("type");
            String idate = request.getParameter("date");
            String ides = request.getParameter("des");
            //创建事件对象
            Incident ii = new Incident();
            ii.latlng = latlng;
            ii.type = IconStrings.decideType(itype);
            ii.description = ides;
            ii.reportTime = idate;
            //将数据插入数据库
             //返回结果
            if(im.addIncident(ii)){
                  out.println("OK<br/>LOCATION:" + latlng + "<br/>TYPE:" + itype + "<br/>DATE:"+idate + "<br/>DESCRIPTION:" + ides);
            }else{
                  out.println("ERROR<br/>LOCATION:" + latlng + "<br/>TYPE:" + itype + "<br/>DATE:"+idate + "<br/>DESCRIPTION:" + ides);
            }
        }
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
