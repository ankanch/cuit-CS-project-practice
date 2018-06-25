/* 
 * The MIT License
 *
 * **** Copyright © Long Zhang(kanch).
 * **** Email: kanchisme@gmail.com
 * **** Code created on Mar 01 2018
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


function showMsg(msg) {
    $.snackbar({content: msg});
}

/* function for loading content */
function loadContent(container, url, type) {
    // e.g.  loadContent("content_id","/settings",".html");
    $("#" + container).load(url + type);
}

/* function for loading content */
function loadContentF(container, url, type, complete) {
    // e.g.  loadContent("content_id","/settings",".html");
    $("#" + container).load(url + type);
    complete();
}

function loadJsp(container, url) {
    loadContent(container, url, ".jsp");
}

function loadJspF(container, url, complete) {
    loadContent(container, url, ".jsp", complete);
}

function loadHtml(container, url) {
    loadContent(container, url, ".html");
}

function loadHtmlF(container, url, complete) {
    loadContent(container, url, ".html", complete);
}

// get value from a given table
function GetCellValues(tableid, rowx, coly) {
    var table = document.getElementById(tableid);
    return table.rows[rowx-1].cells[coly-1].innerHTML;
}

function GetTableRow(tableid,rowx){
    return document.getElementById(tableid).rows[rowx-1];
}
