/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 16 2018
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

import dbi.utils.Debug;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author kanch
 */
public class CrossTableJob {
    // pooling function code

    public static final int PF_TREND = 1001;
    public static final int PF_COUNT = 1003;
    public static final int PF_MAX = 1005;
    public static final int PF_MIN = 1006;
    // type code
    public static final int TYPE_NUMBER = 2001;
    public static final int TYPE_TEXT = 2002;

    public String graph_name = "";
    public String graph_des = "";
    public int poolf = PF_COUNT;
    public int dtype = TYPE_TEXT;
    public HashMap<String, String> hmt = new HashMap<>();   // Table : {Database} 
    public HashMap<String, String[]> hmc = new HashMap<>();   // Column : {Database,Table} 
    public HashMap<String,String> hmcomments = new HashMap<>();  // Column : comments

    public CrossTableJob(Object gname, Object gdes, Object columns, Object coltype, Object poolf, Object comments) {
        graph_name = String.valueOf(gname);
        graph_des = String.valueOf(gdes);
        String[] cols = String.valueOf(columns).split(";");          // element: DB->TB->COL
        String[] colcoms = String.valueOf(comments).split(";");
        for (int i = 0; i < cols.length; i++) {
            String[] loc = cols[i].split("->");
            hmcomments.put(loc[2], colcoms[i]);  // Column : comments
            hmt.put(loc[1], loc[0]); // Table : Database 
            hmc.put(loc[2], new String[]{loc[0], loc[1]}); // Column : {Database,Table} 
        }
        switch (String.valueOf(coltype)) {
            case "type_number":
                dtype = TYPE_NUMBER;
                break;
            default:
                dtype = TYPE_TEXT;
        }
        switch (String.valueOf(poolf)) {
            case "pf_trend":
                this.poolf = PF_TREND;
                break;
            case "pf_min":
                this.poolf = PF_MIN;
                break;
            case "pf_max":
                this.poolf = PF_MAX;
                break;
            default:
                this.poolf = PF_COUNT;
        }
    }
}
