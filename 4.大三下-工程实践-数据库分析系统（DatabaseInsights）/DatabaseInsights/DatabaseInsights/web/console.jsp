<%-- 
    Document   : console
    Created on : Mar 2, 2018, 5:16:48 PM
    Author     : kanch
--%>

<%@page import="dbi.mgr.user.UserManager"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Console - Database Insights</title>
        <%@ include file="templates/globehead.html" %>
        <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    </head>
    <% // check if user are authorized to visit this page
        UserManager um = new UserManager();
        if (!um.validateSession(session.getId())) {
    %><jsp:forward page="signin.jsp" /> <%
        }
    %>
    <body style="padding-top: 50px;">
        <%@ include file="templates/console/console_nav.jsp" %>
        <div class="container-fluid">
            <div class="row">
                <%@ include file="templates/console/console_nav_side.jsp" %>

                <main class="col-sm-9 offset-sm-3 col-md-10 offset-md-2 pt-3 bg-light">
                    <div id="dbimc" style="padding-bottom:70px;">
                    </div>
                    <footer class="sticky-footer">
                        <div class="effects">
                            <%@ include file="templates/console/console_footer.jsp" %>
                        </div>
                    </footer>
                </main>
            </div>
        </div>
        <script>
            $(document).ready(function () {
                $("a.nav-link").on("click", function () {
                    if ($(this).hasClass("active")) {
                        return;
                    }
                    $("a.nav-link").removeClass("active");
                    $(this).addClass("active");
                    $("i.material-icons").removeClass("orange600");
                    $(this).find(".material-icons").addClass("orange600");
                    showMsg("loading...");
                    loadJsp('dbimc', this.dataset.url);
                });
                loadJsp('dbimc', '/templates/console/overview');
            });
        </script>
    </body>
</html>
