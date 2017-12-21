<%-- 
    Document   : header
    Created on : Dec 12, 2017, 8:02:39 PM
    Author     : kanch
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>

<nav class="navbar navbar-expand-lg navbar-light bg-light">
    <a class="navbar-brand" href="/IncidentsReport">Incidents Reports</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarNav">
        <ul class="navbar-nav">
            <li class="nav-item active">
                <a class="nav-link"  data-toggle="modal" data-target="#exampleModal" href="">分享 <span class="sr-only">(current)</span></a>
            </li>
            <li class="nav-item" id='alert' style="display:none;">
                <a class="nav-link"  href="javascript:setAlertLoc()">创建警报</a>
            </li>
            <li class="nav-item" >
                <a class="nav-link" href="/IncidentsReport/submit.jsp" id="nav_submit" target="_blank">提交事件</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="/IncidentsReport/about.jsp" id="nav_about" target="_blank">关于</a>
            </li>
        </ul>
    </div>
</nav>

<script>
    function showMsg(msg) {
        $.snackbar({content: msg});
    }

    function SubmitForm(url, formid, error_msg, success_msg) {
        // function from https://stackoverflow.com/questions/25983603/how-to-submit-html-form-without-redirection
        $.ajax({
            url: url,
            type: 'post',
            data: $('#' + formid).serialize(),
            success: function (data) {
                console.log(data)
                if (data.indexOf("ERROR") > -1) {
                    showMsg(error_msg);
                } else {
                    showMsg(success_msg);
                }
            }
        });
    }
</script>

