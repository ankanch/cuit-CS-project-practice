<%-- 
    Document   : crosstableanalytics
    Created on : 2018-6-16, 12:12:18
    Author     : Miss Zhang
--%>
<%@page import="dbi.localization.langID"%>
<%@page import="dbi.localization.lang"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<% lang local = lang.detectLang(request);%>
<h2><%=local.getString(langID.JSP_CTA_CONSOLE_TITLE)%></h2>
<div id="crosstableanalysis">
    <button type="button" class="btn btn-primary" onclick="writenewchart()"><%=local.getString(langID.JSP_CTA_CONSOLE_BTN_ADDCHART)%></button>
    <button type="button" style="float: right" class="btn btn-raised btn-success" onclick="analyze()"><%=local.getString(langID.JSP_CTA_CONSOLE_BTN_GENERATEREPORT)%></button>
    <div id="accordion">
        <div class="progress-line" id="progressbar" style="display:none;"></div>
        <div class="card">
            <div class="card-header" id="headingOne">
                <h5 class="mb-0">
                    <button class="btn btn-link" data-toggle="collapse" data-target="#collapseOne" aria-expanded="true" aria-controls="collapseOne">
                        <%=local.getString(langID.JSP_CTA_CONSOLE_CL1_TITLE)%>
                    </button>
                </h5>
            </div>
            <div id="collapseOne" class="collapse show" aria-labelledby="headingOne" data-parent="#accordion">
                <div class="card-body">
                    <div id="tablediv">
                        <div class="card-body">
                            <div class="alert alert-danger" role="alert" id="alert">
                                <%=local.getString(langID.JSP_CTA_CONSOLE_CL1_TIP)%>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="card">
            <div class="card-header" id="headingTwo">
                <h5 class="mb-0">
                    <button class="btn btn-link collapsed" data-toggle="collapse" data-target="#collapseTwo" aria-expanded="false" aria-controls="collapseTwo">
                        <%=local.getString(langID.JSP_CTA_CONSOLE_CL2_TITLE)%>
                    </button>
                </h5>
            </div>
            <div id="collapseTwo" class="collapse" aria-labelledby="headingTwo" data-parent="#accordion">
                <div class="card-body" id="chartslist">
                    <div class="alert alert-danger" role="alert" id="alert">
                        <%=local.getString(langID.JSP_CTA_CONSOLE_CL2_TIP)%>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

<script src="static/oplib/jsinjsp/analytics.customize.js"></script>
<script src="static/oplib/jsinjsp/analytics.chart.instance.js"></script>
<script src="static/oplib/jsinjsp/analytics.report.js"></script>
<script>
        var iii = 1;
        var currentcol = 1;
        var colrep = [];
        $('#crosstableanalysis').bootstrapMaterialDesign();
        function getDatabase(v) {
            GetDataF("/api/getDatabases", function error(data) {
                showMsg("Failed to load database list.");
            }, function success(data) {
                var list = data.data;
                var element = document.getElementById("showDatabase_" + v);
                var st = "<a class=\"dropdown-item\" onclick=\"getTable(ggggggggggggggggggg,hhhhhhhhhhh)\" id=\"iddb\">dbname</a>";
                var str = "";
                for (var i = 0; i < list.length; i++) {
                    str = str + st.replace("iddb", "iddb" + "_" + v + "_" + i).replace("dbname", list[i]).replace("ggggggggggggggggggg", v).replace("hhhhhhhhhhh", i);
                }
                element.innerHTML = str;
            });
        }

        function analyze() {
            var v = [];
            for (var i = 0; i < colrep.length; i++) {
                var linshi = [];
                var chart = "";
                var chartcomment = "";
                var database = "";
                var table = "";
                var col = "";
                var shujuleixing = "";
                var juhehanshu = "";
                var comment = "";
                var linzong = "";
                chart = $("#chartname_" + colrep[i][0]).val();
                linshi.push(chart);
                chartcomment = $("#comment_" + colrep[i][0]).val();
                linshi.push(chartcomment);
                for (var j = 1; j < colrep[i].length; j++) {
                    col = colrep[i][j];
                    database = document.getElementById("database_" + colrep[i][0] + "_" + col).innerHTML;
                    table = document.getElementById("table_" + colrep[i][0] + "_" + col).innerHTML;
                    linzong = linzong + database + "->" + table + "->" + col + ";";
                }
                linshi.push(linzong);
                shujuleixing = document.getElementById("btn_selecttype_" + colrep[i][0]).dataset.poolf;
                juhehanshu = document.getElementById("buttonnames_" + colrep[i][0]).dataset.poolf;
                linshi.push(shujuleixing);
                linshi.push(juhehanshu);

                for (var j = 1; j < colrep[i].length; j++) {
                    col = colrep[i][j];
                    var qn = $("#colid_" + colrep[i][0] + "_" + col).val();
                    if (qn === '') {
                        comment = comment + col + ";";
                    } else {
                        comment = comment + qn + ";";
                    }
                }
                linshi.push(comment);
                v.push(linshi);
            }
            showMsg("Start analyzing...");
            console.log(v);
            SubmitFormKVF("/api/getCrossTableAnalyzeResult", {data: DBIEX.toString(v)}, function error(data) {
                showMsg("Failed to load table list.");
            }, function success(data) {
                showMsg("success");
                $("#chartslist").html(CHART_CONTAINER_SAVE_REPORT + REPORT_HEAD);
                var line = data.data;
                console.log("line=" + line);
                // data format-> row 1: chart count
                //               row 2: chart id list
                //               row 3: chart option list
                // generate chart 
                for (var i = 0; i < line[0]; i++) {
                    var chtid = line[1][i];
                    console.log("process " + i + "\t with id of " + chtid);
                    var chtcontainer = CHART_CONTAINER.replace("@ID", chtid).replace("@OPTION", line[2][i]);
                    $("#chartslist").append(chtcontainer);
                    option = eval(line[2][i]);
                    initChartWithOption(chtid, option);
                }
                $('#collapseTwo').collapse("show");
            });
        }

        function getTable(a, b) {
            var dbname = document.getElementById("iddb" + "_" + a + "_" + b).innerHTML;
            document.getElementById("buttonMenu_1_" + a).innerText = dbname;
            document.getElementById("buttonMenu_1_" + a).dataset.poolf = dbname;
            SubmitFormKVF("/api/getTables", {dbname: dbname}, function error(data) {
                showMsg("Failed to load table list.");
            }, function success(data) {
                var list = data.data;
                var element = document.getElementById("showTables_" + a);
                var st = "<a class=\"dropdown-item\"  onclick=\"getColumns(" + a + ",lllll)\" id=\"idcolumn\">dbname</a>";
                var str = "";
                for (var i = 0; i < list.length; i++) {
                    str = str + st.replace("idcolumn", "dbc_" + a + "_" + i).replace("dbname", list[i]).replace("lllll", i);
                }
                element.innerHTML = str;
            });
        }

        function getColumns(a, b) {
            console.log("dbc_" + a + "_" + b);
            document.getElementById("buttonMenu_2_" + a).innerHTML = document.getElementById("dbc_" + a + "_" + b).innerHTML;
            var columns = document.getElementById("showColumns_" + a);
            var dbname = document.getElementById("buttonMenu_1_" + a).innerHTML;
            var tbname = document.getElementById("buttonMenu_2_" + a).innerHTML;
            SubmitFormKVF("/api/GetColumns", {dbname: dbname, tbname: tbname, idname: a}, function error_func(data) {
                showMsg("Failed to load table field list.");
            }, function success_func(data) {
                columns.innerHTML = data.data[0];
            });
        }

        function addtoColumn(a, v) {
            var neirong = document.getElementById("col_" + a + "_" + v).innerHTML;
            document.getElementById("buttonMenu_3_" + a).innerHTML = neirong;
        }

        var r = 0;
        function addCol(a) {
            var neirong = document.getElementById("buttonMenu_3_" + a).innerHTML;
            var databasename = document.getElementById("buttonMenu_1_" + a).dataset.poolf;
            var table = document.getElementById("buttonMenu_2_" + a).innerHTML;
            var iid = "colid_" + a + "_" + neirong;
            var databaseid = "database_" + a + "_" + neirong;
            var tableid = "table_" + a + "_" + neirong;
            var myvar = "<tr>" +
                    "       <td id=\"" + databaseid + "\">" + databasename + "</td>" +
                    "      <td id=\"" + tableid + "\">" + table + "</td>" +
                    "       <td>" + neirong + "</td>" +
                    "      <td><input id=\"tttt\" type=\"text\" class=\"form-control\" aria-label=\"Default\" aria-describedby=\"inputGroup-sizing-default\"></td>" +
                    "       <td><button type=\"button\" onclick='deletecolumns(" + a + ",\"ssss\",this)' class=\"btn btn-primary\">删除</button></td>" +
                    "</tr>";
            $("#neirong_" + a).append(myvar.replace("ssss", neirong).replace("tttt", iid));
            var p = 0;
            for (var i = 0; i < colrep.length; i++) {
                console.log(colrep[i][0] + "  " + a);
                if (colrep[i][0] === a) {
                    p = 1;
                    colrep[i].push(neirong);
                    console.log("success");
                }
            }
            if (p === 0) {
                colrep.push([a]);
                colrep[colrep.length - 1].push(neirong);
            }
            console.log(colrep.length);
            if (colrep.length > 0) {
                console.log("test");
            }
            console.log(colrep);
            r = r + 1;
            $(".modal").modal("hide");
        }

        function deletecolumns(a, b, obj) {
            var colreplace = [];
            var tr = obj.parentNode.parentNode;//得到按钮[obj]的父元素[td]的父元素[tr]
            tr.parentNode.removeChild(tr);//从tr的父元素[tbody]移除tr
            colreplace.push(a);
            for (var i = 0; i < colrep.length; i++) {
                console.log("colrep[i][0]:" + colrep[i][0] + ",a:" + a);
                if (colrep[i][0] === a) {
                    for (var j = 1; j < colrep[i].length; j++) {
                        console.log("colrep:" + colrep[i][j] + ",b" + b);
                        if (colrep[i][j] !== b) {
                            colreplace.push(colrep[i][j]);
                        }
                    }
                    colrep[i] = colreplace;
                    break;
                }
            }
            for (var i = 0; i < colrep.length; i++) {
                if (colrep[i].length === 1) {
                    colrep.splice(i, 1);
                }
            }
            console.log("colreplace:");
            console.log(colreplace);
            console.log("after delete:");
            console.log(colrep);
        }

        function removeDiv(v) {
            var div = document.getElementById("coldiv_" + v.toString());
            div.remove();
            for (var i = 0; i < colrep.length; i++) {
                if (colrep[i][0] === v) {
                    colrep.splice(i, 1);
                    break;
                }
            }
            console.log(colrep);
        }

        function createNewchart(v) {
            console.log("current:" + v);
            currentcol = v;
            $('#myModal_' + v).modal();
        }

        function writenewchart() {
            $("#alert").hide();
            var html = "<div class=\"card text-white bg-primary mb-3\" style=\"max-width: 100%;\" id=\"coldiv_ssss\">" +
                    "        <div class=\"card-header bg-primary text-info\" style=\"height:60px\">" +
                    "            <div style=\"float: left;\">" +
                    "                <input type=\"text\" id=\"chartname_ssss\" value=\"图表ssss\" style=\"width: 80%\" class=\"form-control text-white\" aria-label=\"Small\"  aria-describedby=\"inputGroup-sizing-sm\">" +
                    "            </div>" +
                    "            <div style=\"float: left;\">" +
                    "                <input type=\"text\" id=\"comment_ssss\" value=\"描述\" class=\"form-control text-white\" aria-label=\"Small\" aria-describedby=\"inputGroup-sizing-sm\">" +
                    "            </div>" +
                    "            <div class=\"dropdown\" style=\"float: left;\">" +
                    "                <button class=\"btn btn-secondary dropdown-toggle text-white\" type=\"button\" id=\"btn_selecttype_ssss\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">" +
                    "                    数据类型" +
                    "                </button>" +
                    "                <div class=\"dropdown-menu\" aria-labelledby=\"dropdownMenuButton\">" +
                    "                    <a class=\"dropdown-item\" onclick=\"chooseNumber(ssss)\">数字</a>" +
                    "                    <a class=\"dropdown-item\" onclick=\"chooseText(ssss)\">文本</a>" +
                    "                </div>" +
                    "            </div>" +
                    "" +
                    "            <div class=\"dropdown\" style=\"float: left;\" id=\"choosetype_ssss\">" +
                    "                <button class=\"btn btn-secondary dropdown-toggle text-white\" type=\"button\"  data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">" +
                    "                    聚合函数" +
                    "                </button>" +
                    "                <div class=\"dropdown-menu\" aria-labelledby=\"dropdownMenuButton\" >" +
                    "                    " +
                    "                </div>" +
                    "            </div>" +
                    "            <div style=\"float: left;\">" +
                    "                <button type=\"button\" class=\"btn btn-secondary text-white\" onclick=\"createNewchart(ssss)\">添加行</button>" +
                    "            </div>" +
                    "            <div style=\"float: left;\">" +
                    "                <button type=\"button\" class=\"btn btn-secondary text-white\" onclick=\"removeDiv(ssss)\">删除图表</button>" +
                    "            </div>" +
                    "        </div>" +
                    "" +
                    "        <div class=\"card-body bg-light\">" +
                    "               <table class=\"table table-striped text-dark\" id=\"neirong_ssss\">" +
                    "                   <tbody>" +
                    "                           <tr></tr>" +
                    "                   </tbody>" +
                    "        </table>" +
                    "        </div>" +
                    "    </div>";
            var yincang = "<div class=\"modal fade\" id=\"myModal_ssss\" tabindex=\"-1\" role=\"dialog\" aria-labelledby=\"myModalLabel\">" +
                    "    <div class=\"modal-dialog\" role=\"document\">" +
                    "        <div class=\"modal-content\">" +
                    "            <div class=\"modal-header\">" +
                    "                <button type=\"button\" class=\"btn btn-primary\" data-toggle=\"modal\" data-target=\".bd-example-modal-lg\">添加行</button>" +
                    "            </div>" +
                    "            <div class=\"modal-body\">" +
                    "                <table class=\"table\">" +
                    "                    <tbody>" +
                    "                        <tr>" +
                    "                            <th scope=\"row\">1</th>" +
                    "                            <td>" +
                    "                                <div class=\"btn-group\">" +
                    "                                    <button type=\"button\" id=\"buttonMenu_1_ssss\" onclick=\"getDatabase(ssss)\" data-poolf=\"\" class=\"btn btn-primary dropdown-toggle\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">" +
                    "                                        select databases" +
                    "                                    </button>" +
                    "                                    <div class=\"dropdown-menu\" id=\"showDatabase_ssss\">" +
                    "                                    </div>" +
                    "                                </div>" +
                    "                            </td>" +
                    "                        </tr>" +
                    "                        <tr>" +
                    "                            <th scope=\"row\">2</th>" +
                    "                            <td>" +
                    "                                <div class=\"btn-group\">" +
                    "                                    <button type=\"button\" id=\"buttonMenu_2_ssss\" class=\"btn btn-primary dropdown-toggle\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">" +
                    "                                        select tables" +
                    "                                    </button>" +
                    "                                    <div class=\"dropdown-menu\" id=\"showTables_ssss\">" +
                    "                                    </div>" +
                    "                                </div>" +
                    "                            </td>" +
                    "                        </tr>" +
                    "                        <tr>" +
                    "                            <th scope=\"row\">3</th>" +
                    "                            <td>" +
                    "                                <div class=\"btn-group\">" +
                    "                                    <button type=\"button\" id=\"buttonMenu_3_ssss\" class=\"btn btn-primary dropdown-toggle\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">" +
                    "                                        select column" +
                    "                                    </button>" +
                    "                                    <div class=\"dropdown-menu\" id=\"showColumns_ssss\">" +
                    "                                    </div>" +
                    "                                </div>" +
                    "                            </td>" +
                    "                        </tr>" +
                    "                    </tbody>" +
                    "                </table>" +
                    "            </div>" +
                    "            <div class=\"modal-footer\">" +
                    "                <button type=\"button\" class=\"btn btn-default\" data-dismiss=\"modal\"><span class=\"glyphicon glyphicon-remove\" aria-hidden=\"true\"></span>关闭</button>" +
                    "                <button type=\"button\" onclick=\"addCol(ssss)\" id=\"btn_submit\" class=\"btn btn-primary\" ><span class=\"glyphicon glyphicon-floppy-disk\" aria-hidden=\"true\"></span>添加</button>" +
                    "            </div>" +
                    "        </div>" +
                    "    </div>" +
                    "</div>";
            var zong = html + yincang;
            $("#tablediv").append(zong.replace(/ssss/g, iii));
            console.log("zong:" + zong);
            iii = iii + 1;
        }

        function chooseNumber(v) {
            document.getElementById("btn_selecttype_" + v.toString()).innerHTML = "数字";
            document.getElementById("btn_selecttype_" + v.toString()).dataset.poolf = "type_number";
            var element = document.getElementById("choosetype_" + v.toString());
            var str = "<button id=\"buttonnames_" + v.toString() + "\" class=\"btn btn-outline-secondary dropdown-toggle text-white\" type=\"button\" data-toggle=\"dropdown\"" +
                    "                aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf='pf_none'>无</button>" +
                    "                <div class=\"dropdown-menu\">" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_none\">无</a>" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_trend\" data-text='平均'>趋势</a>" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count\">计数</a>" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_max\">最大</a>" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_min\">最小</a>" +
                    "                </div>";

            element.innerHTML = str;
        }

        function choosetypename(v, x) {
            document.getElementById("buttonnames_" + x.toString()).dataset.poolf = v.dataset.poolf;
            document.getElementById("buttonnames_" + x.toString()).innerHTML = v.innerHTML;
        }

        function chooseText(v) {
            document.getElementById("btn_selecttype_" + v.toString()).innerHTML = "文本";
            document.getElementById("btn_selecttype_" + v.toString()).dataset.poolf = "type_text";
            var element = document.getElementById("choosetype_" + v);
            var str = "<button id=\"buttonnames_" + v.toString() + "\" class=\"btn btn-outline-secondary dropdown-toggle text-white\" type=\"button\" data-toggle=\"dropdown\"" +
                    "                aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf='pf_none'>无</button>" +
                    "                <div class=\"dropdown-menu\">" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_none\">无</a>" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count\">计数</a>" +
                    "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count_norepeat\">非重复计数</a>" +
                    "                </div>";

            element.innerHTML = str;
        }
</script>