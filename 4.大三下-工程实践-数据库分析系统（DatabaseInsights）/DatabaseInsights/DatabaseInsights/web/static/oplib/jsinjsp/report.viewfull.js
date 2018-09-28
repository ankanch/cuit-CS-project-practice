/* 
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 08 2018
 *
 * 存放查看报告详细信息页面的js代码
 */
var CHART_CONTAINER = `<div class="card">
                <div class="card-body">
                    <div id="@ID" style="width:60%;min-width: 600px;height:400px;display:inline-block;"></div>
                    <div class="notes" style="width:30%;min-width:200px;height:400px;display:inline-block;">
                        <textarea class="form-control" rows="14" >@DES</textarea>
                    </div>
                </div>
            </div>`;

var CHART_CONTAINER0 = `<div class="card">
                <div class="card-body">
                    <div id="@ID" style="width:60%;min-width: 600px;height:400px;display:inline-block;"></div>
                    <div class="notes" style="width:30%;min-width:200px;height:400px;display:inline-block;">
                        <textarea class="form-control" rows="14">@DES</textarea>
                    </div>
                </div>
            </div>`;
var CHART_CONTAINER1 =  `<div class="card">
                <div class="card-body">
                    <div class="notes" style="width:30%;min-width:200px;height:400px;display:inline-block;">
                        <textarea class="form-control" rows="14">@DES</textarea>
                    </div>
                    <div id="@ID" style="width:60%;min-width: 600px;height:400px;display:inline-block;"></div>
                </div>
            </div>`;

var CHART_CONTAINER_NODES =  `<div class="card">
                <div class="card-body">
                    <div id="@ID" style="width:100%;min-width: 600px;height:400px;display:inline-block;"></div>
                </div>
            </div>`;

function getReport(repid) {
    setProgressBar(true);
    showMsg("Loading report...");
    console.log("loading report..\t id=" + repid);
    GetDataF("getReport?repid=" + repid, function error(data) {
        showMsg("loading error :" + data.message);
    }, function success(data) {
        console.log(data.data);
        $("#report_title").val(data.data[0][0]);
        $("#report_des").val(data.data[0][1]);
        //$("#id").val(data.data[0][2]);
        for (var i = 0; i < data.data[1].length; i++) {
            var chtid = "cht_" + i;
            console.log("process " + i + "\t with id of " + chtid);
            if(data.data[1][i].length > 28){
                CHART_CONTAINER = getlayout();
            }else{
                CHART_CONTAINER = CHART_CONTAINER_NODES;
            }
            var chtcontainer = CHART_CONTAINER.replace("@ID", chtid).replace("@DES",data.data[1][i]);
            $("#report_content").append(chtcontainer);
            option = eval(data.data[2][i]);
            initChartWithOption(chtid, option);
        }
        setProgressBar(false);
    });
}

function getlayout(){
    var v = Math.floor(Math.random() * 2);
    if(v == 0){
        return CHART_CONTAINER0;
    }else if(v == 1){
        return CHART_CONTAINER1;
    }
}

getReport(findGetParameter("repid"));

