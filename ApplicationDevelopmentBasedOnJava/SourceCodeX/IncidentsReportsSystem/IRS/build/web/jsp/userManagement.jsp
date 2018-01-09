<%-- 
    Document   : userManagement
    Created on : 2018-1-4, 17:57:06
    Author     : JakeLin
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<script>
    /**
     * 获取订阅用户 显示
     * @returns {undefined}
     */
    function getUsers(){
        $.get("/IncidentsReport/getUser", function (data){
            //console.log(data);
            var dat = data.split("<br/>");
                /**
                        user.user_ID + "#" +
                        user.user_email + "#" + 
                        user.user_status + "#" + 
                        user.user_location + "$";
                 */
            var userList = dat[1].split("$");
            var textHTML = "";
            for(i = 0; i < userList.length -1; i++){
                //console.log(userList[i]);
                user = userList[i].split("#");
                                /**
                                  <tr id="ordersList-tr-1">
                                    <th scope="row">1</th>
                                    <td>test1@qq.com</td>
                                    <td>1</td>
                                    <td>Chengdu</td>
                                  </tr>     
                                */
                textHTML += "<tr id=\"ordersList-tr-" + user[0] + "\">" +
                                "<th scope=\"row\">" + user[0] + "</th>" +
                                "<td>" + user[1] + "</td>"+ 
                                "<td>" + user[2] + "</td>" + 
                                "<td>" + user[3] + "</td>" + 
                                "</tr>\n";
            }
            console.log(textHTML);
            document.getElementById("ordersList-tbody").innerHTML = textHTML;
        });
    }
    
</script>
