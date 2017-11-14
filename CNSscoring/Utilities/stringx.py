table = """
 <link rel="stylesheet" href="../static/bootstrap-4.0.0-beta/css/bootstrap.min.css" integrity="sha384-/Y6pD6FV/Vv2HJnA6t+vslU6fwYXjCFtcEpHbNJ0lyAFsXTsjBbfaDjzALeQsN6M" crossorigin="anonymous">
<script src="../static/jquery-3.2.1.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.11.0/umd/popper.min.js" integrity="sha384-b/U6ypiBEHpOf/4+1nzFpr53nxSS+GLCkfwBdFNTxtclqqenISfwAzpKaMNFNmj4" crossorigin="anonymous"></script>
<script src="../static/bootstrap-4.0.0-beta/js/bootstrap.min.js"></script>
<div class="container">
<table class="table table-hover">
  <thead>
    <tr>
      <th scope="col">组号</th>
      <th scope="col">总分</th>
      <th scope="col">平均分</th>
    </tr>
  </thead>
  <tbody>
  @TBODY@
  </tbody>
</table>
</div>"""

table_item = """
    <tr>
      <th scope="row">@GID</th>
      <td>@SUM</td>
      <td>@AVG</td>
    </tr>
    """