
/*
 * The MIT License
 *
 * **** Copyright © Long Zhang(kanch) , ChengShiyi.
 * **** Code created on Mar 01 2018
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
package dbi.db.adaptor;

import dbi.utils.DBIResultSet;
import dbi.utils.Debug;
import dbi.utils.GlobeVar;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Types;
import java.text.MessageFormat;
import java.util.Arrays;
import java.util.HashMap;

/**
 *
 * @author ChengShiyi
 */
public class DatabaseHelper {

    private DatabaseAdaptor DBAdaptor;
    private DatabaseConfig databaseConfig;
    private Connection conn;

    public DatabaseHelper(DatabaseConfig databaseConfig) {
        this.databaseConfig = databaseConfig;
        int dbcode = this.databaseConfig.getDatabase();

        if (dbcode == DatabaseConfig.DatabaseCode.DATABASE_MYSQL) {
            DBAdaptor = new MySQLAdaptor();
        } else if (dbcode == DatabaseConfig.DatabaseCode.DATABASE_ORACLE_12C) {
            DBAdaptor = new OracleAdaptor();
        }
    }

    /*
    * 检查 给定DatabaseHelper对象是否为空，以及是否已经建立连接,如果未建立连接，则尝试建立连接
     */
    public static DatabaseHelper isAvailable(DatabaseHelper dbh) {
        if (null != dbh) {
            if (dbh.checkConnection()) {
                return dbh;
            } else if (dbh.Connect()) {
                return dbh;
            }
        }
        return null;
    }
    
    public String getDatabaseTypeName(String type){
        return DBAdaptor.sql_getTypeName(type);
    }

    /**
     * 连接数据库<br/>
     * 返回值：Boolean，连接数据库是否成功
     */
    public Boolean Connect() {
        if (!checkConnection()) {
            try {
                // 创建数据库连接
                Class.forName(databaseConfig.getDriver());
                //Debug.log(databaseConfig.getHost());
                //Debug.log(databaseConfig.getDriver());
                //Debug.log("dbhose=",databaseConfig.getHost(),"\tuname=",databaseConfig.getUsername(),"\tpwd=",databaseConfig.getPassword());
                conn = DriverManager.getConnection(databaseConfig.getHost(), databaseConfig.getUsername(), databaseConfig.getPassword());
            } catch (Exception e) {
                Debug.error(e);
                return false;
            }
        }
        return true;
    }

    /**
     * 检查数据库是否连接<br/>
     * 返回值：Boolean，若成功连接返回true，不成功返回false
     */
    private Boolean checkConnection() {
        try {
            if (conn.isClosed()) {
                return false;
            }
        } catch (Exception e) {
            //Debug.error(e);
            return false;
        }
        return true;
    }

    /**
     * 解除数据库连接<br/>
     * 返回值：无
     */
    public void Disconnect() {
        try {
            conn.close();
        } catch (Exception e) {
            Debug.error(e);
        }
    }

    /**
     * 得到一个给定数据库的全部表的名字<br/>
     * 返回值：DBIResultSet，每一行是一个表名
     *
     * @param <error>
     */
    public DBIResultSet getTables(String dbname) {
        DBIResultSet tables = new DBIResultSet();
        String table_name = "";
        String tablename = "";
        try {
            Statement st = conn.createStatement();
            // 执行数据库语句
            ResultSet rs = st.executeQuery(DBAdaptor.getTableList());
            // 遍历获取结果
            if (databaseConfig.getDatabase() == DatabaseConfig.DatabaseCode.DATABASE_MYSQL) {
                tablename = "Tables_in_" + dbname;
            } else if (databaseConfig.getDatabase() == DatabaseConfig.DatabaseCode.DATABASE_ORACLE_12C) {
                tablename = "table_name";
            }
            while (rs.next()) {
                table_name = rs.getString(tablename);
                tables.addToRow(table_name);
            }
            tables.finishRow();
            st.close();
        } catch (Exception e) {
            Debug.error(e);
        }
        return tables;
    }

    /**
     * 得到给定表的全部列名<br/>
     * 返回值：DBIResultSet，每一行是一个列名
     */
    public DBIResultSet getColumns(String table) {
        DBIResultSet columns = new DBIResultSet();
        String column_name = "";
        try {
            Statement st = conn.createStatement();
            // 执行数据库语句
            ResultSet rs = st.executeQuery(DBAdaptor.getColumnNamesByTable(table));
            // 遍历获取结果

            while (rs.next()) {
                column_name = rs.getString("column_name");
                columns.addToRow(column_name);
            }
            columns.finishRow();
            st.close();
        } catch (Exception e) {
            Debug.error(e);
        }
        return columns;
    }

    /**
     * 得到一个给定表的全部列的性质，并存入T_DATABASE_COLUMN表中<br/>
     * 返回值：DBIResultSet，每一行是一个列的全部性质
     */
    public DBIResultSet getAllColumnSpecies(String table, int userid, int did, DatabaseHelper dbhelper) {
        DBIResultSet getresult = runSQLForResult(DBAdaptor.findTablecolspe(table));
        DBIResultSet primary = runSQLForResult(DBAdaptor.findPrimaryKey(table));
        DBIResultSet foreign = runSQLForResult(DBAdaptor.findForeignKey(table));
        DBIResultSet tid = new DBIResultSet();
        DBIResultSet species = new DBIResultSet();
        tid = dbhelper.runSQLForResult("select tid from T_DATABASE_TABLE where TNAME='" + getresult.getRow(1).get(0) + "'");
        int isPrimary = 0;
        int isRef = 0;
        for (int i = 1; i <= getresult.rowCount(); i++) {
            if (primary.rowCount() != 0) {
                if (getresult.getRow(i).get(1).equals(primary.getRow(1).get(0))) {
                    isPrimary = 1;
                } else {
                    isPrimary = 0;
                }
            }

            if (foreign.rowCount() != 0) {
                for (int j = 0; j < foreign.rowCount(); j++) {
                    if (getresult.getRow(i).get(1).equals(foreign.getRow(j + 1).get(0))) {
                        isRef = 1;
                    }
                }
            }
            species.addToRow(tid.getRow(1).get(0));
            species.addToRow(did);
            species.addToRow(userid);
            species.addToRow(getresult.getRow(i).get(1));
            species.addToRow(getresult.getRow(i).get(2));
            species.addToRow(isPrimary);
            species.addToRow(isRef);
            species.finishRow();
            dbhelper.runSQL("insert into T_DATABASE_COLUMN(TID,DID,USERID,COLUMNNAME,DATATYPE,ISPRIMARY,ISFOREIGNKEY) \n"
                    + "values(" + tid.getRow(tid.rowCount()).get(0) + "," + did
                    + "," + userid + ",'" + getresult.getRow(i).get(1) + "','"
                    + getresult.getRow(i).get(2) + "'," + isPrimary + "," + isRef + ")");
            isRef = 0;
        }
        return species;
    }

    /**
     * 运行select语句<br/>
     * 返回值：DBIResultSet，返回select操作后的全部结果
     */
    public DBIResultSet runSelect(String querys, String table, String condition) {
        DBIResultSet sqlResult = null;
        try {
            Statement st = conn.createStatement();
            String sql = DBAdaptor.generateSelect(querys, table, condition);
            // 执行数据库语句
            Debug.log("SQL=", sql);
            sqlResult = new DBIResultSet(st.executeQuery(sql));
            st.close();
        } catch (SQLException e) {
            Debug.error(e);
        }

        return sqlResult;
    }

    /**
     * 运行含有多个表的select语句<br/>
     * 返回值：DBIResultSet，返回select操作后的全部结果
     */
    public DBIResultSet runJoinSelect(String querys, String[] tables, String joinconditions) {
        DBIResultSet sqlResult = null;
        try {
            Statement st = conn.createStatement();
            String table = tables[0];
            for (int i = 1; i <= tables.length - 1; i++) {
                table = table + "," + tables[i];
                System.out.println(table);
            }
            String sql = "select " + querys + " from " + table + " where " + joinconditions;
            // 执行数据库语句
            Debug.log("SQL=", sql);
            ResultSet rs = st.executeQuery(sql);
            sqlResult = new DBIResultSet(rs);
        } catch (Exception e) {
            Debug.error(e);
        }
        return sqlResult;
    }

    /**
     * 运行update语句<br/>
     * 返回值：boolean，返回update是否成功
     */
    public boolean runUpdate(String table, HashMap<String, Object> keyValues, String condition) {
        // make up SQL UPDATE statment
        String SQL = "UPDATE {0} SET {1} WHERE {2}";
        String kvstr = "";
        for (String key : keyValues.keySet()) {
            Object val = keyValues.get(key);
            if (val instanceof String) {
                kvstr += key + "='" + (String) val + "',";
            } else if (val instanceof Integer) {
                kvstr += key + "=" + String.valueOf((Integer) val) + ",";
            } else if (val instanceof Boolean) {
                kvstr += key + "=" + String.valueOf((Boolean) val) + ",";
            }
        }
        kvstr = kvstr.substring(0, kvstr.length() - 1);
        if (condition.length() < 1) {
            // no condition provided
            condition = " true ";
        }
        SQL = MessageFormat.format(SQL, table, kvstr, condition);
        Debug.log("SQL=", SQL);
        //Execute update statment
        try {
            Statement st = conn.createStatement();
            st.executeUpdate(SQL);
            st.close();
        } catch (Exception e) {
            Debug.error(e);
            return false;
        }
        return true;
    }

    /**
     * 运行sql语句<br/>
     * 返回值：boolean，返回sql执行是否成功，成功返回true，不成功返回false
     */
    public boolean runSQL(String sql) {
        try {
            Debug.log(sql);
            Statement st = conn.createStatement();
            st.executeUpdate(sql);
            st.close();
        } catch (Exception e) {
            Debug.error(e);
            return false;
        }
        return true;
    }

    /**
     * 运行sql语句<br/>
     * 返回值：boolean，返回sql执行结果
     */
    public DBIResultSet runSQLForResult(String sql) {
        DBIResultSet sqlResult = new DBIResultSet();
        try {
            Statement st = conn.createStatement();
            // 执行数据库语句
            Debug.log("SQL=", sql);
            ResultSet rs = st.executeQuery(sql);
            sqlResult = new DBIResultSet(rs);
            st.close();
        } catch (Exception e) {
            Debug.error(e);
        }
        return sqlResult;
    }

    /**
     * 运行oracle函数 返回值：int，返回执行结果（成功与否）
     */
    public int executeOracleFunction(String funcDef, String... params) throws SQLException {
        String query = "{? = call @funcDef@}".replace("@funcDef@", funcDef);
        CallableStatement statement = conn.prepareCall(query);
        statement.registerOutParameter(1, Types.INTEGER);
        for (int i = 2; i <= params.length + 1; i++) {
            statement.setString(i, params[i - 2]);
        }
        statement.execute();
        return statement.getInt(1);
    }

    /**
     * 检查给定用户表的每一列是否为数字或非数字。如果是数字，为1，如果不是，为0<br/>
     * 返回值：DBIResultSet，每一行包含列名和是否为数字列
     */
    public DBIResultSet getIsNumberColumns(int uid, String table) {
        DBIResultSet tables = new DBIResultSet();
        String numberType[] = DBAdaptor.numberType();
        try {
            DBIResultSet res = runSQLForResult("select distinct columnname,datatype,colid from T_DATABASE_COLUMN where userid='" + uid + "' and TID in\n"
                    + "(select tid from T_DATABASE_TABLE where tname='" + table + "') and isprimary=0\n"
                    + "order by colid");
            for (int i = 0; i < res.rowCount(); i++) {
                tables.addToRow(res.getRow(i + 1).get(0));
                if (Arrays.asList(numberType).contains((String) res.getRow(i + 1).get(1))) {
                    tables.addToRow("1");
                } else {
                    tables.addToRow("0");
                }
                tables.finishRow();
            }
        } catch (Exception e) {
            Debug.error(e);
        }
        return tables;
    }

    /**
     * 得到指定uid，数据库名的DatabaseHelper对象<br/>
     * 返回值：boolean，返回指定uid的DatabaseHelper对象
     */
    public DatabaseHelper getUserdbhelper(int uid, String database) {
        DBIResultSet result = runSQLForResult("select distinct a.userid,dbtype,host,username,b.PASSWORD,name from "
                + "T_DATABASE_INFO a, T_DATABASE_CERTIFICATION b where a.userid=b.userid and a.did=b.did"
                + " and a.userid=" + uid + " and NAME='" + database + "'");
        String dbtype = (String) result.getRow(1).get(1);
        String dbhost = (String) result.getRow(1).get(2);
        String username = (String) result.getRow(1).get(3);
        String password = (String) result.getRow(1).get(4);
        String dbname = (String) result.getRow(1).get(5);
        int idbtype = Integer.valueOf(dbtype);
        DatabaseConfig config = new DatabaseConfig(Integer.valueOf(dbtype),
                DatabaseConfig.DatabaseDriver.chooseDriver(idbtype),
                DatabaseConfig.JDBCHostPrefix.autoGenHost(idbtype, dbhost, dbname),
                 username, password);
        return new DatabaseHelper(config);
    }

    public static void main(String[] args) {

        DatabaseHelper helper = new DatabaseHelper(GlobeVar.VAR_DATABASE_CONFIG);
        helper.Connect();
        String[] tables = {"T_DATABASE_COLUMN", "T_DATABASE_TABLE", "T_DATABASE_INFO"};
        DBIResultSet ret = helper.runJoinSelect("columnname,datatype", tables, "T_DATABASE_COLUMN.tid=T_DATABASE_TABLE.tid "
                + "and T_DATABASE_INFO.did=T_DATABASE_COLUMN.DID "
                + "and tname='T_DATABASE_CERTIFICATION' and name='DatabaseInsights'");
        for (int i = 0; i < ret.rowCount(); i++) {
            Debug.log(ret.getRow(i + 1));
        }

    }
}
