<%-- 
    Document   : console_footer
    Created on : Apr 12, 2018, 5:44:21 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.langID"%>
<%@page import="dbi.localization.lang"%>
<%@page import="dbi.utils.GlobeVar"%>
<%@page import="dbi.utils.GlobeVar"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!--
The MIT License

**** Copyright © Long Zhang(kanch).
**** Email: kanchisme@gmail.com
**** Code created on Mar 02 2018

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
<%
    //lang local = GlobeVar.OBJ_MANAGER_USER.detectLang(request); variable already exist
%>
<div class="console-footer-text" > &copy; 2018 Database Insights
    <span > | 
        <a href="/" target="_blank"><%=local.getString(langID.JSP_CONSOLE_FOOTER_HOME)%></a> 
        | <a href="tos.jsp" target="_blank"><%=local.getString(langID.JSP_CONSOLE_FOOTER_SERVICE)%></a> 
        | <a href="/privacy.jsp" target="_blank"><%=local.getString(langID.JSP_CONSOLE_FOOTER_POLICY)%></a> 
    </span>
</div>
<script>
    $('body').bootstrapMaterialDesign();
</script>
