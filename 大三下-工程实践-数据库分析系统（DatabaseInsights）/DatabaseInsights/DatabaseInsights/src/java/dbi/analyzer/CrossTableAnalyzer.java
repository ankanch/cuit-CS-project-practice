/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 13 2018
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

import dbi.utils.DBILog;
import dbi.utils.DBIResultSet;
import dbi.utils.Debug;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author kanch
 */
public class CrossTableAnalyzer {

    private int uid = -1;
    private analyzerUtils au;
    private DBILog dbilog;

    public CrossTableAnalyzer(int uid) {
        this.uid = uid;
    }

    public ArrayList<Chart> generateCharts(ArrayList<CrossTableJob> jobs) {
        ArrayList<Chart> chtarr = new ArrayList<>();
        for (CrossTableJob job : jobs) {
            Debug.log("current process field=", job.graph_name, "\tjob.dtype=", job.dtype, "\tjob.poolf=", job.poolf);
            Debug.log("chtarr.size()=", chtarr.size());
            switch (job.dtype) {
                case CrossTableJob.TYPE_NUMBER:
                    switch (job.poolf) {
                        case CrossTableJob.PF_TREND:
                            chtarr.add(generateTrendChart(job));
                            break;
                        case CrossTableJob.PF_MAX:
                            chtarr.add(generateMaxChart(job));
                            break;
                        case CrossTableJob.PF_MIN:
                            chtarr.add(generateMinChart(job));
                            break;
                        default: //CrossTableJob.PF_COUNT;
                            chtarr.add(generateCountChart(job));
                            break;
                    }
                    break;
                default:    //TYPE_TEXT
                    chtarr.add(generateCountChart(job));
                    break;
            }
        }
        return chtarr;
    }

    private HashMap<String, analyzerUtils> createAnalyzerUtils(CrossTableJob job) {
        HashMap<String, analyzerUtils> hmau = new HashMap<>();
        for (String key : job.hmt.keySet()) {    //generate analyzerUtils instance by table name
            String dbname = job.hmt.get(key);
            if (!hmau.containsKey(key)) {
                hmau.put(key, new analyzerUtils(uid, dbname, key)); //create db operate instance col: au
            }
        }
        Debug.log("analyzerUtils instance generted count=", hmau.size());
        return hmau;
    }

    /*
    * this function will cut off data based on the shortest data column
     */
    private Chart generateTrendChart(CrossTableJob job) {
        Debug.log("generate Trending chart");
        HashMap<String, analyzerUtils> hmau = createAnalyzerUtils(job);
        ArrayList<Object[]> coldatalist = new ArrayList<>();   // format: {colname,coldata}
        int i = 1;
        int minsize = Integer.MAX_VALUE;
        for (String col : job.hmc.keySet()) { // loop over columns and comments
            //Debug.log("retriving data from database", i++, "/", job.hmc.size(), "...");
            DBIResultSet coldata = hmau.get(job.hmc.get(col)[1])
                    .getColumnData(analyzerUtils.SORT_ASC, col); // get instance by table name,then get column data
            coldatalist.add(new Object[]{col, coldata});
            //Debug.log("column", col, "=", coldata);
            if (coldata.rowCount() <= minsize) {   // ready for cut off data 
                minsize = coldata.rowCount();
            }
        }
        //Debug.log("generate chart option for trending chart");
        String ydata = "";
        String xdata = chartsHelper.generateXAxis(0, minsize).toString();
        String lengenddata = chartsHelper.convertToStringArray(job.hmc.keySet());
        for (Object[] cc : coldatalist) {
            String v = ChartOption.OPTION_TRENDM_DATA;
            v = v.replace("@NAME", String.valueOf(cc[0])).replace("@DATA", (((DBIResultSet) cc[1]).toArray1D()).subList(0, minsize).toString());
            ydata += v;
        }
        String option = ChartOption.OPTION_TRENDM.replace("@YDATA", ydata)
                .replace("@XDATA", xdata)
                .replace("@TITLE", job.graph_name)
                .replace("@LEGEND_DATA", lengenddata);
        Chart cht = new Chart(option, Chart.CHARTM_TRENDCHART);
        return cht;
    }

    /*
    * only support 4 level circle graph
     */
    private Chart generateCountChart(CrossTableJob job) {
        Debug.log("generate count chart");
        HashMap<String, analyzerUtils> hmau = createAnalyzerUtils(job);
        ArrayList<Object[]> coldatalist = new ArrayList<>();   // format: {colname,coldata}
        int i = 1;
        for (String col : job.hmc.keySet()) { // loop over columns and comments
            Debug.log("retriving data from database", i++, "/", job.hmc.size(), "...");
            DBIResultSet coldata = hmau.get(job.hmc.get(col)[1])
                    .getColumnValueCounts(col); // get instance by table name,then get column data count
            coldatalist.add(new Object[]{col, coldata});
            Debug.log("column", col, "=", coldata);
        }
        String count_temp = " {value:@V, name:'@N'},";
        String count_temp_selected = "{value:@V, name:'@N', selected:true},";
        Debug.log("generate chart option for count(pie) chart");
        ArrayList<String> radius = chartsHelper.computeRadius(coldatalist.size());
        Debug.log("radius generated :", radius);
        String data = "";
        i = 0;
        for (int t = 0; t < coldatalist.size(); t++) {  // we assure there must be more than two data set
            Object[] cc = coldatalist.get(t);
            String datatemp = "";
            for (ArrayList<Object> arr : ((DBIResultSet) cc[1]).getRows()) {
                if (i == 0 && t == 0) {
                    datatemp += count_temp_selected.replace("@V", String.valueOf(arr.get(1)))
                            .replace("@N", String.valueOf(arr.get(0)));
                    i++;
                } else {
                    datatemp += count_temp.replace("@V", String.valueOf(arr.get(1)))
                            .replace("@N", String.valueOf(arr.get(0)));
                }
            }
            if (t + 1 == coldatalist.size()) {   // last one
                data += ChartOption.OPTION_COUNTM_OUTERCIRCLE.replace("@TIP", job.hmcomments.get(String.valueOf(cc[0])))
                        .replace("@RADIUS", radius.get(t))
                        .replace("@YDATA", datatemp);
                break;
            }
            data += ChartOption.OPTION_COUNTM_INNERCIRCLE.replace("@TIP", job.hmcomments.get(String.valueOf(cc[0])))
                    .replace("@RADIUS", radius.get(t))
                    .replace("@YDATA", datatemp);
        }
        String option = ChartOption.OPTION_COUNTM.replace("@TITLE", job.graph_name)
                .replace("@LEGNED_DATA", "[]")
                .replace("@DATA", data);
        Chart cht = new Chart(option, Chart.CHARTM_PIECHART);
        return cht;
    }

    private Chart generateMaxChart(CrossTableJob job) {
        Chart cht = new Chart("", Chart.CHARTM_PIECHART);
        return cht;
    }

    private Chart generateMinChart(CrossTableJob job) {
        Chart cht = new Chart("", Chart.CHARTM_PIECHART);
        return cht;
    }

}
