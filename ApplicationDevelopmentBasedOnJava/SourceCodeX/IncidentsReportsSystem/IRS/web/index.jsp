<%-- 
    Document   : testjsp
    Created on : Sep 23, 2017, 11:33:27 AM
    Author     : kanch
--%>

<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.Statement"%>
<%@page import="java.sql.Connection"%>
<%@page import="javax.sql.DataSource"%>
<%@page import="javax.naming.InitialContext"%>
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
        <div class="row" style="margin:0px;height:90vh;">
            <div class="col-md-9">
                <div id="ttmap" style="width:100%;height:100%;margin:0px;">

                </div>
            </div>
            <div class="col-md-3">
                <form style="margin-top:5vh;">
                    <div class="form-group">
                        <div class="row" style="margin:0vh;margin-top:15px;">
                            <input type="text" class="form-control" id="inputLocation" aria-describedby="emailHelp" placeholder="输入街道名称，查看事件情况" style="margin-top:4px; ">
                        </div>
                        <div class="row" style="margin:0vh;margin-top:15px;">
                            <button type="button" class="btn btn-primary" style="width:100%;" onclick="search()" >搜索</button>
                        </div>
                    </div>
                    <div class="form-group">
                        <div class="row" style="margin: 0vh;">
                            <div class="btn-group">
                                <button type="button" class="btn btn-info dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                    按事件类型筛选
                                </button>
                                <div class="dropdown-menu">
                                    <a class="dropdown-item" href="#">显示全部</a>
                                    <a class="dropdown-item" href="#">抢劫</a>
                                    <a class="dropdown-item" href="#">偷窃</a>
                                    <a class="dropdown-item" href="#">欺诈</a>
                                    <div class="dropdown-divider"></div>
                                    <a class="dropdown-item" href="#">测试</a>
                                </div>
                            </div>
                        </div>

                    </div>
                    <div class="form-group">
                        <div class="btn-group">
                            <button type="button" class="btn btn-info dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                按事件发送时间筛选
                            </button>
                            <div class="dropdown-menu">
                                <a class="dropdown-item" href="#">显示最近1年</a>
                                <a class="dropdown-item" href="#">最近6个月</a>
                                <a class="dropdown-item" href="#">最近3个月</a>
                                <a class="dropdown-item" href="#">最近1个月</a>
                                <a class="dropdown-item" href="#">最近1周</a>
                            </div>
                        </div>
                    </div>

                </form>
            </div>
        </div>

        <script>
            //全局控件变量
            var inputLocationBox;
            var map;

            $(document).ready(function () {
                //获取所有全局控件变量
                inputLocationBox = document.getElementById("inputLocation");
                map = new qq.maps.Map(
                        document.getElementById("ttmap"),
                        {
                            center: new qq.maps.LatLng(39.914850, 116.403765),
                            zoom: 13
                        }
                );
                //当地图中心属性更改时触发事件
                qq.maps.event.addListener(map, 'center_changed', function () {
                    console.log("latlng:" + map.getCenter());
                });
                //搜索服务
                var latlngBounds = new qq.maps.LatLngBounds();
                //设置Poi检索服务，用于本地检索、周边检索
                searchService = new qq.maps.SearchService({
                    //设置搜索范围为北京
                    location: "北京",
                    //设置搜索页码为1
                    pageIndex: 1,
                    //设置每页的结果数为5
                    pageCapacity: 5,
                    //设置展现查询结构到infoDIV上
                    panel: document.getElementById('infoDiv'),
                    //设置动扩大检索区域。默认值true，会自动检索指定城市以外区域。
                    autoExtend: true,
                    //检索成功的回调函数
                    complete: function (results) {
                        //设置回调函数参数
                        var pois = results.detail.pois;
                        for (var i = 0, l = pois.length; i < l; i++) {
                            var poi = pois[i];
                            //扩展边界范围，用来包含搜索到的Poi点
                            latlngBounds.extend(poi.latLng);
                        }
                        //调整地图视野
                        map.fitBounds(latlngBounds);
                    },
                    //若服务请求失败，则运行以下函数
                    error: function () {
                        showMsg("出错了。");
                    }
                });
                //加载当前区域的事件
                firstLoading();
            });

            function decideType(tstr) {
                switch (tstr) {
                    case "/IncidentsReport/static/icons/car_stolen":
                        return "汽车偷窃";
                    case "/IncidentsReport/static/icons/fire":
                        return "火灾";
                    case "/IncidentsReport/static/icons/kidnapping":
                        return "绑架";
                    case "/IncidentsReport/static/icons/lie":
                        return "欺诈";
                    case "/IncidentsReport/static/icons/robbery":
                        return "抢劫";
                    case "/IncidentsReport/static/icons/stolen":
                        return "入室盗窃";
                    case "/IncidentsReport/static/icons/violence":
                        return "暴力事件";
                }
                return tstr;
            }

            function search() {
                var keyword = inputLocationBox.value;
                console.log("search location:" + keyword);
                if (keyword.length < 1) {
                    showMsg("请输入有效信息后再搜索！");
                    return;
                }
                searchService.search(keyword);
            }

            function getIncidents(vlatlng, vsum) {
                $.get("/IncidentsReport/getIncidents?latlng=" + vlatlng + "&vsum=" + vsum, function (data) {
                    dta = data.split("<br/>");
                    incidentstr = dta[1].split("$");
                    var latlngarr = new Array();
                    var incidentsarr = new Array();
                    var incidentIcons = new Array();
                    //获取地理位置数组和事件数组
                    for (i = 0; i < incidentstr.length; i++) {
                        if (incidentstr[i].length > 5) {
                            incident = incidentstr[i].split("@");
                            ll = incident[4].split(",");
                            //构造标记位置
                            var latlng = new qq.maps.LatLng(Number(ll[0]), Number(ll[1]));
                            console.log(incident);
                            latlngarr.push(latlng);
                            //建立到提示窗
                            var infocontent = '<div style="text-align:left;white-space:nowrap;' +
                                    'margin:10px;">事件类型：@type<br/>' +
                                    '发生时间：@time<br/>' +
                                    '事件描述：@des<br/>' +
                                    '可信度：@credit</div>';
                            infocontent = infocontent.replace("@type", decideType(incident[1]))
                                    .replace("@time", incident[6])
                                    .replace("@des", incident[3])
                                    .replace("@credit", incident[2]);
                            incidentsarr.push(infocontent);
                            //添加标记图标
                            incidentIcons.push(incident[1] + ".png");
                        }
                    }
                    //显示提示窗口
                    var infoWin = new qq.maps.InfoWindow({
                        map: map
                    });
                    for (var i = 0; i < latlngarr.length; i++) {
                        (function (n) {
                            var marker = new qq.maps.Marker({
                                position: latlngarr[n],
                                map: map,
                                icon: incidentIcons[n]
                            });
                            qq.maps.event.addListener(marker, 'click', function () {
                                infoWin.open();
                                infoWin.setContent(incidentsarr[n]);
                                infoWin.setPosition(latlngarr[n]);
                            });
                        })(i);
                    }
                });
            }

            var sss = `
            function getIncidents(vlatlng, vsum) {
                $.get("/IncidentsReport/getIncidents?latlng=" + vlatlng + "&vsum=" + vsum, function (data) {
                    dta = data.split("<br/>");
                    incidentstr = dta[1].split("$");
                    console.log(incidentstr);
                    for (i = 0; i < incidentstr.length; i++) {
                        if (incidentstr[i].length > 5) {
                            incident = incidentstr[i].split("@");
                            ll = incident[4].split(",");
                            //构造标记位置
                            var latlng = new qq.maps.LatLng(Number(ll[0]), Number(ll[1]));
                            console.log(incident);
                            //添加标记
                            var marker = new qq.maps.Marker({
                                icon: incident[1] + ".png",
                                map: map,
                                position: latlng});
                            //添加标记点击事件
                            //添加到提示窗
                            var info = new qq.maps.InfoWindow({
                                map: map
                            });
                            //获取标记的点击事件
                            var infocontent = '<div style="text-align:left;white-space:nowrap;' +
                                    'margin:10px;">事件类型：@type<br/>' +
                                    '发生时间：@time<br/>' +
                                    '事件描述：@des<br/>' +
                                    '可信度：@credit</div>';
                            infocontent = infocontent.replace("@type",decideType(incident[1]))
                                                     .replace("@time",incident[6] )
                                                     .replace("@des", incident[3])
                                                     .replace("@credit", incident[2]);
                            qq.maps.event.addListener(marker, 'click', function () {
                                info.open();
                                info.setContent(infocontent);
                                info.setPosition(latlng);
                            });
                        }
                    }
                });
            }
`;

            function firstLoading() {
                center = map.getCenter();
                getIncidents(center.getLat() + "," + center.getLng(), 30);
            }
        </script>
    </body>
</html>
