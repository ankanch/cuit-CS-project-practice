<%-- 
    Document   : settings
    Created on : Mar 4, 2018, 7:27:06 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="dbi.localization.lang"%>
<%@page import="java.util.HashMap"%>
<%@page import="dbi.mgr.user.UserManager"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%
    UserManager um1 = new UserManager();
    HashMap<String, String> hm = um1.getUserInfo(lang.detectLang(request),session.getId());
    lang local = lang.detectLang(request);
%>
<div id="settings">
    <h2><%=local.getString(langID.JSP_CONSOLE_SETTINGS_TITLE)  %></h2>
    <div class="card mb-3 pl-5 pr-5">
        <div class="card-body pl-5 pr-5">
            <p><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_REGISTEDON)  %>: April 22 2017<%= request.getLocale() %></p>
            <p><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_STATUS)  %>: <%=hm.get("STATUS")%></p>
            <p><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_LASTLOGIN)  %>: <%=hm.get("LASTLOGIN")%></p>
        </div>
    </div>
    <div class="card mb-3 pl-5 pr-5">
        <div class="card-body pl-5 pr-5">
            <div class="row">
                <form class="console-mw-500 col-md-8">
                    <div class="form-group is-focused bmd-form-group">
                        <label for="settings_username" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_USERNAME)  %></label>
                        <input type="text" class="form-control console-table-input" id="settings_username" disabled value="<%=hm.get("USERNAME")%>">
                        <span class="bmd-help"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_TIP_USERNAME)  %></span>
                    </div>
                    <div class="form-group">
                        <label for="settings_email" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_EMAIL)  %></label>
                        <input type="email" class="form-control" id="settings_email" value="<%=hm.get("EMAIL")%>">
                        <span class="bmd-help"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_TIP_EMAIL)  %></span>
                    </div>
                </form>
                <div class="col-md-4 ">
                    <button type="button" class="btn btn-raised btn-success " onclick="changeInfo(true);"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_BUTTON_SAVE)  %></button>
                </div>
            </div>
        </div>
    </div>
    <div class="card mb-3 pl-5 pr-5">
        <div class="card-body pl-5 pr-5">
            <div class="row">
                <form class="console-mw-500 col-md-8">
                    <div class="form-group">
                        <label for="settings_oldpassword" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_OLDPASSWORD)  %></label>
                        <input type="password" class="form-control" id="settings_oldpassword">
                    </div>
                    <div class="form-group">
                        <label for="settings_newpassword" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_NEWPASSWORD)  %></label>
                        <input type="password" class="form-control" id="settings_newpassword">
                    </div>
                    <div class="form-group">
                        <label for="settings_confirmnewpassword" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_COMFIRM_NEWPASSWORD)  %></label>
                        <input type="password" class="form-control" id="settings_confirmnewpassword">
                    </div>
                </form>
                <div class="col-md-4 ">
                    <button type="button" class="btn btn-raised btn-success " onclick="changeInfo(false);"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_BUTTON_SAVE)  %></button>
                </div>
            </div>
        </div>
    </div>
    <div class="card mb-3 pl-5 pr-5">
        <div class="card-body pl-5 pr-5">
            <button type="button" class="btn btn-raised btn-danger"><%=local.getString(langID.JSP_CONSOLE_SETTINGS_LABEL_WARNING)  %>
        </div>
    </div>
</div>
<script>
    $('#settings').bootstrapMaterialDesign();

    // true for password,
    // false for username
    function changeInfo(typex) {
        if (typex == true) {
            // change email
            var nemail = $("#settings_email").val();
            SubmitFormKVF("/api/UpdateUserinfo", {typex: "email", email:nemail}, function error(data) {
                showMsg("Failed to change email,please try again later!");
            }, function success(data) {
                showMsg("Your email now has been changed!");
            });
        } else {
            // change password
            var newpwd = $("#settings_newpassword").val();
            var oldpwd = $("#settings_oldpassword").val();
            var comfirmpwd = $("#settings_confirmnewpassword").val();
            if(newpwd != comfirmpwd || newpwd.length <3){
                showMsg("Password does not match!");return;
            }
            SubmitFormKVF("/api/UpdateUserinfo", {typex: "pwd", npwd:newpwd ,opwd:oldpwd}, function error(data) {
                showMsg("Failed to change password, please try again later(You may enter a wrong old password)!");
            }, function success(data) {
                showMsg("Your password now has been changed!");
            });
        }
    }

</script>