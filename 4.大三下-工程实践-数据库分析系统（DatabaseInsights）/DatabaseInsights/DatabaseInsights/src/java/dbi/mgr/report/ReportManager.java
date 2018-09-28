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

import dbi.db.adaptor.DatabaseConfig;
import dbi.db.adaptor.DatabaseHelper;
import dbi.utils.DBIDataExchange;
import dbi.utils.DBILog;
import dbi.utils.DBIResultSet;
import dbi.utils.DataValidation;
import dbi.utils.Debug;
import dbi.utils.GlobeVar;
import java.util.ArrayList;

/**
 *
 * @author kanch
 */
public class ReportManager {

    private final DatabaseConfig dbconfig = GlobeVar.VAR_DATABASE_CONFIG;
    private final DatabaseHelper dbhelper;
    private DBILog dbilog;

    public ReportManager() {
        dbhelper = new DatabaseHelper(dbconfig);
        dbhelper.Connect();
        dbilog = new DBILog();
    }

    /*
    * 向给定用户添加一个分析报告
     */
    public boolean addReport(int uid, Report rep) {
        Debug.log("uid:", Integer.toString(uid), ",title:", rep.title, ",descrption:", rep.des);
        dbilog.log(String.valueOf(uid), DBILog.TYPE_INFO, "create a new report with title " + rep.title);
        try {
            if (dbhelper.Connect()) {
                int ret = dbhelper.executeOracleFunction("F_INSERT_REPORT(?,?,?,?,?)",
                        Integer.toString(uid), rep.title, rep.des,
                        DataValidation.encodeToBase64(DBIDataExchange.makeupInternalExchangeData(rep.charts.getRows())),
                        rep.relations);
                if (ret != 1) {
                    Debug.log("error in save report");
                    return false;
                }
            }
            return true;
        } catch (Exception e) {
            Debug.error(e);
        }
        return false;
    }

    /*
    * 获得指定ID的分析报告信息
     */
    public Report getReport(int repid) {
        Report rep = new Report();
        if (dbhelper.Connect()) {
            String sql = "SELECT * FROM T_DATABASE_REPORT WHERE RID=" + String.valueOf(repid);
            DBIResultSet ret = dbhelper.runSQLForResult(sql);
            rep.id = Integer.parseInt(ret.getData(1, 1, String.class));
            rep.userid = Integer.parseInt(ret.getData(1, 2, String.class));
            rep.title = ret.getData(1, 3, String.class);
            rep.generatedate = ret.getData(1, 4, String.class);
            rep.des = ret.getData(1, 5, String.class);
            rep.charts = DBIDataExchange.parse(DataValidation.decodeFromBase64(ret.getData(1, 6, String.class)));
            rep.relations = ret.getData(1, 7, String.class);
        }
        return rep;
    }

    /*
    * delete report by report id
     */
    public boolean deleteReport(int repid) {
        if (dbhelper.Connect()) {
            try {
                dbhelper.executeOracleFunction("F_DELETE_REPORT(?)", String.valueOf(repid));
            } catch (Exception e) {
                Debug.error(e);
                return false;
            }
        }
        return true;
    }

    /**
     * 给定用户ID，获得该用户所有分析报告列表
     */
    public ArrayList<Report> getUserReportsList(int uid) {
        ArrayList<Report> replist = new ArrayList<>();
        if (dbhelper.Connect()) {
            String sql = "SELECT RID,USERID,TITLE,GENERATEDATE,DESCRIPTION,RELATION FROM T_DATABASE_REPORT WHERE USERID=" + String.valueOf(uid);
            DBIResultSet ret = dbhelper.runSQLForResult(sql);
            for (int i = 1; i <= ret.rowCount(); i++) {
                Report rep = new Report();
                rep.id = Integer.parseInt(ret.getData(i, 1, String.class));
                rep.userid = Integer.parseInt(ret.getData(i, 2, String.class));
                rep.title = ret.getData(i, 3, String.class);
                rep.generatedate = ret.getData(i, 4, String.class);
                rep.des = ret.getData(i, 5, String.class);
                rep.relations = ret.getData(i, 6, String.class);
                replist.add(rep);
            }
        }
        return replist;
    }

    public String generateReportEmail(int repid) {
        Report rep = getReport(repid);
        String email_content = "<p>Dear User,</p>"
                + "<p>Thanks for using Database Insights ( <a href=\"https://github.com/ankanch/DatabaseInsights\">https://github.com/ankanch/DatabaseInsights</a> ).</p>"
                + "<p>Here is the report you request.</p>"
                + "<p> </p>"
                + "<p><strong>Report Title:</strong> @TITLE</p>"
                + "<p><strong>Description:</strong> @DES</p>"
                + "<p><strong>Generate Date:</strong> @DATE</p>"
                + "<p><strong>Report Link:</strong> http://localhost/report.viewfull.jsp?repid=@LINK</p>"
                + "<p> </p>"
                + "<blockquote><span style=\"color: #0000ff;\">Database Insights © 2018 .</span><span style=\"color: #0000ff;\">You recive this email because you request the report.</span></blockquote>";
        email_content = email_content.replace("@TITLE", rep.title)
                .replace("@DES", rep.des)
                .replace("@DATE", rep.generatedate)
                .replace("@LINK", String.valueOf(rep.id));
        return email_content;
    }

    public static void main(String[] argv) {

        ReportManager report = new ReportManager();
        ReportManager rm = new ReportManager();
        Report rp = new Report();
        //Debug.log("addReport=",rm.addReport(43, rp));
        Debug.log("getReport=", rm.getReport(105));
        Debug.log("getUserReportsList=", rm.getUserReportsList(48));

    }

}
