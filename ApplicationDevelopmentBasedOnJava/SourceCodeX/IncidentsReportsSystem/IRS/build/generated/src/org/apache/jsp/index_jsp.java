package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.Connection;
import javax.sql.DataSource;
import javax.naming.InitialContext;

public final class index_jsp extends org.apache.jasper.runtime.HttpJspBase
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
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("<!DOCTYPE html>\n");
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
      out.write("        <div class=\"row\" style=\"margin:0px;height:90vh;\">\n");
      out.write("            <div class=\"col-md-9\">\n");
      out.write("                <div id=\"ttmap\" style=\"width:100%;height:100%;margin:0px;\">\n");
      out.write("\n");
      out.write("                </div>\n");
      out.write("            </div>\n");
      out.write("            <div class=\"col-md-3\">\n");
      out.write("                <form style=\"margin-top:5vh;\">\n");
      out.write("                    <div class=\"form-group\">\n");
      out.write("                        <div class=\"row\" style=\"margin:0vh;margin-top:15px;\">\n");
      out.write("                            <input type=\"text\" class=\"form-control\" id=\"inputLocation\" aria-describedby=\"emailHelp\" placeholder=\"输入街道名称，查看事件情况\" style=\"margin-top:4px; \">\n");
      out.write("                        </div>\n");
      out.write("                        <div class=\"row\" style=\"margin:0vh;margin-top:15px;\">\n");
      out.write("                            <button type=\"button\" class=\"btn btn-primary\" style=\"width:100%;\" onclick=\"search()\" >搜索</button>\n");
      out.write("                        </div>\n");
      out.write("                    </div>\n");
      out.write("                    <div class=\"form-group\">\n");
      out.write("                        <div class=\"row\" style=\"margin: 0vh;\">\n");
      out.write("                            <div class=\"btn-group\">\n");
      out.write("                                <button type=\"button\" class=\"btn btn-info dropdown-toggle\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">\n");
      out.write("                                    按事件类型筛选\n");
      out.write("                                </button>\n");
      out.write("                                <div class=\"dropdown-menu\">\n");
      out.write("                                    <a class=\"dropdown-item\" href=\"#\">显示全部</a>\n");
      out.write("                                    <a class=\"dropdown-item\" href=\"#\">抢劫</a>\n");
      out.write("                                    <a class=\"dropdown-item\" href=\"#\">偷窃</a>\n");
      out.write("                                    <a class=\"dropdown-item\" href=\"#\">欺诈</a>\n");
      out.write("                                    <div class=\"dropdown-divider\"></div>\n");
      out.write("                                    <a class=\"dropdown-item\" href=\"#\">测试</a>\n");
      out.write("                                </div>\n");
      out.write("                            </div>\n");
      out.write("                        </div>\n");
      out.write("\n");
      out.write("                    </div>\n");
      out.write("                    <div class=\"form-group\">\n");
      out.write("                        <div class=\"btn-group\">\n");
      out.write("                            <button type=\"button\" class=\"btn btn-info dropdown-toggle\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">\n");
      out.write("                                按事件发送时间筛选\n");
      out.write("                            </button>\n");
      out.write("                            <div class=\"dropdown-menu\">\n");
      out.write("                                <a class=\"dropdown-item\" href=\"#\">显示最近1年</a>\n");
      out.write("                                <a class=\"dropdown-item\" href=\"#\">最近6个月</a>\n");
      out.write("                                <a class=\"dropdown-item\" href=\"#\">最近3个月</a>\n");
      out.write("                                <a class=\"dropdown-item\" href=\"#\">最近1个月</a>\n");
      out.write("                                <a class=\"dropdown-item\" href=\"#\">最近1周</a>\n");
      out.write("                            </div>\n");
      out.write("                        </div>\n");
      out.write("                    </div>\n");
      out.write("\n");
      out.write("                </form>\n");
      out.write("            </div>\n");
      out.write("        </div>\n");
      out.write("\n");
      out.write("        <script>\n");
      out.write("            //全局控件变量\n");
      out.write("            var inputLocationBox;\n");
      out.write("            var map;\n");
      out.write("\n");
      out.write("            $(document).ready(function () {\n");
      out.write("                //获取所有全局控件变量\n");
      out.write("                inputLocationBox = document.getElementById(\"inputLocation\");\n");
      out.write("                map = new qq.maps.Map(\n");
      out.write("                        document.getElementById(\"ttmap\"),\n");
      out.write("                        {\n");
      out.write("                            center: new qq.maps.LatLng(39.914850, 116.403765),\n");
      out.write("                            zoom: 13\n");
      out.write("                        }\n");
      out.write("                );\n");
      out.write("                //当地图中心属性更改时触发事件\n");
      out.write("                qq.maps.event.addListener(map, 'center_changed', function () {\n");
      out.write("                    console.log(\"latlng:\" + map.getCenter());\n");
      out.write("                });\n");
      out.write("                //绑定单击事件添加参数\n");
      out.write("                qq.maps.event.addListener(map, 'click', function (event) {\n");
      out.write("                    alert('您点击的位置为: [' + event.latLng.getLat() + ', ' +\n");
      out.write("                            event.latLng.getLng() + ']');\n");
      out.write("                });\n");
      out.write("                //地图上的图表\n");
      out.write("                var center = new qq.maps.LatLng(39.916527, 116.397128);\n");
      out.write("                var marker = new qq.maps.Marker({\n");
      out.write("                    position: center,\n");
      out.write("                    map: map,\n");
      out.write("                });\n");
      out.write("                //设置图表位置\n");
      out.write("                var anchor = new qq.maps.Point(39, 39),\n");
      out.write("                        size = new qq.maps.Size(37, 37),\n");
      out.write("                        origin = new qq.maps.Point(0, 0),\n");
      out.write("                        markerIcon = new qq.maps.MarkerImage(\n");
      out.write("                                \"/IncidentsReport/static/icons/car_stolen.png\",\n");
      out.write("                                size,\n");
      out.write("                                origin,\n");
      out.write("                                anchor\n");
      out.write("                                );\n");
      out.write("                marker.setIcon(markerIcon);\n");
      out.write("                //加载当前区域的事件\n");
      out.write("                firstLoading();\n");
      out.write("            });\n");
      out.write("\n");
      out.write("            function decideType(tstr) {\n");
      out.write("                switch (tstr) {\n");
      out.write("                    case \"/IncidentsReport/static/icons/car_stolen\":\n");
      out.write("                        return \"汽车偷窃\";\n");
      out.write("                    case \"/IncidentsReport/static/icons/fire\":\n");
      out.write("                        return \"火灾\";\n");
      out.write("                    case \"/IncidentsReport/static/icons/kidnapping\":\n");
      out.write("                        return \"绑架\";\n");
      out.write("                    case \"/IncidentsReport/static/icons/lie\":\n");
      out.write("                        return \"欺诈\";\n");
      out.write("                    case \"/IncidentsReport/static/icons/robbery\":\n");
      out.write("                        return \"抢劫\";\n");
      out.write("                    case \"/IncidentsReport/static/icons/stolen\":\n");
      out.write("                        return \"入室盗窃\";\n");
      out.write("                    case \"/IncidentsReport/static/icons/violence\":\n");
      out.write("                        return \"暴力事件\";\n");
      out.write("                }\n");
      out.write("                return tstr;\n");
      out.write("            }\n");
      out.write("\n");
      out.write("            function search() {\n");
      out.write("                var loc = inputLocationBox.value;\n");
      out.write("                console.log(\"search location:\" + loc);\n");
      out.write("                if (loc.length < 1) {\n");
      out.write("\n");
      out.write("                    return;\n");
      out.write("                }\n");
      out.write("            }\n");
      out.write("\n");
      out.write("            function getIncidents(vlatlng, vsum) {\n");
      out.write("                $.get(\"/IncidentsReport/getIncidents?latlng=\" + vlatlng + \"&vsum=\" + vsum, function (data) {\n");
      out.write("                    dta = data.split(\"<br/>\");\n");
      out.write("                    incidentstr = dta[1].split(\"$\");\n");
      out.write("                    console.log(incidentstr);\n");
      out.write("                    for (i = 0; i < incidentstr.length; i++) {\n");
      out.write("                        if (incidentstr[i].length > 5) {\n");
      out.write("                            incident = incidentstr[i].split(\"@\");\n");
      out.write("                            ll = incident[4].split(\",\");\n");
      out.write("                            //构造标记位置\n");
      out.write("                            latlng = new qq.maps.LatLng(Number(ll[0]), Number(ll[1]));\n");
      out.write("                            console.log(incident);\n");
      out.write("                            //添加标记\n");
      out.write("                            var marker = new qq.maps.Marker({\n");
      out.write("                                icon: incident[1] + \".png\",\n");
      out.write("                                map: map,\n");
      out.write("                                position: latlng});\n");
      out.write("                            //添加标记点击事件\n");
      out.write("                            //添加到提示窗\n");
      out.write("                            var info = new qq.maps.InfoWindow({\n");
      out.write("                                map: map\n");
      out.write("                            });\n");
      out.write("                            //获取标记的点击事件\n");
      out.write("                            var infocontent = '<div style=\"text-align:left;white-space:nowrap;' +\n");
      out.write("                                    'margin:10px;\">事件类型：@type<br/>' +\n");
      out.write("                                    '发生时间：@time<br/>' +\n");
      out.write("                                    '事件描述：@des<br/>' +\n");
      out.write("                                    '可信度：@credit</div>';\n");
      out.write("                            infocontent = infocontent.replace(\"@type\",decideType(incident[1]))\n");
      out.write("                                                     .replace(\"@time\",incident[6] )\n");
      out.write("                                                     .replace(\"@des\", incident[3])\n");
      out.write("                                                     .replace(\"@credit\", incident[2]);\n");
      out.write("                            qq.maps.event.addListener(marker, 'click', function () {\n");
      out.write("                                info.open();\n");
      out.write("                                info.setContent(infocontent);\n");
      out.write("                                info.setPosition(latlng);\n");
      out.write("                            });\n");
      out.write("                        }\n");
      out.write("                    }\n");
      out.write("                });\n");
      out.write("            }\n");
      out.write("\n");
      out.write("            function firstLoading() {\n");
      out.write("                center = map.getCenter();\n");
      out.write("                getIncidents(center.getLat() + \",\" + center.getLng(), 30);\n");
      out.write("            }\n");
      out.write("        </script>\n");
      out.write("    </body>\n");
      out.write("</html>\n");
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
