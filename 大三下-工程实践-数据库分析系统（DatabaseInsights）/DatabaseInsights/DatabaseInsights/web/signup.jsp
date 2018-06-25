<%-- 
    Document   : signup
    Created on : Mar 1, 2018, 1:36:42 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.lang"%>
<%@page import="dbi.localization.langID"%>
<%@page import="dbi.mgr.user.UserManager"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<% // check if user are authorized to visit this page
    UserManager um = new UserManager();
    if (um.validateSession(session.getId())) {
%><jsp:forward page="console.jsp" /> <%
    }
    lang local = lang.detectLang(request);
%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Signup - Database Insights</title>
        <%@ include file="templates/globehead.html" %>
    </head>
    <body>
        <%@ include file="templates/index/indexnav_titleonly.html" %>
        <div class="pt-md-4 pb-md-5">
            <div class="card bg-light mx-auto " style="max-width: 400px;">
                <div class="card-header"><h4>Sign up</h4></div>
                <div class="card-body">
                    <%@ include file="templates/components/form_signup.html" %>
                </div>
            </div>

        </div>
        <footer class="container py-5">
            <%@ include file="templates/index/footer.html" %>
        </footer>

    </body>
</html>