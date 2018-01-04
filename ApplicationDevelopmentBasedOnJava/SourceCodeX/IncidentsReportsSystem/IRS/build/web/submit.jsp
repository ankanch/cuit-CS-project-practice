<%-- 
    Document   : submit
    Created on : Dec 18, 2017, 12:19:13 PM
    Author     : kanch
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
    </head>
    <body>
        <jsp:include page="template/header.jsp"/>
        <div class="container">
            <div class="row" style="margin-top:45px;text-align: center;margin: 0 auto;padding-left:12%;">
                要提交一个事件，请首先选择事件发生地点,你可以通过在下方地图中单击来实现地理位置的选择。<br/>
                当你开始进行提交事件报告，你就需要保证你提交的事件是真实可靠的，否则你需要对一切你提交的虚假信息负责。
            </div>
            <div id="ttmap" style="width:70%;height:500px;margin:0 auto;margin-top:25px;">

            </div>
            <form style="width:68%;margin:0 auto;margin-top:15px;margin-bottom:65px;" id="submit_incident">
                <div class="alert alert-danger" role="alert" >
                    当前选中位置(LatLng)：
                    <input type="text" class="form-control" id="select_postion" name="location" placeholder="请在地图里面单击选择一个位置">
                </div>
                <div class="form-group">
                    <label for="ides" class="bmd-label-floating">请在这里输入事件描述</label>
                    <textarea class="form-control" id="ides" rows="5" name="des"></textarea>
                </div>
                <div class="form-group">
                    <label class="mr-sm-2" for="inlineFormCustomSelect">请选择要报告的事件类型：</label>
                    <div class="btn-group">
                        <button type="button"  id="current_type" class="btn btn-info dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                            选择事件类型
                        </button>
                        <div class="dropdown-menu">
                            <a class="dropdown-item" href="javascript:selectIncidentType('汽车偷窃')">汽车偷窃</a>
                            <a class="dropdown-item" href="javascript:selectIncidentType('火灾')">火灾</a>
                            <a class="dropdown-item" href="javascript:selectIncidentType('入室盗窃')">入室盗窃</a>
                            <a class="dropdown-item" href="javascript:selectIncidentType('欺诈')">欺诈</a>
                            <div class="dropdown-divider"></div>
                            <a class="dropdown-item" href="javascript:selectIncidentType('抢劫')">抢劫</a>
                            <a class="dropdown-item" href="javascript:selectIncidentType('绑架')">绑架</a>
                            <a class="dropdown-item" href="javascript:selectIncidentType('暴力事件')">暴力事件</a>
                        </div>
                    </div>
                </div>
                <input type="text" class="form-control" id="select_type" name="type" style="display:none;" placeholder="请在地图里面单击选择一个位置">
                <div class="row">
                    <div class="col-md-3"><label>事件发生时间：</label></div>
                    <div class="col-md-5">
                        <input type="date" class="form-control " name="date" placeholder="请选择事件发生时间">
                    </div>

                </div>
                <div class="checkbox" style="margin-top:55px;">
                    <label>
                        <input type="checkbox" id="c1"> 我确定我输入的信息真实可靠
                    </label>
                </div>
                <div class="checkbox">
                    <label>
                        <input type="checkbox" id="c2"> 我确认我提交的信息符合《Incidents Report系统信息提交规范》
                    </label>
                </div>
                <div class="checkbox">
                    <label>
                        <input type="checkbox" id="c3"> 我确认所报告的事件还没有得到解决
                    </label>
                </div>
                <br/>
                <a class="btn btn-default" href="/IncidentsReport">取消</a>
                <a href="javascript:submitIncident()" class="btn btn-primary btn-raised">提交事件</a>
            </form>
        </div>

        <script>
            //全局控件变量
            var inputLocationBox;
            var map;
            var selectPos;


            $(document).ready(function () {
                //初始化样式
                $('body').bootstrapMaterialDesign();
                //获取所有全局控件变量
                inputLocationBox = document.getElementById("inputLocation");
                document.getElementById("nav_submit").style.color = "deeppink";
                //初始化地图
                map = new qq.maps.Map(
                        document.getElementById("ttmap"),
                        {
                            center: new qq.maps.LatLng(39.914850, 116.403765),
                            zoom: 13
                        }
                );
                //添加监听事件   获取鼠标单击事件
                qq.maps.event.addListener(map, 'click', function (event) {
                    selectPos = event.latLng;
                    document.getElementById("select_postion").value = selectPos.toString();
                    var marker = new qq.maps.Marker({
                        position: selectPos,
                        map: map
                    });
                    qq.maps.event.addListener(map, 'click', function (event) {
                        marker.setMap(null);
                    });
                });
            });

            function selectIncidentType(typex) {
                document.getElementById("select_type").value = typex;
                document.getElementById("current_type").textContent = typex;
            }

            function selCheck() {
                var aa = document.getElementById("c1").checked;
                var bb = document.getElementById("c2").checked;
                var cc = document.getElementById("c3").checked;
                if(aa && bb && cc){
                    return true;
                }
                showMsg("请同意相关协议后再进行提交！");
                return false;
            }

            function submitIncident() {
                if (selCheck()) {
                    showMsg("提交中...");
                    SubmitForm("/IncidentsReport/SubmitIncident", "submit_incident", "提交失败，请重试！", "提交成功！");
                }
            }
        </script>
    </body>
</html>

