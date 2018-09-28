<%-- 
    Document   : logs
    Created on : Mar 4, 2018, 8:50:39 PM
    Author     : kanch
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<div id="logs">
    <div class="card">
        <div class="card-body">
            <button type="button" class="btn btn-raised btn-primary" style="width:20%">导出为csv文件</button>
            <button class="btn btn-raised btn-primary dropdown-toggle" type="button" id="dropdownMenuButton" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                6个月
            </button>
              <div class="dropdown-menu" aria-labelledby="dropdownMenuButton">
                <a class="dropdown-item" href="#" id="7d" onclick="chooseTime('7d',this)">7天</a>
                <a class="dropdown-item" href="#" id="1m" onclick="chooseTime('1m',this)">1个月</a>
                <a class="dropdown-item" href="#" id="6m" onclick="chooseTime('6m',this)">6个月</a>
                <a class="dropdown-item" href="#" id="1y" onclick="chooseTime('1y',this)">1年</a>
                <a class="dropdown-item" href="#" id="all" onclick="chooseTime('all',this)">全部</a>
              </div>
           
        </div>
    </div>

    <div class="card" id="tablecontent">
        
    </div>
</div>
<script>
    $('#logs').bootstrapMaterialDesign();
    
    function chooseTime(v,q){
        var element = document.getElementById(q.id).innerText;
        document.getElementById("dropdownMenuButton").innerHTML=element;
        SubmitFormKVF("/getLogs",{time:v} , function error(data) {
            showMsg("Failed to load log.");
        }, function success(data) {
            var element = document.getElementById("tablecontent");
            element.innerHTML = data.data[0];
        });
    }
    
    SubmitFormKVF("/getLogs",{time:"6m"} , function error(data) {
            showMsg("Failed to load log.");
        }, function success(data) {
            var element = document.getElementById("tablecontent");
            element.innerHTML = data.data[0];
    });
</script>