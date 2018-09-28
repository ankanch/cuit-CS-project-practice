<%-- 
    Document   : console_nav_side
    Created on : Apr 10, 2018, 5:28:15 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="dbi.utils.GlobeVar"%>
<%@page import="dbi.localization.lang"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%
    lang local = lang.detectLang(request);
%>
<nav class="col-sm-3 col-md-2 hidden-xs-down bg-faded sidebar" style="box-shadow: 0 0 5px 0 rgba(0,0,0,.35);">
    <span class="console-nav-split-text"><%=local.getString(langID.JSP_NAV_SIDE_TITLE_ANALYTICS) %></span>
    <ul class="nav nav-pills flex-column">
        <li class="nav-item">
            <a class="nav-link console-siderbar active" data-url="/templates/console/overview" href="javascript:">
                <i class="material-icons console-sidebar-icon-text">account_balance</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_OVERVIEW) %></span>
                <span class="sr-only">(current)</span></a>
        </li>
        <li class="nav-item">
            <a class="nav-link console-siderbar" data-url="/templates/console/reports" href="javascript:">
                <i class="material-icons console-sidebar-icon-text">assignment</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_REPORTS) %></span>
            </a>
        </li>
        <!--li class="nav-item">
            <a class="nav-link console-siderbar" data-url="/templates/console/realtimeanalytics" href="javascript:">
                <i class="material-icons console-sidebar-icon-text">timeline</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_REALTIME) %></span>
            </a>
        </li-->
        <li class="nav-item" data-toggle="collapse" data-target="#moreAnalytics" class="collapsed">
            <a class="nav-link console-siderbar" data-url="/templates/console/analytics" href="javascript:">
                <i class="material-icons console-sidebar-icon-text">assessment</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_ANALYTICS) %></span>
                <i class="material-icons console-sidebar-icon-text mr-0">expand_more</i>
            </a>
        </li>
        <ul class="sub-menu collapse console-sidebar-collapse" id="moreAnalytics" style="height: 0px;">
            <li class="nav-item console-sidebar-subnav">
                <a class="nav-link console-siderbar" data-url="/templates/console/analytics/autoanalytics" href="javascript:">
                    <i class="material-icons console-sidebar-icon-text">lightbulb_outline</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_AUTO) %></span>
                </a>
            </li>
            <li class="nav-item console-sidebar-subnav">
                <a class="nav-link console-siderbar" data-url="/templates/console/analytics/crosstableanalytics" href="javascript:">
                    <i class="material-icons console-sidebar-icon-text">library_books</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_CROSSTABLE) %></span>
                </a>
            </li>
            <li class="nav-item console-sidebar-subnav">
                <a class="nav-link console-siderbar" data-url="/templates/console/analytics/costomizeAnalysis" href="javascript:">
                    <i class="material-icons console-sidebar-icon-text">settings_ethernet</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_CUSTOMIZE) %></span>
                </a>
            </li>
        </ul>
    </ul>

    <hr class="console-nav-split"><span class="console-nav-split-text"><%=local.getString(langID.JSP_NAV_SIDE_TITLE_DATABASE) %></span>
    <ul class="nav nav-pills flex-column">
        <li class="nav-item">
            <a class="nav-link console-siderbar" data-url="/templates/console/credentials" href="javascript:">
                <i class="material-icons console-sidebar-icon-text">archive</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_CREDENTIALS) %></span>
            </a>
        </li>
        <li class="nav-item">
            <a class="nav-link console-siderbar" data-url="/templates/console/logs" href="javascript:">
                <i class="material-icons console-sidebar-icon-text">assignment_late</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_LOGS) %></span>
            </a>
        </li>
    </ul>

    <hr class="console-nav-split"><span class="console-nav-split-text"><%=local.getString(langID.JSP_NAV_SIDE_TITLE_ACCOUNT) %></span>
    <ul class="nav nav-pills flex-column">
        <li class="nav-item">
            <a class="nav-link console-siderbar" data-url="/templates/console/settings" href="javascript:">
                <i class="material-icons console-sidebar-icon-text">settings</i><span class="console-sidebar-icon-text"><%=local.getString(langID.JSP_NAV_SIDE_SETTINGS) %></span>
            </a>
        </li>
    </ul>
</nav>