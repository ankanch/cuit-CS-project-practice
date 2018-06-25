<%-- 
    Document   : index
    Created on : Feb 28, 2018, 5:57:59 PM
    Author     : kanch
--%>

<%@page import="dbi.localization.lang"%>
<%@page import="dbi.localization.langID"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%  lang local = lang.detectLang(request); %>
<!DOCTYPE html>
<!--
The MIT License

**** Copyright © Long Zhang(kanch).
**** Email: kanchisme@gmail.com
**** Code created on Feb 28 2018

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
<html>
    <head>
        <title>Database Insights</title>
        <%@ include file="templates/globehead.html" %>
    </head>
    <body>
        <%@ include file="templates/index/indexnav.html" %>


        <div class="position-relative overflow-hidden p-3 p-md-5 text-center bg-light index-showcase-1">
            <div class="col-md-5 p-lg-5 mx-auto my-5">
                <h1 class="display-4 font-weight-normal text-white ">Database Insights</h1>
                <p class="lead font-weight-normal text-white ">Write anything about database insights here. </p>
                <button type="button" class="btn btn-raised btn-lg text-white " data-toggle="modal" data-target="#modal_quick_signup">Try it now!</button>
            </div>
        </div>
        <%@ include file="templates/dialogs/quicksignup.jsp" %>
        <div class="d-md-flex flex-md-equal w-100">
            <div class="bg-primary pt-3 px-3 pt-md-5 px-md-5 text-center text-white overflow-hidden">
                <div class="my-3 py-3">
                    <h2 class="display-5">Turn insights into potentials</h2>
                    <p class="lead px-5 mx-5">Get stronger results across all your columns, 
                        tables, and databases. Database Insights offer 
                        data analytics products for businesses of all sizes 
                        to better understand your data.</p>
                </div>
                <div class="bg-light box-shadow mx-auto index-showcase-2" style="width: 80%; height: 300px; border-radius: 21px 21px 0 0;"></div>
            </div>
        </div>

        <div class="d-md-flex flex-md-equal w-100">
            <div class="pt-3 pt-md-5 text-center text-white overflow-hidden ">
                <div class=" mb-3 index-showcase-3" style="height: 430px;"></div>
            </div>
            <div class="pt-3 px-3 pt-md-5 px-md-5 text-center overflow-hidden my-auto">
                <div class="my-3 p-3 ">
                    <h2 class="display-5">Powerful data analytics solutions for database of all shapes and sizes.</h2>
                </div>
            </div>
        </div>

        <div class="d-md-flex flex-md-equal w-100 text-white">
            <div class="bg-dark  pt-3 px-3 pt-md-5 pb-md-5 mb-5 px-md-5 text-center overflow-hidden">
                <div class="my-3 py-3">
                    <h2 class="display-5" id="title_features">Features</h2>
                </div>
                <div class="card-deck">
                    <div class="card text-black" style="width: 18rem;">
                        <img class="card-img-top index-showcase-feature" src="static/img/showcase/showcase_feature_relation.png" alt="Card image cap">
                        <div class="card-body">
                            <h5 class="card-title">Full Relations</h5>
                            <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                        </div>
                    </div>
                    <div class="card text-black" style="width: 18rem;">
                        <img class="card-img-top index-showcase-feature" src="static/img/showcase/showcase_features_realtime.png" alt="Card image cap">
                        <div class="card-body">
                            <h5 class="card-title">Realtime Analyzing</h5>
                            <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                        </div>
                    </div>
                    <div class="card text-black" style="width: 18rem;">
                        <img class="card-img-top index-showcase-feature" src="static/img/showcase/showcase_feature_dbs.jpg" alt="Card image cap">
                        <div class="card-body">
                            <h5 class="card-title">Multiple DBS support</h5>
                            <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                        </div>
                    </div>
                    <div class="card text-black" style="width: 18rem;">
                        <img class="card-img-top index-showcase-feature" src="static/img/showcase/showcase_feature_report.jpg" alt="Card image cap">
                        <div class="card-body">
                            <h5 class="card-title">Full Detailed Report</h5>
                            <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <footer class="container py-5">
            <%@ include file="templates/index/footer.html" %>
        </footer>
    </body>
</html>

