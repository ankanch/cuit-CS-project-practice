<%-- 
    Document   : quicksignup
    Created on : Mar 1, 2018, 9:05:45 PM
    Author     : kanch
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!-- Modal -->
<div class="modal fade" id="modal_quick_signup" tabindex="-1" role="dialog" aria-labelledby="modal_quick_signup" aria-hidden="true" >
  <div class="modal-dialog modal-dialog-centered" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="exampleModalLongTitle">Sign up and gain the insights today!</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body px-5">
        <%@ include file="../components/form_signup.html" %>
      </div>
    </div>
  </div>
</div>
