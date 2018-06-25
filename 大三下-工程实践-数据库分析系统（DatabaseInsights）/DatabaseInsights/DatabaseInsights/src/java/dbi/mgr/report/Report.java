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
package dbi.mgr.report;

import dbi.utils.DBIDataExchange;
import dbi.utils.DBIResultSet;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 *
 * @author kanch
 */
public class Report {

    public String title = "";
    public String des = "";
    public DBIResultSet charts = new DBIResultSet();  // 多行两列，第一行存放图表信息，第二存放用户针对改图表添加的信息
    public int id = 0;
    public int userid = 0;
    public String relations = ""; //存放参与分析的数据库表
    public String generatedate = "";

    public Report() {
    }

    public Report(String datastring) {
        String[] decoded = datastring.split("<@REPSP!>");
        title = decoded[0];
        des = decoded[1];
        charts = DBIDataExchange.parse(decoded[2]);
        relations = decoded[3];
        Date now = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); 
        generatedate = sdf.format(now);
    }

    @Override
    public String toString() {
        DBIResultSet ret = new DBIResultSet();
        ret.addToRow(title);
        ret.addToRow(des);
        ret.addToRow(id);
        ret.finishRow();
        ret.addRow(charts.getRows().get(0));
        ret.addRow(charts.getRows().get(1));
        return  DBIDataExchange.makeupInternalExchangeData(ret.getRows()) ;
    }

}
