<%-- 
    Document   : autoanalytics
    Created on : Apr 16, 2018, 8:26:09 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="dbi.localization.lang"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<% lang local = lang.detectLang(request);%>
<div id="analytics_auto">
    <h2>Auto Analytics</h2>
    <div class="card">
        <div class="progress-line" id="progressbar" style="display:none;"></div>
        <div class="card-body">
            <button type="button" class="btn" disabled style="color:#4e4e52;"><%=local.getString(langID.ANA_AUTO_TIP_SELECDBT)%></button>
            <div class="btn-group">
                <button class="btn dropdown-toggle" type="button" id="buttonMenu1" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"
                        onclick="getDatabases()">
                    <%=local.getString(langID.ANA_AUTO_TIP_BTN_SELDB)%>
                </button>
                <div class="dropdown-menu" aria-labelledby="buttonMenu1" id="showDatabase">

                </div>
            </div>
            <div class="btn-group">
                <button class="btn dropdown-toggle" type="button" id="buttonMenu2" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    <%=local.getString(langID.ANA_AUTO_TIP_BTN_SELTB)%>
                </button>
                <div class="dropdown-menu" aria-labelledby="buttonMenu2" id="showTables">

                </div>
            </div>
        </div>
    </div>
    <div class="row mt-2">
        <div class="col-md-12">
            <div class="card">
                <h5 class="card-header" id="card_title"><%=local.getString(langID.ANA_AUTO_TIP_RET_TITLE)%></h5>
                <div class="card-body" id="chartslist">
                    <div class="alert alert-danger" role="alert" id="alert">
                        <%=local.getString(langID.ANA_AUTO_TIP_RESULT)%>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

<script src="static/oplib/jsinjsp/analytics.auto.js"></script>
<script src="static/oplib/jsinjsp/analytics.chart.instance.js"></script>
<script src="static/oplib/jsinjsp/analytics.report.js"></script>
<script>
                            $('#analytics_auto').bootstrapMaterialDesign();
</script>
