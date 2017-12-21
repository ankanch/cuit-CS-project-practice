<%-- 
    Document   : about
    Created on : Dec 21, 2017, 11:51:31 PM
    Author     : kanch
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>关于Incidents Report</title>
        <link href="https://fonts.googleapis.com/css?family=Inconsolata" rel="stylesheet" type="text/css">
        <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
        <!-- Compiled and minified CSS -->
        <link rel="stylesheet" href="static/materialize/css/bootstrap-material-design.min.css">
        <link rel="stylesheet" href="static/snackbarjs/snackbar.min.css">
        <script src="static/materialize/popper.js"></script>
        <script src="static/jquery-3.2.1.min.js"></script>
        <script src="static/snackbarjs/snackbar.min.js"></script>
        <script charset="utf-8" src="http://map.qq.com/api/js?v=2.exp&key=DPIBZ-OHXKD-A6O4L-HPUN3-ZAAV7-A6B6P"></script>
        <!-- Compiled and minified JavaScript -->
        <script src="static/materialize/js/bootstrap-material-design.min.js"></script>
    </head>
    <body>
        <jsp:include page="template/header.jsp"/>
        <div class="row" >
            <div class="card" style="margin:0 auto;width:80%;margin-top:25px;">
                <h4 class="card-header">关于 Incidents Report 系统</h4>
                <div class="card-body">
                    <h4 class="card-title">此系统</h4>
                    <p class="card-text">With supporting text below as a natural lead-in to additional content.</p>
                    <a href="#" class="btn btn-primary">系统管理员登陆</a>
                    <h4 class="card-title">普通用户</h4>
                    <p class="card-text">With supporting text below as a natural lead-in to additional content.</p>
                    <h4 class="card-title">执法机构</h4>
                    <p class="card-text">各地各级执法机构可以通过本平台方便的将自己的执法历史信息公布于众，增强公众安全意识和机构可信度。</p>
                    <a href="/IncidentsReport/L2AdminLogin.jsp" class="btn btn-primary">执法机构管理员登陆</a>
                </div>
            </div>
        </div>
        <script>
            $(document).ready(function () {
                document.getElementById("nav_about").style.color = "deeppink";
            });
        </script>
    </body>
</html>
