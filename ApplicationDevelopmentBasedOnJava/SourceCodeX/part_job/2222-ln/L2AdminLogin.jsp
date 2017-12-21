<%-- 
    Document   : L2AdminLogin
    Created on : 2017-12-21, 19:53:24
    Author     : JakeLin
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>二级管理员登录</title>
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

        <jsp:include page="template/header.jsp"/>
        <script type='text/javascript'>
            $(document).ready(function () {
                $('body').bootstrapMaterialDesign();
            });

            function check() {
                var inputL2AdminID = document.getElementById("inputL2AdminID").value;
                if (inputL2AdminID === null || inputL2AdminID === '') {
                    alert("Please input L2AdminID!");
                    return false;
                }

                var inputL2AdminPassword = document.getElementById("inputL2AdminPassword").value;
                if (inputL2AdminPassword === null || inputL2AdminPassword === '') {
                    alert("Please input inputL2AdminPassword!");
                    return false;
                }
                return true;
            }

            function submitLogin() {
                if (true === check()) {
                    showMsg("提交中...");
                    SubmitForm("/IncidentsReport/validatel2admin", "submit_l2admin", "登陆失败，请检查账号或密码有无错误！", "提交成功！");
                }
            }
        </script>
    </head>

    <body>
        <div class="container">

            <div class="card" style="width: 20rem;margin:0 auto;margin-top:18vh;">
                
                <div class="card-body">
                    <h4 class="card-title">二级管理员登录</h4>
                    <form id="submit_l2admin">
                        <div class="form-group">
                            <label for="exampleInputEmail1">二级管理员用户名</label>
                            <input type="text" name="username" class="form-control" id="inputL2AdminID" aria-describedby="emailHelp" placeholder="请输入二级管理员用户名">
                            <small id="emailHelp" class="form-text text-muted"></small>
                        </div>
                        <div class="form-group">
                            <label for="exampleInputPassword1">密码</label>
                            <input type="password" name="password" class="form-control" id="inputL2AdminPassword" placeholder="密码">
                        </div>
                        <div class="form-check">
                            <label class="form-check-label">
                                <input type="checkbox" class="form-check-input">
                                <small>记住密码</small>
                            </label>
                        </div>
                        <a href="javascript:submitLogin()" class="btn btn-primary btn-raised" style="margin-left: 200px">登录</a>
                    </form>
                </div>
            </div>
        </div>

    </body>
</html>
