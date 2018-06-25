<%-- 
    Document   : console_add_credentials
    Created on : Apr 13, 2018, 11:03:38 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="dbi.localization.lang"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<!--
The MIT License

*** Copyright © Long Zhang(kanch)
*** Email: kanchisme@gmail.com
*** Code created on Mar 05 2018

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-->
<!-- Modal -->
<div class="modal fade" id="modal_add_credentials" tabindex="-1" role="dialog" aria-labelledby="modal_add_credentials" aria-hidden="true" >
    <div class="modal-dialog modal-dialog-centered" role="document">
        <div class="modal-content" id="modal_add_credentials_content">
            <div class="modal-header">
                <h5 class="modal-title" id="exampleModalLongTitle"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_TITLE) %></h5>
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
            </div>
            <div class="modal-body px-5">
                <form id="form_add_newCredential">
                    <div class="form-group">
                        <label for="dbSelect" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_SELECT) %></label>
                        <select class="form-control" id="dbSelect" name="dbtype">
                            <option value="1000" selected>Oracle Database 12c</option>
                            <option value="2000">MySQL</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label for="database_host" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_HOST) %></label>
                        <input type="text" required="required" class="form-control" id="database_host" name="dbhost">
                        <span class="bmd-help"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_HOST_TIP) %></span>
                    </div>
                    <div class="form-group">
                        <label for="database_name" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_DBNAME) %></label>
                        <input type="text" required="required" class="form-control" id="database_name" name="dbname">
                        <span class="bmd-help"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_DBNAME_TIP) %></span>
                    </div>
                    <div class="form-group">
                        <label for="database_username" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_USERNAME) %></label>
                        <input type="text" required="required" class="form-control" id="database_username" name="dbusername">
                        <span class="bmd-help"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_USERNAME_TIP) %></span>
                    </div>
                    <div class="form-group">
                        <label for="database_password" class="bmd-label-floating"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_PASSWORD) %></label>
                        <input type="password" required="required" class="form-control" id="database_password" name="dbpass">
                        <span class="bmd-help"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_PASSWORD_TIP) %></span>
                    </div>
                    <div class="checkbox pt-md-5 pb-md-4">
                        <label>
                            <input type="checkbox" id="agreement" name="optionsRadios" id="optionsRadios1" value="option1">
                            <%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_IAGREE_PRE) %>
                            <a href="#" target="_blank"><%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_IAGREE_SUF) %></a> 
                        </label>
                    </div>
                    <input type="text" id="dbsname" name="dbs" style="display:none;">
                    <button type="button" class="btn btn-raised btn-primary" onclick="add(this)">Add Database</button>
                    <button type="button" class="btn btn-link "  data-dismiss="modal"><small>Cancel</small></button>
                    <div id="info_check">
                        <%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_TIP_CHECKING) %>
                        <div class="progress-line"></div>
                    </div>
                </form>
                <script>
                    $("#info_check").hide();
                    function add(input) {
                        if ($("#agreement").is(':checked') == false) {
                            showMsg("<%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_TIP_AGREEMENT) %>");
                            return;
                        }
                        this.disabled = true;
                        $("#info_check").show();
                        $('#dbsname').val($("#dbSelect").val());
                        
                        SubmitFormFF("/api/addCredentials", "form_add_newCredential", function error() {
                            showMsg("<%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_TIP_FAILED) %>");
                            $("#info_check").hide();
                            this.disabled = false;
                        }, function success() {
                            showMsg("<%=local.getString(langID.JSP_CONSOLE_CREDENTIAL_ADD_TIP_SUCCESS) %>");
                            $("#info_check").hide();
                            $("#modal_add_credentials").modal('hide');
                        });

                        return;
                    }
                    
                    

                </script>
            </div>
        </div>
    </div>
</div>