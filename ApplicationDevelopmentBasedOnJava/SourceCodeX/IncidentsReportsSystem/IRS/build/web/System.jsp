<%-- 
    Document   : System
    Created on : 2017-12-29, 11:03:40
    Author     : JakeLin
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>Incidents Report</title>
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
        <style>
            .wrap{
                width: 150px;white-space: nowrap;text-overflow: ellipsis;overflow: hidden;
                }
        </style>
    </head>
    <body>
        <jsp:include page="template/header.jsp"/>
        <jsp:include page="jsp/incidentManagement.jsp"/>
        <jsp:include page="jsp/l2adminManagement.jsp"/>
        <jsp:include page="jsp/userManagement.jsp"/>
        <div style="margin: 0 1cm 0 1cm;">
            <div class="row">
                <div class="col  jumbotron">
                    <div>
                        <input class="btn btn-secondary btn-lg" type="button" value="二级管理员列表" onclick="showDiv('l2adminsList')"/>
                    </div>
                    <div>  
                        <input id="incidentsList-button" class="btn btn-secondary btn-lg" type="button" value="事件列表" onclick="showDiv('incidentsList')"/>                       
                    </div>
                    <div>
                        <input class="btn btn-secondary btn-lg" type="button" value="订阅用户列表" onclick="showDiv('ordersList')"/>
                    </div>
                    <div>
                        <input class="btn btn-secondary btn-lg" type="button" value="其他事项" onclick="showDiv('fourth')"/>
                    </div>
                </div>
                <div class="col-10">
                    <div style="margin: 20px 10px 10px;padding-left:2%;">
                        <h1 class="display-3">欢迎使用管理系统</h1>
                        <p class="lead">在这里你可以对系统的功能进行修改，或者增添、修改、删除事件的数据</p>
                        <hr class="my-4">
                    </div>
                    <div class="card" style="margin-left:2%;">
                        <div id="l2adminsList">
                            <table class="table table-striped">
                                <thead class="thead-inverse">
                                  <tr>
                                    <th>管理员编号</th>
                                    <th>用户名</th>
                                    <th>密码</th>
                                    <th>状态</th>
                                    <th>操作</th>
                                  </tr>
                                </thead>
                                <tbody id="l2adminsList-tbody">
<!--                                  <tr>
                                    <th scope="row">1</th>
                                    <td>Mark</td>
                                    <td>Otto</td>
                                    <td>1</td>
                                  </tr> -->
                                  <tr>
                                      <th scope="row"><div style="margin-right: 3px" class="wrap" title="1">12134124343fdfsdgfgd6543653456</div></th>
                                    <td><div class="wrap" title="2">markdfsdgfsghgfdgffdgfdgfddgfhhfdhfdh</div></td>
                                    <td><div class="wrap" title="3">4234we423534gfdgfdgfdggfdgfd4534</div></td>
                                    <td><div class="wrap" title="4">12134124343654gdgdffgfd3653456</div></td>
                                    <td><div style="width: 150px;" class="wrap" id="firstButton">
                                               <button type="button" style="margin-right: 5px;height: 30px;" class="btn btn-raised btn-primary" onclick="showButton('Button1')">修改</button>
                                               <button type="button" style="height: 30px" class="btn btn-raised btn-secondary" onclick="showButton('Button2')">删除</button>
                                           </div>
                                           <div style="width: 150px;" class="wrap" id="secondButton">
                                               <button style="margin-right: 5px;height: 30px;" class="btn btn-raised btn-primary" type="button" value="保存" onclick="showButton('Button3')">提交</button>
                                               <button style="height: 30px" class="btn btn-raised btn-secondary" type="button" value="取消" onclick="showButton('Button4')">取消</button>
                                           </div>
                                    </td>
                                  </tr>
                                </tbody>
                              </table>
                            <div>
                                <a class="btn btn-raised btn-primary" style="margin: 10px 0px 20px 70%;" href="javascript:createL2admin()">添加二级管理员</a>
                            </div>
                        </div>
                        
                        <div id="incidentsList">
                             <table class="table table-striped">
                                <thead class="thead-inverse">
                                    <tr id="incidentsList-row">
                                    <th>事件编号</th>
                                    <th>事件类型</th>
                                    <th>发生时间</th>
                                    <th>可信度</th>
                                    <th>事件描述</th>
                                    <th>地点</th>
                                    <th>经度</th>
                                    <th>纬度</th>
                                    <th>操作</th>
                                  </tr>
                                </thead>
                                <tbody id="incidentsList-tbody">
<!--                                    
                                    <tr id="incident-tr-7">
                                    <th scope="row">7</th>
                                    <td>/IncidentsReport/static/icons/car_stolen</td>
                                    <td>2017-12-16 07:41:45.0</td>
                                    <td>11/12</td>
                                    <td>测试事件，事件类型：车辆偷窃。</td>
                                    <td>Beijing</td>
                                    <td>39.37011636082244</td>
                                    <td>116.21114354003907</td>
                                  </tr>  -->
                                  <tr>
                                       <th scope="row"><div style="width: 70px;" class="wrap" title="12134124343fdfsdgfgd6543653456">1</div></th>
                                       <td><div style="width: 70px;" class="wrap" title="/IncidentsReport/static/icons/car_stolen">/IncidentsReport/static/icons/car_stolen</div></td>
                                       <td><div style="width: 70px;" class="wrap" title="3">2017-12-11 07:41:45</div></td>
                                       <td><div style="width: 60px;" class="wrap" title="4">11/12</div></td>
                                       <td><div style="width: 150px;" class="wrap" title="5">测试事件，事件类型：lie欺诈。</div></td>
                                       <td><div style="width: 70px;" class="wrap" title="6">beijing</div></td>
                                       <td><div style="width: 70px;" class="wrap" title="7">39.37011636082244</div></td>
                                       <td><div style="width: 100px;" class="wrap" title="8">116.21114354003907</div></td>
                                       
                                       <td>
                                           <div style="width: 150px;" class="wrap" id="firstButton">
                                               <button type="button" style="margin-right: 5px;height: 30px;" class="btn btn-raised btn-primary" onclick="showButton('secondButton')">修改</button>
                                               <button type="button" style="height: 30px" class="btn btn-raised btn-secondary" onclick="showButton('secondButton')">删除</button>
                                           </div>
                                           <div style="width: 150px;" class="wrap" id="secondButton">
                                               <button style="margin-right: 5px;height: 30px;" class="btn btn-raised btn-primary" type="button" onclick="showButton('firstButton')">提交</button>
                                               <button style="height: 30px" class="btn btn-raised btn-secondary" type="button" value="取消" onclick="showButton('firstButton')">取消</button>
                                           </div>
                                       </td>
                                     </tr>
                                </tbody>
                              </table>
                             <div>
                                <a class="btn btn-raised btn-primary" style="margin: 10px 0px 20px 70%;" href="javascript:createIncident()">添加事件</a>
                            </div>
                        </div>
                        <div id="ordersList">
                             <table class="table table-striped">
                                <thead class="thead-inverse">
                                  <tr>
                                    <th>用户编号</th>
                                    <th>邮箱地址</th>
                                    <th>状态</th>
                                    <th>所在地</th>
                                  </tr>
                                </thead>
                                <tbody id="ordersList-tbody">
                                  <tr>
                                    <th scope="row">1</th>
                                    <td>test1@qq.com</td>
                                    <td>1</td>
                                    <td>Chengdu</td>
                                  </tr>                           
                                </tbody>
                              </table>
                        </div>
                        <div id="fourth" style="padding-left:1%;">
                        </div>
                    </div>
                </div>
            </div>
        </div>
        
        <script>
            var l2adminID = 1;
            
            $(document).ready(function () {
                
                $('body').bootstrapMaterialDesign();
                showDiv('incidentsList');
                showButton('firstButton');
                hiddenButton("secondButton");
                l2adminID = localStorage.getItem("l2adminID");
                console.log(l2adminID);
                
            });
            
            function  showDiv(name){
                if("l2adminsList"===name){
                    document.getElementById(name).style.display="block";
                    document.getElementById("incidentsList").style.display="none";
                    document.getElementById("ordersList").style.display="none";
                    document.getElementById("fourth").style.display="none";
                    getL2admin();
                }
                if("incidentsList"===name){
                    document.getElementById(name).style.display="block";
                    document.getElementById("l2adminsList").style.display="none";
                    document.getElementById("ordersList").style.display="none";
                    document.getElementById("fourth").style.display="none";
                    getIncidents(l2adminID, 50);
                }
                if("ordersList"===name){
                    document.getElementById(name).style.display="block";
                    document.getElementById("l2adminsList").style.display="none";
                    document.getElementById("incidentsList").style.display="none";
                    document.getElementById("fourth").style.display="none";
                    getUsers();
                  
                }
                if("fourth"===name){
                    document.getElementById(name).style.display="block";
                    document.getElementById("l2adminsList").style.display="none";
                    document.getElementById("incidentsList").style.display="none";
                    document.getElementById("ordersList").style.display="none";
                }
             }
             
             function showButton(id){
                    document.getElementById(id).style.display="block";
                    
             }
             function hiddenButton(id){
                 document.getElementById(id).style.display="none";
             }
            
    </script>
    
    
</html>