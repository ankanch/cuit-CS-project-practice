<%-- 
    Document   : costomizeAnalysis
    Created on : 2018-4-26, 15:32:04
    Author     : Miss Zhang
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="dbi.localization.lang"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<% lang local = lang.detectLang(request);%>
<div id="analytics_auto">
    <h2><%=local.getString(langID.ANA_CUSTOM_TITLE)%></h2>
    <div class="card">
        <div class="progress-line" id="progressbar" style="display:none;"></div>
        <div class="card-body">
            <button type="button" class="btn" disabled style="color:#4e4e52;"><%=local.getString(langID.ANA_CUSTOM_TIP_SELECDBT)%></button>
            <div class="btn-group">
                <button class="btn dropdown-toggle" type="button" id="buttonMenu1" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"
                        onclick="getDatabases()">
                    <%=local.getString(langID.ANA_CUSTOM_TIP_BTN_SELDB)%>
                </button>
                <div class="dropdown-menu" aria-labelledby="buttonMenu1" id="showDatabase">

                </div>
            </div>
            <div class="btn-group">
                <button class="btn dropdown-toggle" type="button" id="buttonMenu2" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    <%=local.getString(langID.ANA_CUSTOM_TIP_BTN_SELTB)%>
                </button>
                <div class="dropdown-menu" aria-labelledby="buttonMenu2" id="showTables">

                </div>
            </div>
            <button type="button" class="btn btn-raised btn-success" id="btn_start" onclick="startAnalyze()"  style="display:none"><%=local.getString(langID.ANA_CUSTOM_BTN_START)%></button>
        </div>
    </div>
    <hr>
    <div id="accordion">
        <div class="card">
            <div class="card-header" id="headingOne">
                <h5 class="mb-0">
                    <button class="btn btn-link console-text-button" data-toggle="collapse" data-target="#collapseOne" aria-expanded="true" aria-controls="collapseOne">
                        <%=local.getString(langID.ANA_CUSTOM_TIP_CLP_TITLE1)%>
                    </button>
                </h5>
            </div>
            <div id="collapseOne" class="collapse show" aria-labelledby="headingOne" data-parent="#accordion">
                <div class="card-body">
                    <div class="alert alert-danger" role="alert" id="alarmcard">
                        <%=local.getString(langID.ANA_CUSTOM_TIP_C1)%>
                    </div>
                    <table class="table table-striped" style="text-align:center;" id="columnstable">
                        <thead>
                            <tr>
                                <th scope="col"><%=local.getString(langID.ANA_CUSTOM_TABLE_C1_INDEX)%></th>
                                <th scope="col"><%=local.getString(langID.ANA_CUSTOM_TABLE_C2_FIELD)%></th>
                                <th scope="col"><%=local.getString(langID.ANA_CUSTOM_TABLE_C3_TYPE)%></th>
                                <th scope="col"><%=local.getString(langID.ANA_CUSTOM_TABLE_C4_POOLF)%></th>
                                <th scope="col"><%=local.getString(langID.ANA_CUSTOM_TABLE_C5_COMMENT)%></th>
                            </tr>
                        </thead>
                        <tbody id="DBtbody">

                        </tbody>
                    </table>
                </div>
            </div>
        </div>
        <div class="card">
            <div class="card-header" id="headingTwo">
                <h5 class="mb-0">
                    <button class="btn btn-link collapsed console-text-button" data-toggle="collapse" data-target="#collapseTwo" aria-expanded="false" aria-controls="collapseTwo">
                        <%=local.getString(langID.ANA_CUSTOM_TIP_CLP_TITLE2)%>
                    </button>
                </h5>
            </div>
            <div id="collapseTwo" class="collapse" aria-labelledby="headingTwo" data-parent="#accordion">
                <div class="card-body" id="chartslist">
                    <div class="alert alert-danger" role="alert" >
                        <%=local.getString(langID.ANA_CUSTOM_TIP_C2)%>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

<script src="static/oplib/jsinjsp/analytics.customize.js"></script>
<script src="static/oplib/jsinjsp/analytics.chart.instance.js"></script>
<script src="static/oplib/jsinjsp/analytics.report.js"></script>
<script>
    $("#columnstable").hide();
    $('#analytics_auto').bootstrapMaterialDesign();
</script>

