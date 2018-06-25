<%-- 
    Document   : analytics
    Created on : Mar 4, 2018, 8:45:45 PM
    Author     : kanch
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<script src="static/echarts.min.js"></script>
<div id="analytics">
    <h1>Analytics</h1>
    <div class="row">
        <div class="col-md-4">
            <div class="card text-white bg-primary mb-3">
                <div class="card-header">Analysis method 1</div>
                <div class="card-body">
                    <h5 class="card-title">Automatic Analysis</h5>
                    <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                </div>
            </div>
        </div>
        <div class="col-md-4">
            <div class="card text-white bg-secondary mb-3">
                <div class="card-header">Analysis method 2</div>
                <div class="card-body">
                    <h5 class="card-title">Cross-Table Analysis</h5>
                    <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                </div>
            </div>
        </div>
        <div class="col-md-4">
            <div class="card text-white bg-info mb-3">
                <div class="card-header">Analysis method 3</div>
                <div class="card-body">
                    <h5 class="card-title">Customize Analysis</h5>
                    <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                </div>
            </div>
        </div>
    </div>
    <div class="row">
        <div class="alert alert-primary" role="alert" style="width:100%">
            Is this your <a href="#" class="alert-link">first time</a> use Database Insights?. <br/>
            Above are the tips for you to get quick start. Just click corresponding navigator after your reading turtoils above.<br/>
            In Database Insights, we are deliver easy to use analysis service for you. <br/>
            Contact us at support@dbisystem.com if you need any further help.
        </div>
    </div>

</div>

<script>
    $('#analytics').bootstrapMaterialDesign();
</script>