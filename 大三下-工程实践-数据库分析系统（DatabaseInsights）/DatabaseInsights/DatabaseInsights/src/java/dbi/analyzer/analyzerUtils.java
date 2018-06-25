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

import dbi.db.adaptor.DatabaseConfig;
import dbi.db.adaptor.DatabaseHelper;
import dbi.utils.DBIResultSet;
import dbi.utils.Debug;
import dbi.utils.GlobeVar;
import java.util.ArrayList;

/**
 *
 * @author kanch
 */
public class analyzerUtils {

    public static final String SORT_ASC = " ORDER BY @COL ASC";
    public static final String SORT_DESC = " ORDER BY @COL DESC";
    public static final String SORT_NONE = " ";

    private DatabaseConfig dbconfig = GlobeVar.VAR_DATABASE_CONFIG;
    private DatabaseHelper dbhelper;

    private int uid;
    private String database;
    private String table;
    private DatabaseHelper user;

    public analyzerUtils(int uid, String database, String table) {
        this.uid = uid;
        this.database = database;
        this.table = table;
        dbhelper = new DatabaseHelper(dbconfig);
        if (dbhelper.Connect()) {
            user = dbhelper.getUserdbhelper(this.uid,database);
        }
    }
    
    public String getUserDatabaseType(String type){
        return user.getDatabaseTypeName(type);
    }

    /**
     * 获取一列的所有数据,参数指定是否排序，否则为SORT_NONE 返回值：DBIResultSet，多行，每行一个数据
     */
    public DBIResultSet getColumnData(String sort, String column) {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String sql = "select " + column + " from " + table + sort.replace("@COL", column);
                ret = user.runSQLForResult(sql);
            }
        }
        return ret;
    }

    /**
     * 从columnspecies中得到指定用户的指定表的所有列的全部信息<br/>
     * 返回值：DBIResultSet，每一行包含表的一列的全部信息
     */
    public DBIResultSet getAllColumnSpecies() {
        DBIResultSet dbire = new DBIResultSet();
        String sql = "select * from T_DATABASE_COLUMN where TID in (select tid from T_DATABASE_TABLE where tname='"
                + table + "') "
                + "and userid=" + uid;
        if (dbhelper.Connect()) {
            dbire = dbhelper.runSQLForResult(sql);
        }
        dbhelper.Disconnect();
        return dbire;
    }

    /**
     * 得到指定用户的指定表每一列不重复的值的数量<br/>
     * 返回值：DBIResultSet，多行，每行由2列组成，分别存放列名，列不重复值个数
     */
    public DBIResultSet findDistinctValues() {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String column = "";
                DBIResultSet tablename = dbhelper.runSQLForResult("select distinct columnname  from t_database_column where userid=" + uid + " and "
                        + "tid in(select tid from T_DATABASE_TABLE where tname='" + table + "')");
                for (int i = 0; i < tablename.rowCount() - 1; i++) {
                    column = column + "count(distinct " + tablename.getRow(i + 1).get(0) + "),";
                }
                column = column + " count(distinct " + tablename.getRow(tablename.rowCount()).get(0) + ")";
                Debug.log(column);
                String sql = "select " + column + " from " + table;
                Debug.log(sql);
                DBIResultSet dbire = user.runSQLForResult(sql);
                //拼凑结果集 ---格式： 多行，每一行为 [列名,列不重复值个数]
                for (int i = 1; i <= tablename.rowCount(); i++) {
                    ArrayList<Object> row = new ArrayList<>();
                    row.add(tablename.getData(i, 1));
                    row.add(dbire.getData(1, i));
                    ret.addRow(row);
                }
            }
        }
        return ret;
    }

    /**
     * 得到指定用户的指定表每一列最大的值<br/>
     * 返回值：DBIResultSet，只有一行，按照在表中列的顺序依次展示每一列最大的值
     */
    public DBIResultSet getMaxiumValues() {
        DBIResultSet dbire = new DBIResultSet();

        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                DBIResultSet result = user.getIsNumberColumns(uid, table);
                for (int i = 0; i < result.rowCount(); i++) {
                    if (result.getRow(i + 1).get(1).equals("1")) {
                        DBIResultSet max = user.runSQLForResult("select max(" + result.getRow(i + 1).get(0) + ") from " + table);
                        dbire.addToRow(max.getRow(1).get(0));
                    } else {
                        dbire.addToRow(null);
                    }
                }
                dbire.finishRow();
            }
        }
        return dbire;
    }

    /**
     * 得到指定用户的指定表每一列最小的值<br/>
     * 返回值：DBIResultSet，只有一行，按照在表中列的顺序依次展示每一列最小的值
     */
    public DBIResultSet getMiniumValues() {
        DBIResultSet dbire = new DBIResultSet();

        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                DBIResultSet result = user.getIsNumberColumns(uid, table);
                for (int i = 0; i < result.rowCount(); i++) {
                    if (result.getRow(i + 1).get(1).equals("1")) {
                        DBIResultSet min = user.runSQLForResult("select min(" + result.getRow(i + 1).get(0) + ") from " + table);
                        dbire.addToRow(min.getRow(1).get(0));
                    } else {
                        dbire.addToRow(null);
                    }
                }
                dbire.finishRow();
            }
        }
        return dbire;
    }

    /**
     * 得到指定用户的指定表每一列的平均值<br/>
     * 返回值：DBIResultSet，只有一行，按照在表中列的顺序依次展示每一列的平均值
     */
    public DBIResultSet getAverangeValues() {
        DBIResultSet dbire = new DBIResultSet();

        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                DBIResultSet result = user.getIsNumberColumns(uid, table);
                for (int i = 0; i < result.rowCount(); i++) {
                    if (result.getRow(i + 1).get(1).equals("1")) {
                        DBIResultSet avg = user.runSQLForResult("select avg(" + result.getRow(i + 1).get(0) + ") from " + table);
                        dbire.addToRow(avg.getRow(1).get(0));
                    } else {
                        dbire.addToRow(null);
                    }
                }
                dbire.finishRow();
            }
        }
        return dbire;
    }

    /**
     * 得到指定用户的指定表每一列的和<br/>
     * 返回值：DBIResultSet，只有一行，按照在表中列的顺序依次展示每一列的和
     */
    public DBIResultSet getAllColumnSum() {
        DBIResultSet dbire = new DBIResultSet();

        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                DBIResultSet result = user.getIsNumberColumns(uid, table);
                for (int i = 0; i < result.rowCount(); i++) {
                    if (result.getRow(i + 1).get(1).equals("1")) {
                        DBIResultSet sum = user.runSQLForResult("select sum(" + result.getRow(i + 1).get(0) + ") from " + table);
                        dbire.addToRow(sum.getRow(1).get(0));
                    } else {
                        dbire.addToRow(null);
                    }
                }
                dbire.finishRow();
            }
        }
        return dbire;
    }

    /**
     * 获取给定表的给定列的所有不同值以及其个数<br/>
     * 返回值：DBIResultSet，多行，每行由3列组成，分别存放列名字，不同值，值出现次数
     */
    public DBIResultSet getDistinctValuesCount(Object[] columns) {
        DBIResultSet ret = new DBIResultSet();
        if (columns.length < 1) {
            return ret;
        }
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                for (int i = 0; i < columns.length; i++) {
                    DBIResultSet tablename = user.runSQLForResult("select count(" + columns[i] + ")," + columns[i] + " from " + table + " group by " + columns[i] + "");
                    for (int j = 0; j < tablename.rowCount(); j++) {
                        ArrayList<Object> row = new ArrayList<>();
                        row.add(columns[i]);
                        row.add(tablename.getData(j + 1, 2));
                        row.add(tablename.getData(j + 1, 1));
                        ret.addRow(row);
                    }
                }
            }
        }
        return ret;
    }

    /**
     * 获取给定表的给定列的所有值列表<br/>
     * 返回值：DBIResultSet，多行，每行由2列组成，第一列为列名，第2列的所有值数组
     */
    public DBIResultSet getColumnValues(Object[] columns) {
        DBIResultSet ret = new DBIResultSet();
        if (columns.length < 1) {
            return ret;
        }
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                for (int i = 0; i < columns.length; i++) {
                    DBIResultSet coldata = user.runSQLForResult("select " + columns[i] + " from " + table);
                    Debug.log("coldata=", coldata);
                    ret.addToRow(columns[i]);
                    ret.addToRow(coldata);
                    ret.finishRow();
                }
            }
        }
        return ret;
    }

    /**
     * *********************************************************************
     * Pooling functions for customize analyze on Columns
     * *********************************************************************
     */
    /**
     * 获取给定列的平均值<br/>
     * 返回值：DBIResultSet，1行，列名，平均值
     */
    public DBIResultSet getColumnAverage(String column) {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String sql = "SELECT AVG(" + column + ") FROM " + table;
                ret = user.runSQLForResult(sql);
            }
        }
        return ret;
    }

    /**
     * 获取给定列的最大值<br/>
     * 返回值：DBIResultSet，1行，列名，最大值
     */
    public DBIResultSet getColumnMaxiumValue(String column) {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String sql = "SELECT MAX(" + column + ") FROM " + table;
                ret = user.runSQLForResult(sql);
            }
        }
        return ret;
    }

    /**
     * 获取给定列的最小值<br/>
     * 返回值：DBIResultSet，1行，列名，最小值
     */
    public DBIResultSet getColumnMiniumValue(String column) {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String sql = "SELECT MIN(" + column + ") FROM " + table;;
                ret = user.runSQLForResult(sql);
            }
        }
        return ret;
    }

    /**
     * 获取给定列的总和<br/>
     * 返回值：DBIResultSet，1行，列名，总和
     */
    public DBIResultSet getColumnSum(String column) {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String sql = "SELECT SUM(" + column + ") FROM " + table;
                ret = user.runSQLForResult(sql);
            }
        }
        return ret;
    }

    /**
     * 获取给定列所有值的分组统计结果<br/>
     * 返回值：DBIResultSet，多行，每行由2列组成，第一列为值，第2列为数量
     */
    public DBIResultSet getColumnValueCounts(String column) {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String sql = "SELECT " + column + ",COUNT(" + column + ") FROM " + table + " GROUP BY " + column;
                ret = user.runSQLForResult(sql);
            }
        }
        return ret;
    }

    /**
     * 获取给定列所有不同值的个数<br/>
     * 返回值：DBIResultSet，多行，每行由1列组成，存放不同数据值
     */
    public DBIResultSet getColumnValueCountsNoRepeat(String column) {
        DBIResultSet ret = new DBIResultSet();
        if (dbhelper.Connect()) {
            if ((user = DatabaseHelper.isAvailable(user)) != null) {
                String sql = "SELECT DISTINCT " + column + " FROM " + table;
                ret = user.runSQLForResult(sql);
            }
        }
        return ret;
    }

    public static void main(String args[]) {
        analyzerUtils au = new analyzerUtils(43, "DatabaseInsights", "T_DI_USER");
        Debug.log("getAllColumnSpecies=", au.getAllColumnSpecies());
        Debug.log("findDistinctValues=", au.findDistinctValues());
        Debug.log("getMaxiumValues=", au.getMaxiumValues());
        Debug.log("getMiniumValues=", au.getMiniumValues());
        Debug.log("getAverangeValues=", au.getAverangeValues());
        Debug.log("getAllColumnSum=", au.getAllColumnSum());
        String columns[] = {"password", "email"};
        Debug.log("getColumnData=",au.getColumnData(SORT_DESC, "USERID"));
        Debug.log("getDistinctValuesCount=", au.getDistinctValuesCount(columns));
        Debug.log("getColumnAverage=", au.getColumnAverage("USERID"));
        Debug.log("getColumnAverage=", au.getColumnMaxiumValue("STATUS"));
        Debug.log("getColumnMiniumValue=", au.getColumnMiniumValue("STATUS"));
        Debug.log("getColumnSum=", au.getColumnSum("STATUS"));
        Debug.log("getColumnValueCounts=", au.getColumnValueCounts("STATUS"));
        Debug.log("getColumnValueCountsNoRepeat=", au.getColumnValueCountsNoRepeat("STATUS"));
    }

}
