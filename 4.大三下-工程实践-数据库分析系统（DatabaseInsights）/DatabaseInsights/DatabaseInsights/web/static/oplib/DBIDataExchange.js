/* 
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Apr 19 2018
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

class DBIEX {

    constructor(exstr) {
        // init spliter
        var SP_STATUS = "<@SUS>";
        var SP_MESSAGE = "<@MSG>";
        var SP_COLUMN = "<@C>";
        var SP_ROW = "<@R>";
        this.message = "";
        this.status = false;
        this.data = [];
        // parse source str
        // str like below:
        // true<@SUS>this is a test message<@MSG>test1<@C>text11<@C><@R>test2<@C>text22<@C><@R>test3<@C>text33<@C><@R> 
        var res = exstr.split(SP_STATUS);
        if (res[0] === "true") {
            this.status = true;
        }
        var res = res[1].split(SP_MESSAGE);
        this.message = res[0];
        var rows = res[1].split(SP_ROW);
        if (rows.length > 1) {
            var i;
            for (i = 0; i < rows.length; i++) {
                var rowx = rows[i].split(SP_COLUMN);
                rowx.pop();
                if (rowx.length > 0) {
                    this.data.push(rowx);
                }
            }
        } else {
            this.data.push(rows);
        }
        //console.log(this);
    }

    static toString(arr) {
        // input a 2d arr, and convert it to DBIResultSet format
        var SP_COLUMN = "<@C>";
        var SP_ROW = "<@R>";
        var SP_MESSAGE = "<@MSG>";
        var ret = "";
        arr.forEach(function (item, index, array) {
            var rowstr = "";
            item.forEach(function (item, index, array) {
                if (item.length > 0) {
                    rowstr += item + SP_COLUMN;
                }else{
                    rowstr += "no notes provided." + SP_COLUMN;
                }
            });
            ret += rowstr + SP_ROW;
        });
        return "1" + SP_MESSAGE + ret;
    }
}


