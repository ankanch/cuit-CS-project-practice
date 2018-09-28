<%-- 
    Document   : credentials
    Created on : Mar 4, 2018, 8:48:37 PM
    Author     : kanch
--%>

<%@page import="dbi.utils.GlobeVar"%>
<%@page import="dbi.utils.DBIResultSet"%>
<%@page import="dbi.mgr.credential.CredentialManager"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<% lang local = lang.detectLang(request);%>
<jsp:useBean id="credential" class="dbi.mgr.credential.CredentialBean" scope="page"/>
<jsp:setProperty name="credential" property="sessionID" value="<%=request.getSession().getId()%>"/>
<jsp:setProperty name="credential" property="lang" value="<%=request.getLocale().toString()%>"/>
<div id="credentials">
    <h2><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TITLE)%></h2>
    <div class="card">
        <div class="progress-line" id="progressbar"></div>
        <div class="card-body" id="credentialscard">
            <div class="row">
                <div class="col-md-4 console-div-text"><p class="console-vc bmd-form-group">
                        <%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_CSUM_PRE)%>
                        <span class="" id="cre_count"><jsp:getProperty name="credential" property="DBcount" /> </span>
                        <%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_CSUM_SUF)%></p>
                </div>
                <div class="col-md-2">
                    <div class="bmd-form-group console-vc">
                        <button type="button" class="btn btn-primary " data-toggle="modal" data-target="#modal_add_credentials"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_BUTTON_ADD)%></button>
                    </div>
                </div>
                <form class="form-inline my-2 my-lg-0 col-md-5 ml-auto mr-0">
                    <div class="form-group console-div-vc">
                        <label for="searchcre" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TIP_SEARCH)%></label>
                        <input type="text" class="form-control" id="searchcre">
                    </div>
                    <span class="form-group bmd-form-group console-div-vc"> <!-- needed to match padding for floating labels -->
                        <button type="submit" class="btn btn-primary"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_BUTTON_SEARCH)%></button>
                    </span>
                </form>
            </div>
            <%@ include file="../dialogs/console_add_credentials.jsp" %>
            <hr>
            <jsp:getProperty name="credential" property="certifications" />
        </div>
    </div>
</div>
<script>
    $('#credentials').bootstrapMaterialDesign();
    $("#progressbar").hide();

    function edit(row) {
        var inputprefix = "credtable_row_" + row + "_col_";
        $("#credtable_row_" + row + "_edit").hide();
        $("#credtable_row_" + row + "_save").show();
        $("#" + inputprefix + "1").removeAttr('disabled');
        $("#" + inputprefix + "2").removeAttr('disabled');
        $("#" + inputprefix + "3").removeAttr('disabled');
        $("#" + inputprefix + "4").removeAttr('disabled');
    }

    function save(row) {
        $("#progressbar").show();
        var inputprefix = "credtable_row_" + row + "_col_";
        
        var dbhost = $("#credtable_row_" + row + "_col_2").val();
        var dbname = $("#credtable_row_" + row + "_col_1").val();
        var dbpwd = $("#credtable_row_" + row + "_col_4").val();
        //send updates to server
        SubmitFormKVF("/api/updateCredential", {cid: row, dbhost: dbhost, dbname: dbname, dbpwd: dbpwd}, function error(data) {
            showMsg("<%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TIP_FAILED_UPDATE)%>");
        }, function success(data) {
            showMsg("<%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TIP_SUCCESS_UPDATE)%>");
            $("#progressbar").hide();
            $("#credtable_row_1_edit").show();
            $("#credtable_row_1_save").hide();
            $("#" + inputprefix + "1").attr('disabled', 'disabled');
            $("#" + inputprefix + "2").attr('disabled', 'disabled');
            $("#" + inputprefix + "3").attr('disabled', 'disabled');
            $("#" + inputprefix + "4").attr('disabled', 'disabled');
        });
    }

    function del(row) {
        $("#progressbar").show();
        //send updates to server
        SubmitFormKVF("/api/deleteCredentials", {cid: row}, function error(data) {
            showMsg("<%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TIP_FAILED_DELETE)%>");
        }, function success(data) {
            showMsg("<%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TIP_SUCCESS_DELETE)%>");
            $("#progressbar").hide();
            $("#credtable_row_" + row).remove();
        });
    }

</script>

