<%-- 
    Document   : console_nav
    Created on : Apr 2, 2018, 9:26:05 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.lang"%>
<%@page import="java.util.HashMap"%>
<%@page import="dbi.mgr.user.UserManager"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%
    UserManager um1 = new UserManager();
    HashMap<String, String> hm = um1.getUserInfo(lang.detectLang(request),session.getId());

%>
<nav class="navbar navbar-dark bg-primary navbar-expand-lg  fixed-top">
    <a class="navbar-brand" href="#">
        <img src="/static/img/logo/logo.png" width="30" height="30" class="d-inline-block align-top" alt="">
        Database Insights
    </a>
    <ul class="navbar-nav">
        <li class="nav-item dropdown">
            <a class="nav-link dropdown-toggle" href="#" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                <%= hm.get("USERNAME")%>
            </a>
            <div class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">
                <a class="dropdown-item" href="#">Account Settings</a>
                <a class="dropdown-item" href="#">Another action</a>
                <a class="dropdown-item" href="javascript:signout()">Sign out</a>
            </div>
        </li>
    </ul>
    <div class="collapse navbar-collapse justify-content-end" id="navbarNavDropdown">
        <ul class="navbar-nav">
            <li class="nav-item">
                <a class="nav-link" href="#">Help</a>
            </li>
        </ul>
    </div>
</nav>
<script>
    function signout() {
        SubmitFormKVF("/urlmap", {target : "console-user-signout" }, function error(data) {
            showMsg("Failed to signout, network error!");
        }, function success(data) {
            showMsg("You are signed out now!");
            window.location = "signin.jsp";
        });
    }
</script>
