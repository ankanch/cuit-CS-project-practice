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
        <script src="static/echarts.min.js"></script>
        <script src="static/snackbarjs/snackbar.min.js"></script>
        <script charset="utf-8" src="http://map.qq.com/api/js?v=2.exp&key=DPIBZ-OHXKD-A6O4L-HPUN3-ZAAV7-A6B6P"></script>
        <!-- Compiled and minified JavaScript -->
        <script src="static/materialize/js/bootstrap-material-design.min.js"></script>
    </head>
    <body>
        <jsp:include page="template/header.jsp"/>
        <div class="row" style="margin:0px;height:90vh;">
            <div class="col-md-9" style="padding-left: 0px;">
                <div id="ttmap" style="width:100%;height:100%;margin:0px;">

                </div>
                <!-- Modal -->
                <div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
                    <div class="modal-dialog" role="document">
                        <div class="modal-content">
                            <div class="modal-header">
                                <h5 class="modal-title" id="exampleModalLabel">创建事件警报</h5>
                                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                            </div>
                            <div class="modal-body">
                                <form id="registe_for_alert">
                                    <div class="form-group">
                                        <label for="exampleInputEmail1" class="bmd-label-floating">您的电子邮件地址：</label>
                                        <input name="email" type="email" class="form-control" id="exampleInputEmail1">
                                        <span class="bmd-help">我们将不会与任何人分享您填入的信息.</span>
                                    </div>
                                    <div class="form-group">
                                        <label for="exampleInputPassword1" class="bmd-label-floating">警报名称：</label>
                                        <input name="alertname" type="text" class="form-control" id="exampleInputPassword1">
                                    </div>
                                    <div class="form-group">
                                        报警地理位置（方圆3公里）：
                                        <input name="location" type="text" class="form-control" id="exampleInputPassword2" readonly>
                                    </div>
                                </form>
                            </div>
                            <div class="modal-footer">
                                <button type="button" class="btn btn-secondary" data-dismiss="modal">取消</button>
                                <button type="button" class="btn btn-primary" onclick="send()" data-dismiss="modal">建立警报</button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="col-md-3">
                <form style="margin-top:5vh;">
                    <div class="form-group" style="padding-top:0px;">
                        <button type="button" class="btn btn-primary col-md-3" style="width:100%;float: right;" onclick="search()" >搜索</button>
                        <input type="text" class="form-control col-md-9" id="inputLocation" aria-describedby="emailHelp" placeholder="输入街道名称，查看事件情况" style="margin-top:4px; ">
                    </div>
                    <div class="form-group">
                        <div class="row" style="margin: 0vh;">
                            <div class="btn-group">
                                <button type="button" class="btn btn-info dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                    按事件类型筛选
                                </button>
                                <div class="dropdown-menu">
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('all')">显示全部</a>
                                    <div class="dropdown-divider"></div>
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('/IncidentsReport/static/icons/car_stolen')">汽车偷窃</a>
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('/IncidentsReport/static/icons/fire')">火灾</a>
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('/IncidentsReport/static/icons/stolen')">入室盗窃</a>
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('/IncidentsReport/static/icons/lie')">欺诈</a>
                                    <div class="dropdown-divider"></div>
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('/IncidentsReport/static/icons/robbery')">抢劫</a>
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('/IncidentsReport/static/icons/kidnapping')">绑架</a>
                                    <a class="dropdown-item" href="javascript:incidentTypeFilter('/IncidentsReport/static/icons/violence')">暴力事件</a>
                                </div>
                            </div>
                        </div>

                    </div>

                </form>
                <div id="main" style="width: 98%;height:300px;"></div>
            </div>
        </div>

        <script>
            //全局控件变量
            var inputLocationBox;
            var map;
            var loading = false;
            var incidentsList = new Array();    // 事件信息数组，每一个元素由数组组成
            ////（0：经纬度，1：卡片内容，2：事件图标，3：事件类型，4：事件ID，5：时间发生时间，6：marker）
            var myChart = echarts.init(document.getElementById('main'));

            $(document).ready(function () {
                //获取所有全局控件变量
                $('body').bootstrapMaterialDesign();
                inputLocationBox = document.getElementById("inputLocation");
                document.getElementById("alert").style.display = 'block';
                map = new qq.maps.Map(
                        document.getElementById("ttmap"),
                        {
                            center: new qq.maps.LatLng(39.914850, 116.403765),
                            zoom: 13
                        }
                );
                //当地图中心属性更改时触发事件
                qq.maps.event.addListener(map, 'center_changed', function () {
                    updateOnmove();
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

            function search() {
                var keyword = inputLocationBox.value;
                console.log("search location:" + keyword);
                if (keyword.length < 1) {
                    showMsg("请输入有效信息后再搜索！");
                    return;
                }
                searchService.search(keyword);
                firstLoading();
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
                            var incidentInfoObj = new Array();
                            incident = incidentstr[i].split("@");
                            ll = incident[4].split(",");
                            //构造标记位置
                            var latlng = new qq.maps.LatLng(Number(ll[0]), Number(ll[1]));
                            console.log(incident);
                            latlngarr.push(latlng);
                            incidentInfoObj.push(latlng); //0 事件经纬度
                            //建立到提示窗
                            var infocontent = '<div style="text-align:left;white-space:nowrap;' +
                                    'margin:10px;">事件类型：@type<br/>' +
                                    '发生时间：@time<br/>' +
                                    '已确认该事件人数：@credit</div>' +
                                    '<button type="button" class="btn btn-outline-success btn-sm" onclick="support(@id)">标记为可靠</button>';
                            infocontent = infocontent.replace("@type", decideType(incident[1]))
                                    .replace("@time", incident[6])
                                    .replace("@credit", incident[2])
                                    .replace("@id", incident[0]);
                            incidentsarr.push(infocontent);
                            incidentInfoObj.push(infocontent);   //1事件卡片内容
                            //添加标记图标
                            incidentIcons.push(incident[1] + ".png");
                            incidentInfoObj.push(incident[1] + ".png"); //2事件图标
                            incidentInfoObj.push(incident[1]);  //3 事件类型
                            incidentInfoObj.push(incident[0]); //4:事件ID
                            incidentInfoObj.push(incident[6]); //5:发生日期
                            incidentsList.push(incidentInfoObj); //
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
                                icon: incidentsList[n][2]
                            });
                            qq.maps.event.addListener(marker, 'click', function () {
                                infoWin.open();
                                infoWin.setContent(incidentsList[n][1]);
                                infoWin.setPosition(incidentsList[n][0]);
                                //加载类似事件统计图
                                updateStatgraphBytime(incidentsList[n][3]);
                            });
                            incidentsList[n].push(marker);  //6：marker在对应incidentInfoObj数组的下标为4的位置，而不是incidentsList
                        })(i);
                    }
                    //显示事件统计数据
                    updateIncidentsStatgraph();
                });
            }


            //删除地图上的所有事件标记
            function deleteOverlays() {
                if (incidentsList) {
                    for (i in incidentsList) {
                        if (typeof incidentsList[i][6] != 'undefined') {
                            incidentsList[i][6].setMap(null);
                        }
                    }
                    incidentsList.length = 0;
                }
            }

            function setAllIncidentsVisable() {
                for (var i = 0; i < incidentsList.length; i++) {
                    if (typeof incidentsList[i][6] != 'undefined') {
                        incidentsList[i][6].setVisible(true);
                    }
                }
            }

            function incidentTypeFilter(type) {
                if (type == "all") {
                    for (var i = 0; i < incidentsList.length; i++) {
                        if (typeof incidentsList[i][6] != 'undefined') {
                            incidentsList[i][6].setVisible(true);
                        }
                    }
                    return;
                }
                setAllIncidentsVisable();
                for (var i = 0; i < incidentsList.length; i++) {
                    if (typeof incidentsList[i][6] != 'undefined' && incidentsList[i][3] != type) {
                        incidentsList[i][6].setVisible(false);
                    }
                }
            }

            function firstLoading() {
                if (loading) {
                    setTimeout(function () {
                        return;
                    }, 3000);
                    return;
                }
                loading = true;
                showMsg("加载数据...");
                incidentsList = new Array();
                center = map.getCenter();
                getIncidents(center.getLat() + "," + center.getLng(), 30);
                setTimeout(function () {
                    loading = false;
                }, 3000);
            }

            function updateOnmove() {
                if (loading) {
                    setTimeout(function () {
                        return;
                    }, 3000);
                    return;
                }
                loading = true;
                showMsg("加载数据...");
                deleteOverlays();
                console.log("moving_map_update_latlng:" + map.getCenter());
                incidentsList = new Array();
                center = map.getCenter();
                getIncidents(center.getLat() + "," + center.getLng(), 30);
                setTimeout(function () {
                    loading = false;
                }, 1500);
            }

            function setAlertLoc() {
                $('#exampleModal').modal('show');
                document.getElementById('exampleInputPassword2').value = map.getCenter();
            }

            function checkEmail() {
                var inputEmail = document.getElementById("exampleInputEmail1").value;
                if (inputEmail === null || inputEmail === '') {
                    alert("Please input Email!");
                    return false;
                }

                var inputStatus = document.getElementById("exampleInputPassword1").value;
                if (inputStatus === null || inputStatus === '') {
                    alert("Please input Status!");
                    return false;
                }

                var inputSubscriabe = document.getElementById("exampleInputPassword2").value;
                if (inputSubscriabe === null || inputSubscriabe === '') {
                    alert("Please input Subscriabe!");
                    return false;
                }
                return true;
            }
            function send() {
                if (true === checkEmail()) {
                    showMsg("提交中...");
                    SubmitForm("/IncidentsReport/getEmailMessage", "registe_for_alert", "注册失败", "注册成功！");
                }
            }

            function sortFunction(a, b) {
                if (a[0] === b[0]) {
                    return 0;
                } else {
                    return (a[0] < b[0]) ? -1 : 1;
                }
            }

            //本函数用来显示某一类事件最近一段时间的发生情况,默认最长粒度：60天
            function updateStatgraphBytime(itype) {
                var datelist = new Array();
                var dv = new Array();
                for (i in incidentsList) {
                    if (incidentsList[i][3] == itype) {
                        var xp = 0;
                        for (j in datelist) {
                            if (incidentsList[i][5] == datelist[j]) {
                                break;
                            }
                            xp += 1;
                        }
                        if (xp == datelist.length) {
                            var nd = new Array();
                            nd = [incidentsList[i][5], 1];
                            datelist.push(nd);
                        } else {
                            datelist[xp][1] += 1;
                        }
                    }
                }
                datelist.sort(sortFunction);
                //组合数组
                for (i in datelist) {
                    dv.push(datelist[i][1]);
                }
                if (datelist.length < 7) {
                    for (var i = datelist.length; i < 7 - datelist.length; i++) {
                        dv.splice(i, 0, i % 2);
                    }
                }
                console.log(dv);
                drawLinerGraph(dv)
            }

            //该函数用来生成国区7天的数据,返回对应数组
            function last7Days(d) {
                d = +(d || new Date()), days = [], i = 7;
                while (i--) {
                    days.push(formatUSDate(new Date(d -= 8.64e7)));
                }
                return days;
            }

            // Return date string in mm/dd/y format
            //function from:https://stackoverflow.com/questions/22850929/most-efficient-way-to-get-the-dates-for-the-past-7-days-in-javascript
            function formatUSDate(d) {
                function z(n) {
                    return (n < 10 ? '0' : '') + +n;
                }
                return z(d.getMonth() + 1) + '/' + z(d.getDate()) + '/' + d.getFullYear();
            }


            //本函数用于统计在当前屏幕环境下各类事件的发生情况
            function updateIncidentsStatgraph() {
                var data = [["/IncidentsReport/static/icons/car_stolen", 0],
                    ["/IncidentsReport/static/icons/fire", 0],
                    ["/IncidentsReport/static/icons/kidnapping", 0],
                    ["/IncidentsReport/static/icons/lie", 0],
                    ["/IncidentsReport/static/icons/robbery", 0],
                    ["/IncidentsReport/static/icons/stolen", 0],
                    ["/IncidentsReport/static/icons/violence", 0]];
                for (i in incidentsList) {
                    for (j in data) {
                        if (incidentsList[i][3] == data[j][0]) {
                            data[j][1] += 1;
                            break;
                        }
                    }
                }
                //将数据划分为两个数组
                var pp = new Array();
                for (i in data) {
                    pp.push(data[i][1]);
                }
                console.log(pp);
                drawBargraph(pp);
            }

            function drawBargraph(data) {
                var dataAxis = ['汽车偷窃', '火灾', '绑架', '欺诈', '抢劫', '入室盗窃', "暴力事件"];
                option = {
                    title: {
                        text: '各类事件发生情况',
                        subtext: '基于当前显示区域'
                    },
                    xAxis: {
                        data: dataAxis,
                        axisTick: {
                            show: false
                        },
                        axisLine: {
                            show: false
                        }
                    },
                    yAxis: {
                        axisLine: {
                            show: false
                        },
                        axisTick: {
                            show: false
                        },
                        axisLabel: {
                            textStyle: {
                                color: '#999'
                            }
                        }
                    },
                    series: [
                        {// For shadow
                            type: 'bar',
                            itemStyle: {
                                normal: {color: 'rgba(0,0,0,0.05)'}
                            },
                            barGap: '-100%',
                            barCategoryGap: '40%',
                            animation: true
                        },
                        {
                            type: 'bar',
                            itemStyle: {
                                normal: {
                                    color: new echarts.graphic.LinearGradient(
                                            0, 0, 0, 1,
                                            [
                                                {offset: 0, color: '#83bff6'},
                                                {offset: 0.5, color: '#188df0'},
                                                {offset: 1, color: '#188df0'}
                                            ]
                                            )
                                },
                                emphasis: {
                                    color: new echarts.graphic.LinearGradient(
                                            0, 0, 0, 1,
                                            [
                                                {offset: 0, color: '#2378f7'},
                                                {offset: 0.7, color: '#2378f7'},
                                                {offset: 1, color: '#83bff6'}
                                            ]
                                            )
                                }
                            },
                            data: data
                        }
                    ]
                };
                myChart.clear();
                myChart.setOption(option);
            }

            function drawLinerGraph(data) {
                var date = last7Days();
                option = {
                    tooltip: {
                        trigger: 'axis',
                        position: function (pt) {
                            return [pt[0], '10%'];
                        }
                    },
                    title: {
                        left: 'center',
                        text: '同类事件最近发生情况',
                    },
                    xAxis: {
                        type: 'category',
                        boundaryGap: false,
                        data: date
                    },
                    yAxis: {
                        type: 'value',
                        boundaryGap: [0, '100%']
                    },
                    series: [
                        {
                            name: '报告事件数',
                            type: 'line',
                            smooth: true,
                            symbol: 'none',
                            sampling: 'average',
                            itemStyle: {
                                normal: {
                                    color: 'rgb(255, 70, 131)'
                                }
                            },
                            areaStyle: {
                                normal: {
                                    color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [{
                                            offset: 0,
                                            color: 'rgb(255, 158, 68)'
                                        }, {
                                            offset: 1,
                                            color: 'rgb(255, 70, 131)'
                                        }])
                                }
                            },
                            data: data
                        }
                    ]
                };
                myChart.clear();
                myChart.setOption(option);
            }

            function support(id) {
                $.getScript("/IncidentsReport/supportIncidents?iid=" + id, function success(data) {
                    console.log(data)
                    if (data.indexOf("ERROR") > -1) {
                        showMsg(data.split("<br/>")[1]);
                    } else {
                        showMsg("事件确认成功！");
                    }
                })
            }
        </script>
    </body>
</html>
