<%-- 
    Document   : overview.jsp
    Created on : Mar 4, 2018, 7:08:43 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="java.util.ArrayList"%>
<%@page import="dbi.utils.GlobeVar"%>
<%@page import="dbi.utils.DBILog"%>
<%@page import="dbi.utils.DBIResultSet"%>
<%@page import="dbi.localization.lang"%>
<%@page import="java.util.HashMap"%>
<%@page import="dbi.mgr.user.UserManager"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%
    UserManager um1 = new UserManager();
    HashMap<String, String> hm = um1.getUserInfo(lang.detectLang(request), session.getId());
    String databaseHtml = "";
    lang local = lang.detectLang(request);
%>
<div class="row">
    <div class="col-md-6">
        <div class="card">
            <div class="card-header">
                <h5><font size="5"><%=local.getString(langID.JSP_OVERVIEW_CONSOLE_ACCOUNTINFO_TITLE)%></font></h5>
            </div>

            <div class="card-body">
                <p><%=local.getString(langID.JSP_OVERVIEW_CONSOLE_TIP_WELCOME)%><b><%= hm.get("USERNAME")%></b> !</p>
                <p><%=local.getString(langID.JSP_OVERVIEW_CONSOLE_TIP_LASTLOGIN)%><b><%=hm.get("LASTLOGIN")%></b></p>
            </div>
        </div>
    </div>
    <div class="col-md-6">
        <div class="card" >
            <div class="card-header">
                <h5><font size="5"><%=local.getString(langID.JSP_OVERVIEW_CONSOLE_DATABASEINFO_TITLE)%></font></h5>
            </div>
            <div class="card-body">
                <%
                    StringBuilder a = new StringBuilder();
                    String html = "<div class=\"d-flex w-100 justify-content-between\">"
                            + "<h5 class=\"mb-1\">%s</h5>"
                            + "<small class=\"text-muted\">3 days ago</small>"
                            + "</div>"
                            + "<p class=\"mb-1\">%s</p>";
                    DBIResultSet database = um1.getUserDatabases(session.getId());
                    DBIResultSet databasehost = um1.getUserDatabasehost(session.getId());
                    for (int i = 0; i < database.rowCount(); i++) {
                        a.append(String.format(html, database.getRow(i + 1).get(0), databasehost.getRow(i + 1).get(0)));
                    }
                    databaseHtml = a.toString();
                %>
                <%=databaseHtml%>
            </div>
        </div>
    </div>
</div>    
<div class="row mt-3">
    <div class="col-md-5">
        <div class="card" >
            <div class="card-header">
                <h5><font size="5"><%=local.getString(langID.JSP_OVERVIEW_CONSOLE_NEWS_TITLE)%></font></h5>
            </div>
            <div class="card-body">
                <div class="list-group">
                    <a href="#" class="list-group-item list-group-item-action flex-column align-items-start">
                        <div class="d-flex w-100 justify-content-between">
                            <h5 class="mb-1">Database Insights v1.0 is online</h5>
                            <small>3 days ago</small>
                        </div>
                        <p class="mb-1">After works on days and nights, exciting to announce Database Insights has now been out for use. The ...</p>
                        <small>click to read more.</small>
                    </a>
                    <a href="#" class="list-group-item list-group-item-action flex-column align-items-start">
                        <div class="d-flex w-100 justify-content-between">
                            <h5 class="mb-1">Introduce analysis report!</h5>
                            <small class="text-muted">1 week ago</small>
                        </div>
                        <p class="mb-1">We are happy to introduce a new function of Database Insights : Report System, which helps you ...</p>
                        <small class="text-muted">click to read more.</small>
                    </a>
                    <a href="#" class="list-group-item list-group-item-action flex-column align-items-start">
                        <div class="d-flex w-100 justify-content-between">
                            <h5 class="mb-1">Project landed.</h5>
                            <small class="text-muted">2 month ago</small>
                        </div>
                        <p class="mb-1">Donec id elit non mi porta gravida at eget metus. Maecenas sed diam eget risus varius blandit.</p>
                        <small class="text-muted">click to read more.</small>
                    </a>
                </div>
            </div>
        </div>
    </div>
    <div class="col-md-7">
        <div class="card">
            <div class="card-header">
                <h5><font size="5"><%=local.getString(langID.JSP_OVERVIEW_CONSOLE_RECENTACT_TITLE)%></font></h5>
            </div>
            <div class="card-body">
                <div class="list-group">
                    <%
                        DBILog dbilog = new DBILog();
                        DBIResultSet dbirs = dbilog.getRecentLog(session.getId());
                        if (dbirs == null || dbirs.rowCount() == 0) {
                    %>
                    <%=local.getString(langID.JSP_OVERVIEW_CONSOLE_TIP_NORECENT)%>
                    <%
                    } else {
                        for (ArrayList<Object> row : dbirs.getRows()) {
                    %>
                    <a href="#" class="list-group-item list-group-item-action flex-column align-items-start">
                        <div class="d-flex w-100 justify-content-between">
                            <small><%=row.get(3)%></small>
                        </div>
                        <p class="mb-1"><%=row.get(6)%></p>
                        <small><%=row.get(4) + "->" + row.get(5)%></small>
                    </a>
                    <%
                            }
                        }
                    %>
                </div>
            </div>
        </div>
    </div>
</div>


<script>
</script>