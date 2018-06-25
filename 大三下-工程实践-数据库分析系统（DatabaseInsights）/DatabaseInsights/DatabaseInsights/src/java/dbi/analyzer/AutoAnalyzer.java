/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Apr 17 2018
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
import dbi.utils.GlobeVar;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author kanch
 */
public class AutoAnalyzer {

    private int uid = -1;
    private String table = "";
    private String database = "";
    private DBILog dbilog;
    private analyzerUtils au;

    public AutoAnalyzer(int uid,String database, String table) {
        this.uid = uid;
        this.table = table;
        this.database = database;
        au = new analyzerUtils(this.uid,database,table);
        dbilog = new DBILog(database,table,uid);
    }

    public ArrayList<Chart> getAutoCharts(int chttype) {
        dbilog.log("perform automatic analysis.");
        switch (chttype) {
            case Chart.CHART_HISTOGRAM:
                return getAutoHistogramCharts();
            case Chart.CHART_LINECHART:
                return getAutoLineCharts();
            case Chart.CHART_PIECHART:
                return getAutoPieCharts();
            default:
                return new ArrayList<Chart>();
        }
    }

    public ArrayList<Chart> getAutoPieCharts() {
        ArrayList<Chart> charts_list = new ArrayList<Chart>();
        DBIResultSet distinctVals = au.findDistinctValues();
        Debug.log("distinctVals.length=", distinctVals.rowCount());
        Debug.log("distinctVals=", distinctVals);
        if (distinctVals.rowCount() < 1) {
            return charts_list;
        }
        //check columns to draw piecharts
        // here is how we dectect:
        //        less than 5 distinct values column will be rendered to piecharts
        Debug.log("Generate Piechart...--------cur chart_list.length=", charts_list.size());
        ArrayList<String> cols = new ArrayList<>();
        for (int i = 1; i <= distinctVals.rowCount(); i++) {
            int ditvalcount = Integer.valueOf((String) distinctVals.getData(i, 2));
            if (ditvalcount < 5 && ditvalcount > 0) {
                cols.add((String) distinctVals.getData(i, 1));
            }
        }
        // now render parameters for piecharts
        DBIResultSet dbirsbuf = au.getDistinctValuesCount( cols.toArray()); // return name ,value ,counts
        if (dbirsbuf.rowCount() > 0) {
            HashMap<String, DBIResultSet> piecharts = new HashMap<>();
            for (ArrayList<Object> row : dbirsbuf.getRows()) {
                DBIResultSet piedata = new DBIResultSet();
                String colname = (String) row.get(0);
                if (piecharts.containsKey(colname)) {
                    piedata = piecharts.get(colname);
                }
                piedata.addToRow((String) row.get(1));
                piedata.addToRow((String) row.get(2));
                piedata.finishRow();
                piecharts.put(colname, piedata);
            }
            for (String key : piecharts.keySet()) {
                Chart cht = chartsHelper.generateBarchart(piecharts.get(key));
                cht.title = "Value Accounting of Table " + table + "." + key;
                charts_list.add(cht);
            }
        }
        return charts_list;
    }

    public ArrayList<Chart> getAutoLineCharts() {
        ArrayList<Chart> charts_list = new ArrayList<Chart>();
        DBIResultSet colSpecies = au.getAllColumnSpecies();
        //check columns to draw linecharts
        //methodlogy: draw linecharts for every numberic columns excluding primary keys
        //            then draw statistics of the values for every column which is not numberic
        Debug.log("colSpecies=", colSpecies);
        Debug.log("Generate linecharts...--------cur chart_list.length=", charts_list.size());
        ArrayList<String> cols = new ArrayList<>();
        for (int i = 1; i <= colSpecies.rowCount(); i++) {
            //Debug.log("-Detecting column with type ", colSpecies.getRow(i).get(5));
            if (colSpecies.getRow(i).get(5).equals(au.getUserDatabaseType("NUMBER"))) {
                cols.add((String) colSpecies.getRow(i).get(4));
                Debug.log("--Found ", colSpecies.getRow(i).get(5));
            }
        }
        // now render parameters for linecharts
        DBIResultSet dbirsbuf = au.getColumnValues( cols.toArray()); // return column name,values
        Debug.log("dbirsbuf=",dbirsbuf);
        if (dbirsbuf.rowCount() > 0) {
            for (ArrayList<Object> row : dbirsbuf.getRows()) {
                String colname = (String) row.get(0);
                DBIResultSet linedata = (DBIResultSet) row.get(1);
                Chart cht = chartsHelper.generateLinechart(linedata);
                cht.title = "Trend of " + table + "." + colname;
                charts_list.add(cht);
            }
        }
        return charts_list;
    }

    public ArrayList<Chart> getAutoHistogramCharts() {
        ArrayList<Chart> charts_list = new ArrayList<Chart>();
        DBIResultSet distValues = au.getAllColumnSpecies();
        //check columns to draw histogramcharts
        //methodlogy: draw linecharts for every numberic columns excluding primary keys
        Debug.log("Generate histogram charts...--------cur chart_list.length=", charts_list.size());
        
        return charts_list;
    }

    public static void main(String[] argvs) {
        AutoAnalyzer aa = new AutoAnalyzer(GlobeVar.OBJ_MANAGER_USER.getUIDbySessionID("19105E36BA6793CBA237F6510CCDD028"),"11", "T_DI_USER");
    }

}
