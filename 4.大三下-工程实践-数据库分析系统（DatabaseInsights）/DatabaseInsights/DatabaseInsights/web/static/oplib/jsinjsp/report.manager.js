/* 
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 07 2018
 *
 * 这里整合了属于 console/report.jsp 的js代码
 */

function getReports() {
    GetDataF("getReport?gtype=1", function error(data) {
        showMsg("loading error :" + data.message);
    }, function success(data) {
        $("#reportscontainer").html(data.data[0]);
    });
}

function view(rownum) {
    rownum += 1;
    var repid = $(GetTableRow("report_table", rownum).cells[5]).find(".report-id").val();
    var w = window.open('report.viewfull.jsp?repid=' + repid, "report title", "height=640,width=1024");
}

function del(repid, tip) {
    if (tip) {
        $('#delconfirm').modal('show');
        $("#delcon").click(function a() {
            del(repid, false);
        });
    } else {
        //delete
        console.log("delete id=" + repid);
        $('#delconfirm').modal('hide');
        GetDataF("/deleteReport?repid=" + repid, function error(data) {
            showMsg("error in deleting : " + data.message);
        }, function success(data) {
            showMsg(data.message);
            $("#rep_" + repid).remove();
        });
    }
}

function inspect(rownum) {
    rownum += 1;
    $("#modelinfo_title").html($(GetTableRow("report_table", rownum).cells[5]).find(".report-fulltitle").val());
    $("#modelinfo_created").html(GetCellValues("report_table", rownum, 3));
    $("#modelinfo_des").html($(GetTableRow("report_table", rownum).cells[5]).find(".report-fulldes").val());
    $("#modelinfo_ralation").html($(GetTableRow("report_table", rownum).cells[5]).find(".report-relations").val());
    $("#viewfullreport").click(function a() {
        view(rownum-1);
    });
    $('#exampleModalCenter').modal('show');
}


