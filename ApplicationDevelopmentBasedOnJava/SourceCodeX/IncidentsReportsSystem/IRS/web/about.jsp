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
                    <h4 class="card-title">关于此系统</h4>
                    <p class="card-text">Incident Reports 系统通过建立事件地图，方便广大人民群众及时了解自己身边的各种情况，避开危险和欺诈，同时为广大游客提供留宿/用餐参考，帮助其做出更加有利的决策，另外也可以为政府部门等相关机构的管理决策提供数据，帮助精确管理。
</p>
                    <h4 class="card-title">普通用户</h4>
                    <p class="card-text">对于普通用户，您可以在本站查询某一地区的历史事件发生记录，为自己的行程和活动安排做好相应的规划。同时，您也可以提交事件到本系统，让更多的群众了解到地区事态的发展情况。为社区质量做出贡献。</p>
                    <h4 class="card-title">执法机构</h4>
                    <p class="card-text">各地各级执法机构可以通过本平台方便的将自己的执法历史信息公布于众，增强公众安全意识和机构可信度。</p>
                    <a href="/IncidentsReport/L2AdminLogin.jsp" class="btn btn-primary">管理员登陆</a>
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
