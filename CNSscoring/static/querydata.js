function SubmitForm(url, formid, error_msg, success_msg) {
    // function from https://stackoverflow.com/questions/25983603/how-to-submit-html-form-without-redirection
    $.ajax({
        url: url,
        type: 'post',
        data: $('#' + formid).serialize(),
        success: function (data) {
            console.log(data)
            if (data.indexOf("U") > -1) {
                showMsg(error_msg, 5);
            } else {
                showMsg(success_msg, 5);
            }
        }
    });
}

function SubmitForm(url, formid, error_msg, success_msg, success_func) {
    // function from https://stackoverflow.com/questions/25983603/how-to-submit-html-form-without-redirection
    $.ajax({
        url: url,
        type: 'post',
        data: $('#' + formid).serialize(),
        success: function (data) {
            console.log(data)
            if (data.indexOf("U") > -1) {
                showMsg(error_msg, 5);
            } else {
                showMsg(success_msg, 5);
                console.log("execute_success_function");
                success_func();
                console.log("success_function_done");
            }
        }
    });
}



function postData(url, data_dic, error_msg, success_msg) {
    // function from https://stackoverflow.com/questions/25983603/how-to-submit-html-form-without-redirection
    $.ajax({
        url: url,
        type: 'post',
        data: data_dic,
        success: function (data) {
            console.log(data)
            if (data.indexOf("U") > -1) {
                showMsg(error_msg, 5);
            } else {
                showMsg(success_msg, 5);
            }
        }
    });
}

function postData(url, data_dic, error_msg, success_msg, success_func) {
    // function from https://stackoverflow.com/questions/25983603/how-to-submit-html-form-without-redirection
    $.ajax({
        url: url,
        type: 'post',
        data: data_dic,
        success: function (data) {
            console.log(data)
            if (data.indexOf("U") > -1) {
                showMsg(error_msg, 5);
            } else {
                showMsg(success_msg, 5);
                success_func();
            }
        }
    });
}


function Getdata(url, success_f) {
    $.get(url, function (data) {
        success_f(data);
    });
}

String.prototype.replaceAll = function (search, replacement) {
    var target = this;
    return target.split(search).join(replacement);
};

function parseTuple(t) {
    var lc_level = 0,
        rc_level = 0,
        last_lc = 0,
        last_rc = 0,
        result = [];
    for (i = 0; i < t.length; i++) {
        if (t[i] == "(") {
            lc_level++;
            last_lc = i;
        } else if (t[i] == ")") {
            rc_level++;
            last_rc = i;
        }
        if (rc_level == 1) {
            var substr = t.slice(last_lc + 1, last_rc);
            var data = substr.replaceAll("'", "").split(",");
            result.push(data);
            lc_level--;
            rc_level--;
            i = 0;
            t = t.slice(0, last_lc) + t.substring(last_rc + 1);
        }
        if (lc_level == rc_level && lc_level == 0) {
            break;
        }
    }
    return result;
}

function getCookie(cname) {
    var name = cname + "=";
    var decodedCookie = decodeURIComponent(document.cookie);
    var ca = decodedCookie.split(';');
    for (var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}