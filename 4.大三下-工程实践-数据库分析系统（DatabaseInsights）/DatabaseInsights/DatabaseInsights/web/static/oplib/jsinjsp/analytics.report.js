/* 
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 06 2018
 *
 * 该文件负责首先分析完成后，生成 保存/下载报告的fab按钮，以及开始分析到得到分析结果这一段的逻辑
 */
//用于添加标题头和报告描述头
var REPORT_HEAD = `<div class="notes" style="width:1000px;height:150px;display:inline-block;">
                        <input type="text" class="form-control console-reporttitle-input" id="report_title" placeholder="Add report title here." style="text-align: center;font-size: 3rem;font-weight: 600;">
                        <textarea class="form-control" id="report_des" rows="4" placeholder="Write some description about this report." style="font-size: 1.1rem;"></textarea>
                   </div>`;

//报告生成后右下角的fab按钮
var CHART_CONTAINER_SAVE_REPORT = `<hr/><button type="button" class="btn btn-info bmd-btn-fab btn-raised console-floatbtn-rb-1" onclick="savereport()">
                                        <i class="material-icons">save</i><div class="ripple-container"></div>
                                       </button>
                                        <button type="button" class="btn btn-danger bmd-btn-fab console-floatbtn-rb-2" onclick="downloadreport()">
                                        <i class="material-icons">save_alt</i><div class="ripple-container"></div>
                                       </button>`;

// 用于下载生成的报告
function downloadreport() {
    window.print();
}

//用于使用邮件发送报告
function emailreport(send){
    if(send){
        $("#send").attr("disabled", "disabled");
        var emailaddr = $("#useremail").val(); 
        var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
        if( re.test(String(emailaddr).toLowerCase()) == false){
            showMsg("Please enter a valid email address");
            $("#send").removeAttr("disabled");
            return;
        }
        // send to sevlet
        SubmitFormKVF("sendReport", {repid:findGetParameter("repid"),email:emailaddr}, function error(data){
            $("#send").removeAttr("disabled");
            showMsg(data.message);
        }, function success(data){
            $("#send").removeAttr("disabled");
            showMsg(data.message);
            $("#emailModal").modal("hide")
        });
    }else{
        $("#emailModal").modal()
    }
}

// 用于保存报告到数据库
function savereport() {
    // 所有报告信息都存放在 chartslist 中
    var noteslist = [];
    var optionlist = [];
    $("#chartslist > div > div > div.notes > textarea").each(function () {
        noteslist.push($(this).val());
    });
    $("#chartslist > div > div > div.option").each(function () {
        optionlist.push( $(this).html());
    });
    var data = [noteslist,optionlist];
    var chartsdata = DBIEX.toString(data);
    var title = $("#report_title").val();
    var des = $("#report_des").val();
    var relation = choosed_db + "->" + choosed_table + ";";
    if(title.length < 1){
        title = "no title specified";
    }
    if(des.length < 1){
        des = " ";
    }
    var repdata = encodeReport(title,des,chartsdata,relation);
    if(repdata.length < 110 ){
        showMsg("no charts selected!");
        return;
    }
    // send to sevlet
    SubmitFormKVF("addReport", {repdata:repdata}, function error(data){
        showMsg(data.message);
    }, function success(data){
        showMsg(data.message);
    });

}


function encodeReport(title,des,chtdata,relations){
    return title + "<@REPSP!>" + des + "<@REPSP!>" + chtdata + "<@REPSP!>" + relations;
}