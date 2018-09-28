/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on May 24 2018
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
package dbi.analyzer;

/**
 *
 * @author kanch
 */
public class CustomizeJob {

    // pooling function code
    public static final int PF_NONE = 1001;
    public static final int PF_AVERANGE = 1002;
    public static final int PF_COUNT = 1003;
    public static final int PF_COUNT_NOREPEAT = 1004;
    public static final int PF_MAX = 1005;
    public static final int PF_MIN = 1006;
    public static final int PF_SUM = 1007;

    // type code
    public static final int TYPE_NUMBER = 2001;
    public static final int TYPE_TEXT = 2002;
    public static final int TYPE_BOOLEAN = 2003;

    public String column_name = "";
    public String column_nickname = "";
    public int type = TYPE_NUMBER;
    public int pool_func = PF_NONE;
    public String comment = "";

    public CustomizeJob(String lastf, String newf, String type, String poolf, String comment) {
        switch (type) {
            case "type_text":
                this.type = TYPE_TEXT;
                break;
            case "type_number":
                this.type = TYPE_NUMBER;
                break;
            case "type_boolean":
                this.type = TYPE_BOOLEAN;
                break;
        }
        switch (poolf) {
            case "pf_none":
                this.pool_func = PF_NONE;
                break;
            case "pf_avg":
                this.pool_func = PF_AVERANGE;
                break;
            case "pf_count":
                this.pool_func = PF_COUNT;
                break;
            case "pf_count_norepeat":
                this.pool_func = PF_COUNT_NOREPEAT;
                break;
            case "pf_max":
                this.pool_func = PF_MAX;
                break;
            case "pf_min":
                this.pool_func = PF_MIN;
                break;
            case "pf_sum":
                this.pool_func = PF_SUM;
                break;
        }
        column_name = lastf;
        column_nickname = newf;
        this.comment = comment;
    }

}
