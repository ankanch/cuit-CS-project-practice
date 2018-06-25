/*
 * The MIT License
 *
 * *** Copyright © ChengShiyi (Miss Zhang)
 * *** Code created on  五月 21 2018
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
package dbi.utils;

import dbi.db.adaptor.DatabaseConfig;
import dbi.db.adaptor.DatabaseHelper;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 *
 * @author Miss Zhang
 */
public class DBILog {

    public String dbname;
    public String tname;
    public int userid;
    private final DatabaseConfig dbconfig = GlobeVar.VAR_DATABASE_CONFIG;
    private final DatabaseHelper dbhelper;
    private final SimpleDateFormat df;
    public static final int TYPE_INFO = 1000;
    public static final int TYPE_ERROR = 1005;
    public static final int TYPE_WARNING = 1010;

    public DBILog(String dbname, String tname, int userid) {
        this.dbname = dbname;
        this.tname = tname;
        this.userid = userid;
        dbhelper = new DatabaseHelper(dbconfig);
        df = new SimpleDateFormat("yyyy-MM-dd HH:mm:s");
    }

    public DBILog() {
        this.dbhelper = new DatabaseHelper(dbconfig);
        df = new SimpleDateFormat("yyyy-MM-dd HH:mm:s");
    }

    public void log(String message) {
        Date day = new Date();
        commit(" VALUES(" + userid + ",1000" + ",TO_DATE('" + df.format(day) + "','yyyy-mm-dd hh24:mi:ss'),'"
                + dbname + "','" + tname + "','" + message + "') ");
    }

    public void log(String uid, int type, String message) {
        Date day = new Date();
        commit(" VALUES(" + uid + "," + String.valueOf(type) + ",TO_DATE('" + df.format(day)
                + "','yyyy-mm-dd hh24:mi:ss'),'N/A','N/A','" + message + "') ");
    }

    public void logError(String message) {
        Date day = new Date();
        commit(" VALUES(" + userid + ",1005" + ",TO_DATE('" + df.format(day) + "','yyyy-mm-dd hh24:mi:ss'),'"
                + dbname + "','" + tname + "','" + message + "') ");
    }

    public void logWarning(String message) {
        Date day = new Date();
        commit(" VALUES(" + userid + ",1010" + ",TO_DATE('" + df.format(day) + "','yyyy-mm-dd hh24:mi:ss'),'"
                + dbname + "','" + tname + "','" + message + "') ");
    }

    private void commit(String insertvals) {
        if (dbhelper.Connect()) {
            String sql = "INSERT INTO T_DI_LOG(USERID,LTYPE,LDATE,LDBNAME,LTNAME,LMESSAGE) " + insertvals;
            if (!dbhelper.runSQL(sql)) {
                Debug.error("DBILog error.");
            }
        }
    }

    public DBIResultSet searchlog(String uid, String time) {
        String times = "";
        DBIResultSet result = null;
        switch (time) {
            case "7d":
                times = "where LDATE between sysdate - interval '7' day and sysdate and userid='" + uid + "'";
                break;
            case "1m":
                times = "where LDATE between sysdate - interval '30' day and sysdate and userid='" + uid + "'";
                break;
            case "6m":
                times = "where LDATE between sysdate - 150 and sysdate and userid='" + uid + "'";
                break;
            case "7m":
                times = "where LDATE between sysdate - interval '7' month and sysdate and userid='" + uid + "'";
                break;
            case "1y":
                times = "where LDATE between sysdate - 365 and sysdate and userid='" + uid + "'";
                break;
            case "all":
                times = "where userid='" + uid + "'";
                break;
        }
        String sql = "select * from T_DI_LOG " + times;
        if (dbhelper.Connect()) {
            result = dbhelper.runSQLForResult(sql);
        } else {
            System.out.println("wrong");
        }
        return result;
    }
    
    public DBIResultSet getRecentLog(String sid){
        DBIResultSet dbirs = searchlog(String.valueOf(GlobeVar.OBJ_MANAGER_USER.getUIDbySessionID(sid)),"全部");
        if(dbirs == null){
            return null;
        }
        if(dbirs.rowCount()  < 5){
            return dbirs;
        }
        DBIResultSet ret = new DBIResultSet();
        for(int i=1;i<=5;i++){
            ret.addRow(dbirs.getRow(i));
        }
        return ret;
    }

    public static void main(String args[]) {
        DBILog dbilog = new DBILog("DatabaseInsights", "T_DI_USER", 43);
        dbilog.log("user logged in.");
        dbilog.logWarning("try to login, but password incorrect.");
        dbilog.logError("Password incorrect for 10 times");
    }
}
