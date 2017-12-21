package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;

public final class submit_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

  private static final JspFactory _jspxFactory = JspFactory.getDefaultFactory();

  private static java.util.List<String> _jspx_dependants;

  private org.glassfish.jsp.api.ResourceInjector _jspx_resourceInjector;

  public java.util.List<String> getDependants() {
    return _jspx_dependants;
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    PageContext pageContext = null;
    HttpSession session = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;

    try {
      response.setContentType("text/html;charset=UTF-8");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, true, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      session = pageContext.getSession();
      out = pageContext.getOut();
      _jspx_out = out;
      _jspx_resourceInjector = (org.glassfish.jsp.api.ResourceInjector) application.getAttribute("com.sun.appserv.jsp.resource.injector");

      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("<!DOCTYPE html>\n");
      out.write("\n");
      out.write("<html>\n");
      out.write("    <head>\n");
      out.write("        <title>Incidents Report</title>\n");
      out.write("        <link href=\"https://fonts.googleapis.com/css?family=Inconsolata\" rel=\"stylesheet\" type=\"text/css\">\n");
      out.write("        <link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\">\n");
      out.write("        <!-- Compiled and minified CSS -->\n");
      out.write("        <link rel=\"stylesheet\" href=\"static/materialize/css/bootstrap-material-design.min.css\">\n");
      out.write("        <link rel=\"stylesheet\" href=\"static/snackbarjs/snackbar.min.css\">\n");
      out.write("        <script src=\"static/materialize/popper.js\"></script>\n");
      out.write("        <script src=\"static/jquery-3.2.1.min.js\"></script>\n");
      out.write("        <script src=\"static/snackbarjs/snackbar.min.js\"></script>\n");
      out.write("        <script charset=\"utf-8\" src=\"http://map.qq.com/api/js?v=2.exp&key=DPIBZ-OHXKD-A6O4L-HPUN3-ZAAV7-A6B6P\"></script>\n");
      out.write("        <!-- Compiled and minified JavaScript -->\n");
      out.write("        <script src=\"static/materialize/js/bootstrap-material-design.min.js\"></script>\n");
      out.write("    </head>\n");
      out.write("    <body>\n");
      out.write("        ");
      org.apache.jasper.runtime.JspRuntimeLibrary.include(request, response, "template/header.jsp", out, false);
      out.write("\n");
      out.write("        <div class=\"container\">\n");
      out.write("            <div class=\"row\" style=\"margin-top:45px;text-align: center;margin: 0 auto;padding-left:12%;\">\n");
      out.write("                要提交一个事件，请首先选择事件发生地点,你可以通过在下方地图中单击来实现地理位置的选择。<br/>\n");
      out.write("                当你开始进行提交事件报告，你就需要保证你提交的事件是真实可靠的，否则你需要对一切你提交的虚假信息负责。\n");
      out.write("            </div>\n");
      out.write("            <div id=\"ttmap\" style=\"width:70%;height:500px;margin:0 auto;margin-top:25px;\">\n");
      out.write("\n");
      out.write("            </div>\n");
      out.write("            <form style=\"width:68%;margin:0 auto;margin-top:15px;margin-bottom:65px;\">\n");
      out.write("                <div class=\"alert alert-danger\" role=\"alert\" >\n");
      out.write("                    \"当前选中位置(LatLng)：\" \n");
      out.write("                    <input type=\"text\" class=\"form-control\" id=\"select_postion\" name=\"location\" placeholder=\"请在地图里面单击选择一个位置\">\n");
      out.write("                </div>\n");
      out.write("                <div class=\"form-group\">\n");
      out.write("                    <label for=\"ides\" class=\"bmd-label-floating\">请在这里输入事件描述</label>\n");
      out.write("                    <textarea class=\"form-control\" id=\"ides\" rows=\"5\"></textarea>\n");
      out.write("                </div>\n");
      out.write("                <div class=\"form-group\">\n");
      out.write("                    <label class=\"mr-sm-2\" for=\"inlineFormCustomSelect\">请选择要报告的事件类型：</label>\n");
      out.write("                    <div class=\"btn-group\">\n");
      out.write("                        <button type=\"button\"  id=\"current_type\" class=\"btn btn-info dropdown-toggle\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">\n");
      out.write("                            选择事件类型\n");
      out.write("                        </button>\n");
      out.write("                        <div class=\"dropdown-menu\">\n");
      out.write("                            <a class=\"dropdown-item\" href=\"javascript:selectIncidentType('汽车偷窃')\">汽车偷窃</a>\n");
      out.write("                            <a class=\"dropdown-item\" href=\"javascript:selectIncidentType('火灾')\">火灾</a>\n");
      out.write("                            <a class=\"dropdown-item\" href=\"javascript:selectIncidentType('入室盗窃')\">入室盗窃</a>\n");
      out.write("                            <a class=\"dropdown-item\" href=\"javascript:selectIncidentType('欺诈')\">欺诈</a>\n");
      out.write("                            <div class=\"dropdown-divider\"></div>\n");
      out.write("                            <a class=\"dropdown-item\" href=\"javascript:selectIncidentType('抢劫')\">抢劫</a>\n");
      out.write("                            <a class=\"dropdown-item\" href=\"javascript:selectIncidentType('绑架')\">绑架</a>\n");
      out.write("                            <a class=\"dropdown-item\" href=\"javascript:selectIncidentType('暴力事件')\">暴力事件</a>\n");
      out.write("                        </div>\n");
      out.write("                    </div>\n");
      out.write("                </div>\n");
      out.write("                <input type=\"text\" class=\"form-control\" id=\"select_type\" name=\"type\" style=\"display:none;\" placeholder=\"请在地图里面单击选择一个位置\">\n");
      out.write("                <div class=\"row\">\n");
      out.write("                    <div class=\"col-md-3\"><label>事件发生时间：</label></div>\n");
      out.write("                    <div class=\"col-md-5\">\n");
      out.write("                        <input type=\"date\" class=\"form-control \" name=\"date\" placeholder=\"请选择事件发生时间\">\n");
      out.write("                    </div>\n");
      out.write("                    \n");
      out.write("                </div>\n");
      out.write("                <div class=\"checkbox\" style=\"margin-top:55px;\">\n");
      out.write("                    <label>\n");
      out.write("                        <input type=\"checkbox\"> 我确定我输入的信息真实可靠\n");
      out.write("                    </label>\n");
      out.write("                </div>\n");
      out.write("                <div class=\"checkbox\">\n");
      out.write("                    <label>\n");
      out.write("                        <input type=\"checkbox\"> 我确认我提交的信息符合《Incidents Report系统信息提交规范》\n");
      out.write("                    </label>\n");
      out.write("                </div>\n");
      out.write("                <div class=\"checkbox\">\n");
      out.write("                    <label>\n");
      out.write("                        <input type=\"checkbox\"> 我确认所报告的事件还没有得到解决\n");
      out.write("                    </label>\n");
      out.write("                </div>\n");
      out.write("                <br/>\n");
      out.write("                <button class=\"btn btn-default\">取消</button>\n");
      out.write("                <button onclick=\"submitIncident()\" class=\"btn btn-primary btn-raised\">提交事件</button>\n");
      out.write("            </form>\n");
      out.write("        </div>\n");
      out.write("\n");
      out.write("        <script>\n");
      out.write("            //全局控件变量\n");
      out.write("            var inputLocationBox;\n");
      out.write("            var map;\n");
      out.write("            var selectPos;\n");
      out.write("\n");
      out.write("            $(document).ready(function () {\n");
      out.write("                //初始化样式\n");
      out.write("                $('body').bootstrapMaterialDesign();\n");
      out.write("                //获取所有全局控件变量\n");
      out.write("                inputLocationBox = document.getElementById(\"inputLocation\");\n");
      out.write("                document.getElementById(\"nav_submit\").style.color = \"deeppink\";\n");
      out.write("                //初始化地图\n");
      out.write("                map = new qq.maps.Map(\n");
      out.write("                        document.getElementById(\"ttmap\"),\n");
      out.write("                        {\n");
      out.write("                            center: new qq.maps.LatLng(39.914850, 116.403765),\n");
      out.write("                            zoom: 13\n");
      out.write("                        }\n");
      out.write("                );\n");
      out.write("                //添加监听事件   获取鼠标单击事件\n");
      out.write("                qq.maps.event.addListener(map, 'click', function (event) {\n");
      out.write("                    selectPos = event.latLng;\n");
      out.write("                    document.getElementById(\"select_postion\").value = selectPos.toString();\n");
      out.write("                    var marker = new qq.maps.Marker({\n");
      out.write("                        position: selectPos,\n");
      out.write("                        map: map\n");
      out.write("                    });\n");
      out.write("                    qq.maps.event.addListener(map, 'click', function (event) {\n");
      out.write("                        marker.setMap(null);\n");
      out.write("                    });\n");
      out.write("                });\n");
      out.write("            });\n");
      out.write("\n");
      out.write("            function selectIncidentType(typex) {\n");
      out.write("                document.getElementById(\"select_type\").value = typex;\n");
      out.write("                document.getElementById(\"current_type\").textContent = typex;\n");
      out.write("            }\n");
      out.write("            \n");
      out.write("            function selCheck(){\n");
      out.write("                return true;\n");
      out.write("            }\n");
      out.write("            \n");
      out.write("            function submitIncident(){\n");
      out.write("                if(selCheck()){\n");
      out.write("                    \n");
      out.write("                }\n");
      out.write("            }\n");
      out.write("        </script>\n");
      out.write("    </body>\n");
      out.write("</html>\n");
      out.write("\n");
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          out.clearBuffer();
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
        else throw new ServletException(t);
      }
    } finally {
      _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }
}
