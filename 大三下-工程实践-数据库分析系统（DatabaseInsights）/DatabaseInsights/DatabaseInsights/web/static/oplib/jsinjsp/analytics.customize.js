
/* 
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 06 2018
 *
 * 存放 costimizeAnalysis.jsp专用的js代码
 */

// 图表容器，用来存放图表和注释
var CHART_CONTAINER = `<div class="card">
                <div class="card-body">
                    <div id="@ID" style="width: 800px;height:400px;display:inline-block;"></div>
                    <div class="notes" style="width:200px;height:400px;display:inline-block;">
                        <textarea class="form-control" rows="14" placeholder="write notes here if you want to add more information about this chart."></textarea>
                    </div>
                    <div class="option" style="display:none;">@OPTION</div>
                </div>
            </div>`;

function showRowcolnum() {
    var tab = document.getElementById("columnstable");
    var rows = tab.rows.length;
    return rows;
}

// 用于进行报告生成操作
function startAnalyze() {
    var rowcolnum = showRowcolnum() - 1;
    var fields = "", type = "", summary = "", instructions = "", lastfields = "";
    for (var i = 1; i < rowcolnum + 1; i++) {
        lastfields = lastfields + document.getElementById("lastfield_" + i.toString()).value + ",";
        fields = fields + document.getElementById("field_" + i.toString()).value + ",";
        type = type + document.getElementById("btn_selecttype_" + i.toString()).dataset.poolf + ",";
        summary = summary + document.getElementById("buttonnames_" + i.toString()).dataset.poolf + ",";
        instructions = instructions + document.getElementById("instructions_" + i.toString()).value + " ,";
    }
    SubmitFormKVF("/api/getCostomAnalyzeResult",
        {tname: choosed_table,
        dbname: choosed_db,
        lastfields: lastfields,
        fields: fields,
        type: type,
        summary: summary,
        instructions: instructions},
        function error_func(data) {
            showMsg("error submit data.");
        },
        function success_func(data) {
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
                var chtcontainer = CHART_CONTAINER.replace("@ID", chtid).replace("@OPTION",line[2][i]);
                $("#chartslist").append(chtcontainer);
                option = eval(line[2][i]);
                initChartWithOption(chtid, option);
            }
            $('#collapseTwo').collapse("show");
    });
}

    var choosed_table = "";
    var choosed_db = "";

    function chooseNumber(v) {
        document.getElementById("btn_selecttype_" + v.toString()).innerHTML = "数字";
        document.getElementById("btn_selecttype_" + v.toString()).dataset.poolf = "type_number";
        var element = document.getElementById("choosetype_" + v.toString());
        var str = "<button id=\"buttonnames_" + v.toString() + "\" class=\"btn btn-outline-secondary dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\"" +
                "                aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf='pf_none'>无</button>" +
                "                <div class=\"dropdown-menu\">" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_none\">无</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_avg\" data-text='平均'>平均</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count\">计数</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count_norepeat\">非重复计数</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_max\">最大</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_min\">最小</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_sum\">总和</a>" +
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
        var str = "<button id=\"buttonnames_" + v.toString() + "\" class=\"btn btn-outline-secondary dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\"" +
                "                aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf='pf_none'>无</button>" +
                "                <div class=\"dropdown-menu\">" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_none\">无</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count\">计数</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count_norepeat\">非重复计数</a>" +
                "                </div>";

        element.innerHTML = str;
    }

    function chooseBoolean(v) {
        document.getElementById("btn_selecttype_" + v.toString()).innerHTML = "布尔值";
        document.getElementById("btn_selecttype_" + v.toString()).dataset.poolf = "type_boolean";
        var element = document.getElementById("choosetype_" + v.toString());
        var str = "<button class=\"btn btn-outline-secondary\" type=\"button\" data-toggle=\"dropdown\"" +
                "aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf=\"pf_none\" id=\"buttonnames_" + v.toString() + "\">无</button>";
        element.innerHTML = str;
    }

    function getDatabases() {
        GetDataF("/api/getDatabases", function error(data) {
            showMsg("Failed to load database list.");
        }, function success(data) {
            var list = data.data;
            var element = document.getElementById("showDatabase");
            var st = "<a class=\"dropdown-item\" onclick=\"getTables(this)\" id=\"iddb\">dbname</a>";
            var str = "";
            for (var i = 0; i < list.length; i++) {
                str = str + st.replace("iddb", list[i]).replace("dbname", list[i]);
            }
            element.innerHTML = str;
        });
    }

    function getCharts(v) {
        var tbname = document.getElementById(v.id).innerText;
        choosed_table = tbname;
        document.getElementById("buttonMenu2").innerHTML = tbname;
        var dbname = document.getElementById("buttonMenu1").innerHTML;

        $("#alarmcard").hide();
        $("#columnstable").show();
        SubmitFormKVF("/api/GetTableFields", {dbname: dbname, tbname: tbname}, function error_func(data) {
            showMsg("Failed to load table field list.");
        }, function success_func(data) {
            var element = document.getElementById("DBtbody");
            element.innerHTML = data.data[0];
            document.getElementById("btn_start").style.display = "";
            $('#collapseOne').collapse("show");
        });
    }

    function getTables(v) {
        var dbname = document.getElementById(v.id).innerText;
        choosed_db = dbname;
        document.getElementById("buttonMenu1").innerHTML = dbname;
        SubmitFormKVF("/api/getTables", {dbname: dbname}, function error(data) {
            showMsg("Failed to load table list.");
        }, function success(data) {
            var list = data.data;
            var element = document.getElementById("showTables");
            var st = "<a class=\"dropdown-item\" onclick=\"getCharts(this)\" href=\"#\" id=\"idcolumn\">dbname</a>";
            var str = "";
            for (var i = 0; i < list.length; i++) {
                str = str + st.replace("idcolumn", "dbc" + i).replace("dbname", list[i]);
            }
            element.innerHTML = str;
        });
    }



/* 
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 06 2018
 *
 * 存放 costimizeAnalysis.jsp专用的js代码
 */

// 图表容器，用来存放图表和注释

var disabledcol=[];
var times=[];
var CHART_CONTAINER = `<div class="card">
                <div class="card-body">
                    <div id="@ID" style="width: 800px;height:400px;display:inline-block;"></div>
                    <div class="notes" style="width:200px;height:400px;display:inline-block;">
                        <textarea class="form-control" rows="14" placeholder="write notes here if you want to add more information about this chart."></textarea>
                    </div>
                    <div class="option" style="display:none;">@OPTION</div>
                </div>
            </div>`;

// 用于将图表option实例化
function initChartWithOption(id, option) {
    var myChart = echarts.init(document.getElementById(id));
    myChart.setOption(option);
}

function showRowcolnum() {
    var tab = document.getElementById("columnstable");
    var rows = tab.rows.length;
    return rows;
}

// 用于进行报告生成操作
function startAnalyze() {
    var rowcolnum = showRowcolnum() - 1;
    var fields = "", type = "", summary = "", instructions = "", lastfields = "";
    var continued=false;
    for (var i = 1; i < rowcolnum + 1; i++) {
        for (var j=0;j<disabledcol.length;j++){
            console.log("disabledcol,j:"+disabledcol[j]+" "+i);
            if(disabledcol[j].toString()===i.toString()){
                console.log("disabledcol==j");
                continued=true;
                break;
            }
        }
        if(continued===true){
            continued=false;
            continue;
        }
        lastfields = lastfields + document.getElementById("lastfield_" + i.toString()).value + ",";
        fields = fields + document.getElementById("field_" + i.toString()).value + ",";
        type = type + document.getElementById("btn_selecttype_" + i.toString()).dataset.poolf + ",";
        summary = summary + document.getElementById("buttonnames_" + i.toString()).dataset.poolf + ",";
        instructions = instructions + document.getElementById("instructions_" + i.toString()).value + " ,";
    }
    SubmitFormKVF("/api/getCostomAnalyzeResult",
        {tname: choosed_table,
        dbname: choosed_db,
        lastfields: lastfields,
        fields: fields,
        type: type,
        summary: summary,
        instructions: instructions},
        function error_func(data) {
            showMsg("error submit data.");
        },
        function success_func(data) {
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
                var chtcontainer = CHART_CONTAINER.replace("@ID", chtid).replace("@OPTION",line[2][i]);
                $("#chartslist").append(chtcontainer);
                option = eval(line[2][i]);
                initChartWithOption(chtid, option);
            }
            $('#collapseTwo').collapse("show");
    });
}

    var choosed_table = "";
    var choosed_db = "";
    
    function chooseNumber(v) {
        document.getElementById("btn_selecttype_" + v.toString()).innerHTML = "数字";
        document.getElementById("btn_selecttype_" + v.toString()).dataset.poolf = "type_number";
        var element = document.getElementById("choosetype_" + v.toString());
        var str = "<button id=\"buttonnames_" + v.toString() + "\" class=\"btn btn-outline-secondary dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\"" +
                "                aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf='pf_none'>无</button>" +
                "                <div class=\"dropdown-menu\">" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_none\">无</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_avg\" data-text='平均'>平均</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count\">计数</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count_norepeat\">非重复计数</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_max\">最大</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_min\">最小</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_sum\">总和</a>" +
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
        var str = "<button id=\"buttonnames_" + v.toString() + "\" class=\"btn btn-outline-secondary dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\"" +
                "                aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf='pf_none'>无</button>" +
                "                <div class=\"dropdown-menu\">" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_none\">无</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count\">计数</a>" +
                "                <a class=\"dropdown-item\" href='javascript:' onclick='choosetypename(this," + v.toString() + ") ' data-poolf=\"pf_count_norepeat\">非重复计数</a>" +
                "                </div>";

        element.innerHTML = str;
    }

    function chooseBoolean(v) {
        document.getElementById("btn_selecttype_" + v.toString()).innerHTML = "布尔值";
        document.getElementById("btn_selecttype_" + v.toString()).dataset.poolf = "type_boolean";
        var element = document.getElementById("choosetype_" + v.toString());
        var str = "<button class=\"btn btn-outline-secondary\" type=\"button\" data-toggle=\"dropdown\"" +
                "aria-haspopup=\"true\" aria-expanded=\"false\" style=\"border-style:none\" data-poolf=\"pf_none\" id=\"buttonnames_" + v.toString() + "\">无</button>";
        element.innerHTML = str;
    }

    function getDatabases() {
        GetDataF("/api/getDatabases", function error(data) {
            showMsg("Failed to load database list.");
        }, function success(data) {
            var list = data.data;
            var element = document.getElementById("showDatabase");
            var st = "<a class=\"dropdown-item\" onclick=\"getTables(this)\" id=\"iddb\">dbname</a>";
            var str = "";
            for (var i = 0; i < list.length; i++) {
                str = str + st.replace("iddb", list[i]).replace("dbname", list[i]);
            }
            element.innerHTML = str;
        });
    }

    function getCharts(v) {
        var tbname = document.getElementById(v.id).innerText;
        choosed_table = tbname;
        document.getElementById("buttonMenu2").innerHTML = tbname;
        var dbname = document.getElementById("buttonMenu1").innerHTML;

        $("#alarmcard").hide();
        $("#columnstable").show();
        SubmitFormKVF("/api/GetTableFields", {dbname: dbname, tbname: tbname}, function error_func(data) {
            showMsg("Failed to load table field list.");
        }, function success_func(data) {
            var element = document.getElementById("DBtbody");
            element.innerHTML = data.data[0].toString().split("***")[0];
            for(var i=0;i<Number(data.data[0].toString().split("***")[1]);i++){
                times.push(1);
            }
            document.getElementById("btn_start").style.display = "";
            $('#collapseOne').collapse("show");
        });
    }

    function getTables(v) {
        var dbname = document.getElementById(v.id).innerText;
        choosed_db = dbname;
        document.getElementById("buttonMenu1").innerHTML = dbname;
        SubmitFormKVF("/api/getTables", {dbname: dbname}, function error(data) {
            showMsg("Failed to load table list.");
        }, function success(data) {
            var list = data.data;
            var element = document.getElementById("showTables");
            var st = "<a class=\"dropdown-item\" onclick=\"getCharts(this)\" href=\"#\" id=\"idcolumn\">dbname</a>";
            var str = "";
            for (var i = 0; i < list.length; i++) {
                str = str + st.replace("idcolumn", "dbc" + i).replace("dbname", list[i]);
            }
            element.innerHTML = str;
        });
    }

    function disabledcolumn(v){
        var button=document.getElementById("antibutton_"+v.toString()); 
        if((times[Number(v)-1])%2===1){
            disabledcol.push(v);
            $("#row_"+v.toString()).css("color","#CD6600");
            $("#field_"+v.toString()).css("color","#CD6600");
            $("#btn_selecttype_"+v.toString()).css("color","#CD6600");
            $("#choosetype_"+v.toString()).css("color","#CD6600");
            $("#instructions_"+v.toString()).css("color","#CD6600");
            $("#buttonnames_"+v.toString()).css("color","#CD6600");
            button.innerText="取消禁用";
        }
        else if((times[Number(v)-1])%2===0){
            var newdisabledcol=[];
            var j=0;
            for(var i=0;i<disabledcol.length;i++){
                if(disabledcol[i].toString()!==v.toString()){
                    newdisabledcol.push(disabledcol[i]);
                }
            }
            disabledcol=newdisabledcol;
            $("#row_"+v.toString()).css("color","#000000");
            $("#field_"+v.toString()).css("color","#000000");
            $("#btn_selecttype_"+v.toString()).css("color","#000000");
            $("#choosetype_"+v.toString()).css("color","#000000");
            $("#instructions_"+v.toString()).css("color","#000000");
            $("#buttonnames_"+v.toString()).css("color","#000000");
            button.innerText="禁用";
        }
        times[Number(v)-1]++;
        for(var jj=0;jj<disabledcol.length;jj++){
            console.log("disabled[v]:"+disabledcol[jj]);
        }
        if(disabledcol.length===0){
            console.log("无");
        }
    }
    


