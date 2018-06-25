<%-- 
    Document   : signin
    Created on : Mar 1, 2018, 9:20:04 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="dbi.localization.lang"%>
<%@page import="dbi.utils.GlobeVar"%>
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
        <title><%=local.getString(langID.JSP_SIGNIN_PAGE_TITLE)  %></title>
        <%@ include file="templates/globehead.html" %>
    </head>
    <body>
        <%@ include file="templates/index/indexnav_titleonly.html" %>
        <div class="pt-md-4 pb-md-5">
            <div class="card bg-light mx-auto " style="max-width: 400px;">
                <div class="card-header"><h4><%=local.getString(langID.JSP_SIGNIN_FORM_TITLE)  %></h4></div>
                <div class="card-body">
                    <form id="form_login">
                        <div class="form-group">
                            <label for="login_email" class="bmd-label-floating"><%=local.getString(langID.JSP_SIGNIN_LABEL_EMAIL)  %></label>
                            <input type="email" required="required" class="form-control" id="login_email" name="username">
                        </div>
                        <div class="form-group">
                            <label for="login_password" class="bmd-label-floating"><%=local.getString(langID.JSP_SIGNIN_LABEL_PASSWORD)  %></label>
                            <input type="password" required="required" class="form-control" id="login_password" name="password">
                        </div>
                        <div class="checkbox pt-md-5 pb-md-4">
                            <label>
                                <input type="checkbox" name="rememberme" onclick="rememberpwd()" id="optionsRadios1" value="option1">
                                <%=local.getString(langID.JSP_SIGNIN_LABEL_REMEMBERME)  %>
                            </label>
                        </div>
                        <button type="button" id="btn_login" onclick="login()" class="btn btn-raised btn-success btn-lg btn-block"><%=local.getString(langID.JSP_SIGNIN_LABEL_LOGIN)  %></button>
                        <button type="button" class="btn btn-link btn-block" onclick="window.location = 'resetpassword.jsp'"><small><%=local.getString(langID.JSP_SIGNIN_LABEL_PROBLEMLOGIN)  %></small></button>
                    </form>
                    <script>
                        $('body').bootstrapMaterialDesign();
                        $("#nav_1").text("Database Insights <%=local.getString(langID.JSP_SIGNIN_JS_NAVTITLE)  %>");
                        var btn = document.getElementById("btn_login");

                        function rememberpwd() {

                        }

                        function login() {
                            btn.disabled = true;
                            SubmitFormFF("/api/login", "form_login", function error(data) {
                                showMsg("<%=local.getString(langID.JSP_SIGNIN_TIP_FAILED)%>");
                                $("#progressbar").hide();
                                btn.disabled = false;
                            }, function success(data) {
                                showMsg("<%=local.getString(langID.JSP_SIGNIN_TIP_SUCCESS)%>");
                                $("#progressbar").hide();
                                window.location = "console.jsp";
                            });
                        }
                    </script>
                </div>
            </div>
        </div>
    </body>
</html>
