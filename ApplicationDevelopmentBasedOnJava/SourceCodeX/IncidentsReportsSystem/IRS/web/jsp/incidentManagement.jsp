<%-- 
    Document   : incidentManagement
    Created on : 2018-1-4, 14:05:52
    Author     : JakeLin
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<script>
    /**
     * 获取事件  
     * @param {type} l2admin
     * @param {type} vsum
     * @returns {undefined}
     */
    function getIncidents(l2admin, vsum) {

        showMsg("正在加载事件...");
        var testHTML = "";
        var incidentStr = new Array();
        //var incidents_tbody = document.getElementById("incidentsList-tbody");   //事件table tbody

        $.get("/IncidentsReport/getIncidents?l2admin=" + l2admin + "&vsum=" + vsum, function (data) {
            //console.log(data);
            dat = data.split("<br/>");  //所有事件信息字符串
            incidentStr = dat[1].split("$");    //事件信息数组字符串
            for (i = 0; i < incidentStr.length - 1; i++) {
                //console.log(incidentStr[i]);
                //返回形式：id---type---credit---description---latlng---roughLocation---reportTime
                //显示形式：id---type---time---credit---description---location---lat---lng    (lat,lng)
                incident = incidentStr[i].split("@");
                //console.log(incident[4] + "   " + typeof(incident[4]));
                latlng = incident[4].split(", ");
                testHTML = testHTML + "<tr id=\"incident-tr-" + incident[0] + "\">" +
                        "<th scope=\"row\"><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[0] + "\">" + incident[0] + "</div></th>" +
                        "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[1] + "\">" +
                        "<input class=\"xunchangable\" id=\"incident-type-" + incident[0] + "\" style=\"text\" value=\"" + incident[1] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>" +
                        "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[6] + "\">" +
                        "<input class=\"xunchangable\"  id=\"incident-time-" + incident[0] + "\" style=\"text\" value=\"" + incident[6] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>" +
                        "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[2] + "\">" +
                        "<input class=\"xunchangable\"  id=\"incident-credit-" + incident[0] + "\" style=\"text\" value=\"" + incident[2] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>" +
                        "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[3] + "\">" +
                        "<input class=\"xunchangable\"  id=\"incident-description-" + incident[0] + "\" style=\"text\" value=\"" + incident[3] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>" +
                        "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[5] + "\">" +
                        "<input class=\"xunchangable\"  id=\"incident-location-" + incident[0] + "\" style=\"text\" value=\"" + incident[5] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>" +
                        "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + latlng[0] + "\">" +
                        "<input class=\"xunchangable\"  id=\"incident-lat-" + incident[0] + "\" style=\"text\" value=\"" + latlng[0] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>" +
                        "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + latlng[1] + "\">" +
                        "<input class=\"xunchangable\"  id=\"incident-lng-" + incident[0] + "\" style=\"text\" value=\"" + latlng[1] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>" +
                        /*        
                         "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[6] + "\">" + incident[6] + "</div></td>"+
                         "<td><div style=\"width: 60px;\" class=\"wrap\" title=\"" + incident[2] + "\">" + incident[2] + "</div></td>"+
                         "<td><div style=\"width: 150px;\" class=\"wrap\" title=\"" + incident[3] + "\">" + incident[3] + "</div></td>"+
                         "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[5] + "\">" + incident[5] + "</div></td>"+
                         "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + latlng[0] + "\">" + latlng[0] + "</div></td>"+
                         "<td><div style=\"width: 100px;\" class=\"wrap\" title=\"" + latlng[1] + "\">" + latlng[1] + "</div></td>"+
                         */
                        "<td id=\"incident-tbody-td-button-" + incident[0] + ">" +
                        "<div style=\"width: 150px;\" class=\"wrap\" id=\"button-one-" + incident[0] + "\">" +
                        "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickIncidentUpdate(" + incident[0] + ")\">修改</button>" +
                        "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickIncidentSubmit(" + incident[0] + "," + l2admin + ")\">提交</button>" +
                        "<button type=\"button\" style=\"height: 30px\" class=\"btn btn-raised btn-secondary\" onclick=\"javascript:deleteIncident(" + l2admin + "," + incident[0] + ")\">删除</button>" +
                        "</div>" +
                        "</td>" +
                        "</tr>\n";
                //console.log(" " + i + " : " + incidentStr.length + "\n"+ testHTML);
            }
            console.log("end for\n" + testHTML);
            document.getElementById("incidentsList-tbody").innerHTML = testHTML;
            showMsg("事件加载完毕！");
        });

    }

    /**
     * 删除事件 指定所属管理员ID  事件ID
     * @param {type} adminID  管理员ID 
     * @param {type} incidentID  事件ID
     * @returns {undefined}
     */
    function deleteIncident(adminID, incidentID) {
        /*
         $.get("/IncidentsReport/deleteIncident?adminID=" + adminID + "&incidentID=" + incidentID, function (data){
         console.log(data);
         });
         */
        showMsg("提交中...");
        $.ajax({
            url: '/IncidentsReport/deleteIncident',
            type: 'post',
            data: {
                "adminID": adminID,
                "incidentID": incidentID
            },
            success: function (data) {
                console.log(data);
                if (data.indexOf("ERROR") > -1) {       //失败返回 ERROR
                    showMsg("删除失败");
                } else {
                    var tr = document.getElementById("incident-tr-" + incidentID);
                    tr.parentNode.removeChild(tr);
                    showMsg("删除成功");
                }
            }
        });
    }


    /**
     * 更新事件信息 
     * @param {type} incident  事件对象
     * @returns {undefined}
     */
    function updateIncident(id, type, time, credit, description, location, lat, lng, l2admin) {

        /*
         *             
         "incidentID" : incident.id,
         "type" : incident.type,
         "time" : incident.reportTime,
         "credit" : incident.credit,
         "description" : incident.description,
         "location" : incident.roughLocation,
         "lat" : incident.latlng.substring(0, incident.latlng.substring(incident.latlng.indexOf(","))),
         "lng" : incident.latlng.substring(0, incident.latlng.substring(incident.latlng.indexOf(",") + 1)),
         "reportedby" : incident.reportedby
         */
        $.get("/IncidentsReport/updateIncident?" +
                "incidentID=" + id +
                "&type+" + type +
                "&time=" + time +
                "&credit=" + credit +
                "&description=" + description +
                "&location=" + location +
                "&lat=" + lat, +
                "&lng=" + lng +
                "&reportedby=" + l2admin,
                function (data) {
                    console.log(data);
                    if (data.indexOf("ERROR") > -1) {       //失败返回 ERROR
                        showMsg("事件更新失败，请重试");
                    } else {
                        showMsg("事件更新成功");
                    }
                });
    }

    /**
     * 
     * @param {type} incidentID
     * @returns {undefined}
     */
    function onClickIncidentUpdate(incidentID) {

        document.getElementById("incident-type-" + incidentID).readOnly = false;
        document.getElementById("incident-time-" + incidentID).readOnly = false;
        document.getElementById("incident-credit-" + incidentID).readOnly = false;
        document.getElementById("incident-description-" + incidentID).readOnly = false;
        document.getElementById("incident-location-" + incidentID).readOnly = false;
        document.getElementById("incident-lat-" + incidentID).readOnly = false;
        document.getElementById("incident-lng-" + incidentID).readOnly = false;

        document.getElementById("incident-type-" + incidentID).classList.add("xchangable");
        document.getElementById("incident-time-" + incidentID).classList.add("xchangable");
        document.getElementById("incident-credit-" + incidentID).classList.add("xchangable");
        document.getElementById("incident-description-" + incidentID).classList.add("xchangable");
        document.getElementById("incident-location-" + incidentID).classList.add("xchangable");
        document.getElementById("incident-lat-" + incidentID).classList.add("xchangable");
        document.getElementById("incident-lng-" + incidentID).classList.add("xchangable");
    }

    /**
     * 
     * @param {type} incidentID
     * @returns {undefined}
     */
    function onClickIncidentSubmit(incidentID, l2admin) {
        type = document.getElementById("incident-type-" + incidentID).value;
        time = document.getElementById("incident-time-" + incidentID).value;
        credit = document.getElementById("incident-credit-" + incidentID).value;
        description = document.getElementById("incident-description-" + incidentID).value;
        loc = document.getElementById("incident-location-" + incidentID).value;
        lat = document.getElementById("incident-lat-" + incidentID).value;
        lng = document.getElementById("incident-lng-" + incidentID).value;


        updateIncident(incidentID, type, time, credit, description, loc, lat, lng, l2admin);

        document.getElementById("incident-type-" + incidentID).readOnly = false;
        document.getElementById("incident-time-" + incidentID).readOnly = false;
        document.getElementById("incident-credit-" + incidentID).readOnly = false;
        document.getElementById("incident-description-" + incidentID).readOnly = false;
        document.getElementById("incident-location-" + incidentID).readOnly = false;
        document.getElementById("incident-lat-" + incidentID).readOnly = false;
        document.getElementById("incident-lng-" + incidentID).readOnly = false;
    }
function createIncident(l2admin){
        var tr = document.createElement("tr");
        tr.setAttribute("id", "incident-tr-two-999999");
        tr.innerHTML = "<th scope=\"row\"><div style=\"width: 70px;\" class=\"wrap\" title=\"" + 999999 + "\">" + 999999 + "</div></th>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + "" + "\">" +
                                        "<input id=\"incident-type-" + 999999 + "\" style=\"text\" value=\""+"type" +"\"  style=\"border: 0px\">" + " </div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + "" + "\">" +
                                        "<input id=\"incident-time-" + 999999 + "\" style=\"text\" value=\""+"time" +"\"  style=\"border: 0px\">" + " </div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + "" + "\">" +
                                        "<input id=\"incident-credit-" + 999999 + "\" style=\"text\" value=\""+"credit" +"\"  style=\"border: 0px\">" + " </div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + "" + "\">" +
                                        "<input id=\"incident-description-" + 999999 + "\" style=\"text\" value=\"description"+"" +"\"  style=\"border: 0px\">" + " </div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + "" + "\">" +
                                        "<input id=\"incident-location-" + 999999 + "\" style=\"text\" value=\""+"location" +"\"  style=\"border: 0px\">" + " </div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + "" + "\">" +
                                        "<input id=\"incident-lat-" + 999999 + "\" style=\"text\" value=\""+"lat" +"\"  style=\"border: 0px\">" + " </div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + "" + "\">" +
                                        "<input id=\"incident-lng-" + 999999 + "\" style=\"text\" value=\""+"lng" +"\"  style=\"border: 0px\">" + " </div></td>"+
                                /*        
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[6] + "\">" + incident[6] + "</div></td>"+
                                    "<td><div style=\"width: 60px;\" class=\"wrap\" title=\"" + incident[2] + "\">" + incident[2] + "</div></td>"+
                                    "<td><div style=\"width: 150px;\" class=\"wrap\" title=\"" + incident[3] + "\">" + incident[3] + "</div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + incident[5] + "\">" + incident[5] + "</div></td>"+
                                    "<td><div style=\"width: 70px;\" class=\"wrap\" title=\"" + latlng[0] + "\">" + latlng[0] + "</div></td>"+
                                    "<td><div style=\"width: 100px;\" class=\"wrap\" title=\"" + latlng[1] + "\">" + latlng[1] + "</div></td>"+
                                */
                                    "<td id=\"incident-tbody-td-button-" + 999999 + ">" +
                                           "<div style=\"width: 150px;\" class=\"wrap\" id=\"button-one-" + 999999 + "\">" +
                                             //  "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickIncidentUpdate(" + 999999 + ")\">修改</button>" +
                                               "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:addIncident("+ 999999 +"," + l2admin + ")\">提交</button>" +
                                            //   "<button type=\"button\" style=\"height: 30px\" class=\"btn btn-raised btn-secondary\" onclick=\"javascript:deleteIncident(" + l2admin + "," + 999999 + ")\">删除</button>" +
                                           "</div>" +
                                           
                                       "</td>";
             document.getElementById("incidentsList-tbody").appendChild(tr);
             console.log(tr.innerHTML);
    }
    
    
    function addIncident(incidentID, l2admin){
        type = document.getElementById("incident-type-" + incidentID).value;
        time = document.getElementById("incident-time-" + incidentID).value;
        credit = document.getElementById("incident-credit-" + incidentID).value;
        description = document.getElementById("incident-description-" + incidentID).value;
        loc = document.getElementById("incident-location-" + incidentID).value;
        lat = document.getElementById("incident-lat-" + incidentID).value;
        lng = document.getElementById("incident-lng-" + incidentID).value;
        console.log(type+" "+time+" "+credit+" "+description+" "+loc+" "+lat+" "+lng+" "+l2admin );
        
        /*
        $.get("/IncidentsReport/addIncident?type="+type+"&time="+time+"&credit="+credit+"&description="+description+"&location="+location+"&lat="+lat+"&lng="+lng+"&l2admin="+l2admin,
         function (data){
             if(data.indexOf("ERROR") > -1){
                 showMsg("添加失败!");
             }else{
                 showMsg("添加成功！");
                 
             }
         });
        */
       $.ajax({
            url: '/IncidentsReport/addIncident',
            type: 'post',
            data:{
            'type':type,
            'time':time,
            'credit':credit,
            'description':description,
            'location=':loc,
            'lat':lat,
            'lng':lng,
            'l2admin':l2admin
            },
            success: function (data){
             if(data.indexOf("ERROR") > -1){
                 showMsg("添加失败!");
             }else{
                 showMsg("添加成功！");
                 
             }
         }
        });
       
    }
    
    
    

    /**
     * 
     * @param {type} msg
     * @returns {undefined}
     */
    function showMsg(msg) {
        $.snackbar({content: msg});
    }

</script>
