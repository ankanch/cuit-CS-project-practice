<%-- 
    Document   : l2adminmanagement
    Created on : 2018-1-4, 14:10:23
    Author     : JakeLin
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>

<script>
    /**
     * 新增二级管理员 
     * @param {type} name 
     * @param {type} password
     * @returns {undefined}
     */
    function addL2admin(l2adminID){
         showMsg("正在提交...");
         console.log("id=" + l2adminID);
        name = document.getElementById("l2admin-name-" + l2adminID).value;
        password = document.getElementById("l2admin-password-" + l2adminID).value;
         $.get("/IncidentsReport/addL2admin?name=" + name + "&password=" + password, function (data){
             //console.log(data);
             dat = data.split("<br/>");
             l2admin = dat[1].split("@");
             var tr = document.createElement("tr");
             tr.setAttribute("id", "l2admin-tr-two-" + l2admin[0]);
             tr.innerHTML = //"<tr id=\"l2admin-tr-two-" + l2admin[0] + "\">"+
                                            "<th scope=\"row\">"+
                                            "<div class=\"wrap\" title=\"" + l2admin[0] + "\">" + l2admin[0] + " </div></th>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-name-" + l2admin[0] + "\" type=\"text\" value=\"" + l2admin[1] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-password-" + l2admin[0] + "\" type=\"text\" value=\"" + l2admin[2] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-status-" + l2admin[0] + "\" type=\"text\" value=\"" + l2admin[3] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>"+
                                           "<td id=\"l2admin-tbody-td-button-" + l2admin[0] + ">" +                                          
                                           "<div style=\"width: 150px;\" class=\"wrap\" id=\"l2admin-button-two-" + l2admin[0] + "\">" +
                                               "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickUpdate(" + l2admin[0] + ")\">修改</button>" +
                                               "<button id=\"l2admin-update-" + l2admin[0] + "\" type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickSubmit(" + l2admin[0] + ")\">提交</button>" +
                                               "<button type=\"button\" style=\"height: 30px\" class=\"btn btn-raised btn-secondary\" onclick=\"javascript:deleteL2admin(" + l2admin[0] + ")\">删除</button>" +
                                               
                                           "</div>" +
                                          
                                            "</td>";
             document.getElementById("l2adminsList-tbody").appendChild(tr);
             
             tr = document.getElementById("l2admin-tr-two-" + l2adminID);
             tr.parentNode.removeChild(tr);
             showMsg("添加成功!");
         });
    }
    
    
    /**
     * 获取二级管理员信息
     * @returns {undefined}
     */
    function getL2admin(){
         showMsg("正在加载二级管理员信息...");
         $.get("/IncidentsReport/getL2admin", function (data){
             var textHTML = "";
             dat = data.split("<br/>");
             /**
                        Integer.toString(l2admin.id) + "@" 
                        + l2admin.name + "@" 
                        + l2admin.password + "@"
                        + Integer.toString(l2admin.status) + "$";
              */
             var l2adminList = dat[1].split("$");
             var indexString = "";
             for(i = 0; i < l2adminList.length - 1; i++){
                 l2admin = l2adminList[i].split("@");
                                 /**
                                  <tr>
                                    <th scope="row"><div class="wrap" title="1">12134124343fdfsdgfgd6543653456</div></th>
                                    <td><div class="wrap" title="2">markdfsdgfsghgfdgffdgfdgfddgfhhfdhfdh</div></td>
                                    <td><div class="wrap" title="3">4234we423534gfdgfdgfdggfdgfd4534</div></td>
                                    <td><div class="wrap" title="4">12134124343654gdgdffgfd3653456</div></td>
                                    <td><div style="width: 150px;" class="wrap" id="firstButton">
                                               <button type="button" style="margin-right: 5px;height: 30px;" class="btn btn-raised btn-primary" onclick="showButton('Button1')">修改</button>
                                               <button type="button" style="height: 30px" class="btn btn-raised btn-secondary" onclick="showButton('Button2')">删除</button>
                                           </div>
                                           <div style="width: 150px;" class="wrap" id="secondButton">
                                               <button style="margin-right: 5px;height: 30px;" class="btn btn-raised btn-primary" type="button" value="保存" onclick="showButton('Button3')">提交</button>
                                               <button style="height: 30px" class="btn btn-raised btn-secondary" type="button" value="取消" onclick="showButton('Button4')">取消</button>
                                           </div>
                                    </td>
                                  </tr>       
                                */
                 indexString += l2admin[0] + "$";
                 textHTML = textHTML + 
                     //    "<div id=\"l2admin-div-one-" + l2admin[0] + "\">"+
                      /*      "<tr id=\"l2admin-tr-one-" + l2admin[0] + "\">"+
                            "<th scope=\"row\"><div class=\"wrap\" title=\"" + l2admin[0] + "\">" + l2admin[0] + " </div></th>"+
                             "<td><div class=\"wrap\" title=\"" + l2admin[1] + "\">" + l2admin[1] + " </div></td>"+
                             "<td><div class=\"wrap\" title=\"" + l2admin[2] + "\">" + l2admin[2] + " </div></td>"+
                             "<td><div class=\"wrap\" title=\"" + l2admin[3] + "\">" + l2admin[3] + " </div></td>"+
                            "<td id=\"l2admin-tbody-td-button-" + l2admin[0] + ">" +
                                "<div style=\"width: 150px;\" class=\"wrap\" id=\"l2admin-button-one-" + l2admin[0] + "\">" +
                                    "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickUpdate(" + l2admin[0] + ")\">修改</button>" +
                                    "<button type=\"button\" style=\"height: 30px\" class=\"btn btn-raised btn-secondary\" onclick=\"javascript:deleteL2admin(" + l2admin[0] + ")\">删除</button>" +
                                "</div>" +
                            "</td>"+
                            "</tr>\n" +
                       */
                                  //      "<div id=\"l2admin-div-two-" + l2admin[0] + "\">"+
                                          "<tr id=\"l2admin-tr-two-" + l2admin[0] + "\">"+
                                            "<th scope=\"row\">"+
                                            "<div class=\"wrap\" title=\"" + l2admin[0] + "\">" + l2admin[0] + " </div></th>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-name-" + l2admin[0] + "\" type=\"text\" value=\"" + l2admin[1] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-password-" + l2admin[0] + "\" type=\"text\" value=\"" + l2admin[2] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-status-" + l2admin[0] + "\" type=\"text\" value=\"" + l2admin[3] + "\" readOnly=\"true\" style=\"border: 0px\">" + " </div></td>"+
                                           "<td id=\"l2admin-tbody-td-button-" + l2admin[0] + ">" +                                          
                                           "<div style=\"width: 150px;\" class=\"wrap\" id=\"l2admin-button-two-" + l2admin[0] + "\">" +
                                               "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickUpdate(" + l2admin[0] + ")\">修改</button>" +
                                               "<button id=\"l2admin-update-" + l2admin[0] + "\" type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickSubmit(" + l2admin[0] + ")\">提交</button>" +
                                               "<button type=\"button\" style=\"height: 30px\" class=\"btn btn-raised btn-secondary\" onclick=\"javascript:deleteL2admin(" + l2admin[0] + ")\">删除</button>" +
                                               
                                           "</div>" +
                                          
                                            "</td>"+
                                            "</tr>\n";
             }
             //console.log(textHTML);
             document.getElementById("l2adminsList-tbody").innerHTML = textHTML;
             //console.log(indexString);
             index = indexString.split("$");
             for(i = 0; i < index.length - 1; i++){
                //console.log("l2admin-tr-two-" + index[i]);
             //   document.getElementById("l2admin-tr-two-" + index[i]).style.display="none";
             }            
             showMsg("加载完成!")
         });
    }
    
    
    function deleteL2admin(l2adminID){
        showMsg("提交中...");
        $.get("/IncidentsReport/deleteL2admin?l2adminID=" + l2adminID, function (data){
           if(data.indexOf("ERROR") > -1){
               showMsg("删除失败！");
           }else{
               showMsg("删除成功!");
               tr = document.getElementById("l2admin-tr-two-" + l2adminID);
               tr.parentNode.removeChild(tr);
           }
        });
    }
    
    function onClickUpdate(l2adminID){
        console.log("l2admin-name-" + l2adminID);
        //document.getElementById("l2admin-tr-two-" + l2adminID).style.display="block";
       // document.getElementById("l2admin-tr-one-" + l2adminID).style.display="none";
       
     //  document.getElementById("l2admin-name-" + l2adminID).readOnly = false;
       document.getElementById("l2admin-password-" + l2adminID).readOnly = false;
    //   document.getElementById("l2admin-status-" + l2adminID).readOnly = false;
    }
        
    function onClickSubmit(l2adminID){
        console.log("l2admin-name-"  + l2adminID);
      //  name = document.getElementById("l2admin-name-" + l2adminID).value;
        password = document.getElementById("l2admin-password-" + l2adminID).value;
      //  status = document.getElementById("l2admin-status-" + l2adminID).value;
    //   console.log(name+" " + password +" "+status)
       
       $.get("/IncidentsReport/updateL2admin?l2adminID="+l2adminID+"&password="+password, function (data){
          if(data.indexOf("ERROR") > -1){
              showMsg("操作失败，请重新提交！");
          } else{
              showMsg("操作成功!");
          }
       });
       
      // document.getElementById("l2admin-name-" + l2adminID).readOnly = true;
       document.getElementById("l2admin-password-" + l2adminID).readOnly = true;
     //  document.getElementById("l2admin-status-" + l2adminID).readOnly = true;
    }
    
        function createL2admin(){
             var tr = document.createElement("tr");
             tr.setAttribute("id", "l2admin-tr-two-9999");
             tr.innerHTML = //"<tr id=\"l2admin-tr-two-" + l2admin[0] + "\">"+
                                            "<th scope=\"row\">"+
                                            "<div class=\"wrap\" > $ </div></th>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-name-" + 9999 + "\" type=\"text\" value=\"" + "$name"+ "\"  style=\"border: 3px\">" + " </div></td>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-password-" + 9999 + "\" type=\"text\" value=\"" + "$password"  + "\"  style=\"border: 3px\">" + " </div></td>"+
                                            "<td><div class=\"wrap\" >" + "<input id=\"l2admin-status-" + 9999 + "\" type=\"text\" value=\""  + "\" readOnly=\"true\" style=\"border: 3px\">" + " </div></td>"+
                                           "<td id=\"l2admin-tbody-td-button-" + 9999 + ">" +                                          
                                           "<div style=\"width: 150px;\" class=\"wrap\" id=\"l2admin-button-two-" + 9999 + "\">" +
                                            //   "<button type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:onClickUpdate(" + l2admin[0] + ")\">修改</button>" +
                                               "<button id=\"l2admin-update-" + 9999 + "\" type=\"button\" style=\"margin-right: 5px;height: 30px;\" class=\"btn btn-raised btn-primary\" onclick=\"javascript:addL2admin(" + 9999 + ")\">提交</button>" +
                                            //   "<button type=\"button\" style=\"height: 30px\" class=\"btn btn-raised btn-secondary\" onclick=\"javascript:deleteL2admin(" + l2admin[0] + ")\">删除</button>" +
                                               
                                           "</div>" +
                                          
                                            "</td>";
             document.getElementById("l2adminsList-tbody").appendChild(tr);
             console.log(tr.innerHTML);
        }
    
    function showMsg(msg) {
        $.snackbar({content: msg});
    }
    
</script>
