<%-- 
    Document   : resetpassword
    Created on : Mar 1, 2018, 11:45:08 PM
    Author     : kanch
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Reset your password - Database Insights</title>
        <%@ include file="templates/globehead.html" %>
    </head>
    <body>
        <%@ include file="templates/index/indexnav.html" %>
        <div class="pt-md-5 pb-md-5">
            <div class="card bg-light mx-auto " id="request_email_form" style="max-width: 400px;">
                <div class="card-header"><h4>Password Reset</h4></div>
                <div class="card-body">
                    <form action="api/login" method="post">
                        <p>Please enter the E-mail when you registered your account, we will send you an email guiding you to reset the password.</p>
                        <div class="form-group">
                            <label for="reset_email" class="bmd-label-floating">Email address</label>
                            <input type="email" required="required" class="form-control" id="reset_email" name="email">
                        </div>
                        <button type="submit" class="btn btn-raised btn-success btn-lg btn-block" onclick="requestMail(false)">Send Reset Link</button>
                    </form>
                </div>
            </div>
            <div class="card mx-auto text-center pl-3 pr-3 pt-5" id="mail_send_success" style="max-width:800px;min-height:300px;">
                <div class="card-body mt-5">
                    An email with the password reset link have been sent to you (<b style="color:red;" id="reset_email">email</b>). 
                    Following that email to reset your password.
                    <br/>If you can't find the email in your inbox, please take a look into the spam mails.
                    <br/><br/>
                    <p>Still can't that email? You can <a href="javascript:requestMail(true)" style="color:palevioletred">request again</a></p>
                </div>
            </div>
            <div class="card mx-auto text-center pl-3 pr-3 pt-1" id="reset_password" style="max-width:800px;min-height:300px;">
                <div class="card-body mt-2" id="change_form">
                    You are about to change password of account(<b style="color:red;" id="reset_email">email</b>). 
                    <br/>
                    <form class='text-left pl-5 pr-5 mr-5 ml-5'>
                        <div class="form-group">
                            <label for="signup_password" class="bmd-label-floating">New Password</label>
                            <input type="password" required="required" class="form-control" id="signup_password" name="password">
                            <span class="bmd-help">Including symbol,lowercase,uppercase and number.</span>
                        </div>
                        <div class="form-group">
                            <label for="signup_confirmpassword" class="bmd-label-floating">Confirm Password</label>
                            <input type="password" required="required" class="form-control" id="signup_confirmpassword" oninput="checkpassword(this)">
                        </div>
                    </form>
                    <button type="submit" class="btn btn-raised btn-success " onclick="changePassword()">Confirm Change</button>
                </div>
                <div class="card-body mt-2" id='changed_success'>
                    Your password has been changed!
                    <br/>
                    Redirecting you to login page.
                    <br/>
                    If not redirected,please click this link: <a href="signin.jsp">http://databaseinsights.com/signin.jsp</a>
                </div>
            </div>
        </div>
        <footer class="container py-5">
            <%@ include file="templates/index/footer.html" %>
        </footer>
        <script>
            $("#mail_send_success").hide();
            $("#changed_succsss").hide();
            $("#reset_password").hide();

            function requestMail(again) {
                if (again) {
                    showMsg("Password reset email has been sent to your inbox");
                } else {
                    $("#request_email_form").hide();
                    $("#mail_send_success").show();
                }
            }
            
            function changePassword(){
                $("#changed_succsss").show();
                $("#change_form").hide();
            }

            function checkpassword(input) {
                if (input.value != document.getElementById('signup_password').value) {
                    input.setCustomValidity('Password Not Match.');
                } else {
                    input.setCustomValidity('');
                }
            }

        </script>
    </body>
</html>
