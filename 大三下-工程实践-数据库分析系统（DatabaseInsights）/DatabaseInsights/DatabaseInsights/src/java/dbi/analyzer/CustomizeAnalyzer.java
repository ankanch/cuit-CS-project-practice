/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on May 22 2018
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
import dbi.utils.DataValidation;
import dbi.utils.Debug;
import java.util.ArrayList;

/**
 *
 * @author kanch
 */
public class CustomizeAnalyzer {
    
    private int uid = -1;
    private String table = "";
    private DBILog dbilog;
    private analyzerUtils au;
    
    public CustomizeAnalyzer(int uid, String database, String table) {
        this.uid = uid;
        this.table = table;
        au = new analyzerUtils(this.uid, database, table);
        dbilog = new DBILog(database, table, uid);
    }
    
    public ArrayList<Chart> generateCharts(ArrayList<CustomizeJob> jobs) {
        dbilog.log("perform customize analysis.");
        ArrayList<Chart> chtarr = new ArrayList<>();
        for (CustomizeJob job : jobs) {
            Debug.log("current process field=", job.column_name, "\ttype=", job.type, "\tpoolf=", job.pool_func);
            //Debug.log("chtarr.size()=", chtarr.size());
            switch (job.type) {
                case CustomizeJob.TYPE_NUMBER:
                    switch (job.pool_func) {
                        case CustomizeJob.PF_AVERANGE:
                            chtarr.add(generateAverageChart(job));
                            break;
                        case CustomizeJob.PF_COUNT:
                            chtarr.add(generateCountsChart(job));
                            break;
                        case CustomizeJob.PF_COUNT_NOREPEAT:
                            chtarr.add(generateCountsNoRepeat(job));
                            break;
                        case CustomizeJob.PF_MAX:
                            chtarr.add(generateMaxiumChart(job));
                            break;
                        case CustomizeJob.PF_MIN:
                            chtarr.add(generateMiniumChart(job));
                            break;
                        case CustomizeJob.PF_SUM:
                            chtarr.add(generateSumationChart(job));
                            break;
                        default:
                            break;
                    }
                    break;
                case CustomizeJob.TYPE_TEXT:   // for text type, we generate pie chart
                    switch (job.pool_func) {
                        case CustomizeJob.PF_COUNT:
                            chtarr.add(generateCountsChart(job));
                            break;
                        case CustomizeJob.PF_COUNT_NOREPEAT:
                            chtarr.add(generateCountsNoRepeat(job));
                            break;
                        default:
                            chtarr.add(generateCountsChart(job));
                            break;
                    }
                    break;
                case CustomizeJob.TYPE_BOOLEAN:  // for Boolean type ,we generate piechart
                    chtarr.add(generateCountsChart(job));
                    break;
                default:
                    chtarr.add(generateCountsChart(job));
                    break;
            }
        }
        return chtarr;
    }

    /*
    * scatter chart with an average line
     */
    private Chart generateAverageChart(CustomizeJob job) {
        DBIResultSet avgvalue = au.getColumnAverage(job.column_name);
        DBIResultSet coldata = au.getColumnData(analyzerUtils.SORT_NONE, job.column_name);
        Debug.log("ave=", avgvalue);
        Debug.log("coldata=", coldata);
        ArrayList<Object> cd = coldata.toArray1D();
        String dta = "";
        String sa = "[@X,@Y],";
        for (int i = 0; i < cd.size(); i++) {
            dta += sa.replace("@X", String.valueOf(i + 1))
                    .replace("@Y", String.valueOf(cd.get(i)));
        }
        int minv = DataValidation.findMin(coldata,1);
        int maxv = DataValidation.findMax(coldata,1);
        String chartops = ChartOption.OPTION_SCATTER_WITH_AVERAGE.replace("@TITLE", job.column_nickname)
                .replace("@SUBTITLE", job.comment)
                .replace("@TOOLTIP", job.column_nickname)
                .replace("@DATA", dta)
                .replace("@AVG_Y", String.valueOf(avgvalue.getData(1, 1)))
                .replace("@AVG_X1", "1")
                .replace("@AVG_X2", String.valueOf(cd.size()))
                .replace("@AVERAGE_TEXT", "average")
                .replace("@XMAX", String.valueOf(cd.size() + 1))
                .replace("@YMAX", String.valueOf( maxv + (maxv-minv)/cd.size() ))
                .replace("@YMIN",String.valueOf( minv - minv/cd.size() ));
        Chart cht = new Chart(chartops, Chart.CHART_SCATTER_AVERGAE);
        Debug.log(cht);
        return cht;
    }
    
    private Chart generateCountsChart(CustomizeJob job) {
        DBIResultSet dbirs = au.getColumnValueCounts(job.column_name);
        Chart cht = chartsHelper.generateBarchart(dbirs);
        cht.title = job.column_nickname;
        cht.sub_title = job.comment;
        return cht;
    }
    
    private Chart generateCountsNoRepeat(CustomizeJob job) {
        DBIResultSet dbirs = au.getColumnValueCountsNoRepeat(job.column_name);
        String xdata = "";
        String datatemp = "{ name: '@NODENAME',value: 1,},";
        for (ArrayList<Object> row : dbirs.getRows()) {
            xdata += datatemp.replace("@NODENAME", String.valueOf(row.get(0)));
        }
        String chartops = ChartOption.OPTION_TREEMAP.replace("@DATA", xdata);
        Chart cht = new Chart(chartops, Chart.CHART_TREE_MAP);
        return cht;
    }
    
    private Chart generateMaxiumChart(CustomizeJob job) {
        DBIResultSet dbirs = au.getColumnMaxiumValue(job.column_name);
        Chart cht = new Chart();
        
        return cht;
    }
    
    private Chart generateMiniumChart(CustomizeJob job) {
        DBIResultSet dbirs = au.getColumnMiniumValue(job.column_name);
        Chart cht = new Chart();
        
        return cht;
    }
    
    private Chart generateSumationChart(CustomizeJob job) {
        //DBIResultSet dbirs = au.getColumnSum(job.column_name);
        DBIResultSet coldata = au.getColumnData(analyzerUtils.SORT_ASC, job.column_name);
        String ydata = "", xdata = "";
        double sum = 0.0;
        int i = 0;
        for (ArrayList<Object> obj : coldata.getRows()) {
            sum += Double.parseDouble(String.valueOf(obj.get(0)));
            ydata += String.valueOf(sum) + ",";
            xdata += String.valueOf(++i) + ",";
        }
        String chartops = ChartOption.OPTION_HISTOGRAM_FULLAREA.replace("@TITLE", job.column_nickname)
                .replace("@SUBTITLE", job.comment)
                .replace("@XDATA", xdata.substring(0, xdata.length() - 1))
                .replace("@YDATA", ydata.substring(0, ydata.length() - 1));
        Chart cht = new Chart(chartops, Chart.CHART_HISTOGRAM_FULLAREA);
        return cht;
    }
    
}
