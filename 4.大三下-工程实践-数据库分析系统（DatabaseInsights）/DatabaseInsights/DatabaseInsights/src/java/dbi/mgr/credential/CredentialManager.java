
/*
 * The MIT License
 *
 * *** Copyright © ChengShiyi (Miss Zhang)
 * *** Code created on  三月 11 2018
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
package dbi.mgr.credential;

import dbi.db.adaptor.DatabaseConfig;
import dbi.db.adaptor.DatabaseHelper;
import dbi.utils.DBIResultSet;
import dbi.utils.Debug;
import dbi.utils.GlobeVar;
import java.sql.Connection;
import java.sql.SQLException;

/**
 *
 * @author Miss Zhang
 */
public class CredentialManager {

    private Connection conn;
    private final DatabaseConfig dbconfig = GlobeVar.VAR_DATABASE_CONFIG;
    private final DatabaseHelper dbhelper = new DatabaseHelper(dbconfig);

    /**
     * 在数据库里添加凭证
     * 返回值：boolean，成功返回true，失败返回false
     */
    public Boolean addCredential(String dbhost, String dbname, String dbuser, String dbpawd, String userid, String dbtype) {
        if (dbhelper.Connect()) {
            try {
                int rv = (int) dbhelper.executeOracleFunction("F_CREATE_CREDENTIAL(?,?,?,?,?,?)", dbhost, dbname, dbuser, dbpawd, userid, dbtype);
                switch (rv) {
                    case 1:
                        Debug.log("成功创建credential");
                        break;
                    case -3:
                        Debug.log("未找到数据");
                        return false;
                    case -1:
                        Debug.log("创建失败");
                        break;
                    default:
                        break;
                }
            if(Integer.valueOf(dbtype)==DatabaseConfig.DatabaseCode.DATABASE_ORACLE_12C){
                dbhost=DatabaseConfig.JDBCHostPrefix.makeUpJDBCHost(DatabaseConfig.JDBCHostPrefix.ORACLE_THIN, dbhost, dbname);
            }
            if(Integer.valueOf(dbtype)==DatabaseConfig.DatabaseCode.DATABASE_MYSQL){
                dbhost=DatabaseConfig.JDBCHostPrefix.makeUpJDBCHost(DatabaseConfig.JDBCHostPrefix.MYSQL, dbhost, dbname);
            }
            String driver = "";
            if(Integer.valueOf(dbtype)==DatabaseConfig.DatabaseCode.DATABASE_MYSQL){
                driver = DatabaseConfig.DatabaseDriver.MYSQL;
            }else if(Integer.valueOf(dbtype)==DatabaseConfig.DatabaseCode.DATABASE_ORACLE_12C){
                driver = DatabaseConfig.DatabaseDriver.ORACLE_12C;
        }
            
            
            DatabaseConfig userdbconfig = new DatabaseConfig(Integer.valueOf(dbtype),driver, dbhost,dbuser, dbpawd);
            DatabaseHelper userdbhelper = new DatabaseHelper(userdbconfig);
            DBIResultSet column=null;            
            if(userdbhelper.Connect()){
                DBIResultSet usid=dbhelper.runSelect("userid", "T_DI_USER", "USESSION='"+userid+"'");
                DBIResultSet did = dbhelper.runSQLForResult("select did from T_DATABASE_INFO where name='"+dbname+"' and userid="+usid.getRow(1).get(0)); 
                DBIResultSet table = userdbhelper.getTables(dbname);
                Debug.log(did.getRow(1).get(0));
                int dids=Integer.valueOf((String)did.getRow(1).get(0));
                for(int i=0;i<table.getRow(1).size();i++){
                    dbhelper.runSQL("insert into T_DATABASE_TABLE(did,TNAME) values("+dids+",'"+table.getRow(1).get(i)+"')");
                }
                for(int i=0;i<table.getRow(1).size();i++){
                    userdbhelper.getAllColumnSpecies((String)table.getRow(1).get(i),Integer.valueOf(String.valueOf(usid.getRow(1).get(0))),
                            dids,dbhelper);
                }
                  DBIResultSet selectforeign=dbhelper.runSQLForResult("select columnname,colid from T_DATABASE_COLUMN where isforeignkey=1");
                  Debug.log(selectforeign.getRow(1));
                  System.out.println(selectforeign.rowCount());
                  System.out.println(selectforeign.getRow(2));
                  for(int jj=0;jj<selectforeign.rowCount();jj++){
                      DBIResultSet pri=dbhelper.runSQLForResult("select colid from T_DATABASE_COLUMN where isPrimary=1 and columnname='"
                              +selectforeign.getRow(jj+1).get(0)+"'");
                      Debug.log("pri.getRow(1).get(0):"+pri.getRow(1).get(0));
                      dbhelper.runSQL("update T_DATABASE_COLUMN set foreignkeyref="+
                              Integer.valueOf(String.valueOf(pri.getRow(1).get(0)))
                              +" where colid="+Integer.valueOf(String.valueOf(selectforeign.getRow(jj+1).get(1))));
                  }
            }
            } catch (Exception e) {
                Debug.error(e);
                return false;
            }
        }
        return true;
    }
    
  
    /**
     * 删除凭证
     * 返回值：boolean，成功返回true，失败返回false
     */
    public Boolean deleteCredential(String crdid) {
        if (dbhelper.Connect()) {
            try {
                Object rv = dbhelper.executeOracleFunction("F_DELETE_CREDENTIAL(?)", crdid);
                if ((int) rv == 1) {
                    Debug.log("成功删除凭证");
                } else if ((int) rv == -1) {
                    Debug.log("凭证不存在，无法删除");
                    return false;
                }
            } catch (SQLException e) {
                Debug.error(e);
                return false;
            }
        }
        return true;
    }

    /**
     * 在数据库里修改凭证
     * 返回值：boolean，成功返回true，失败返回false
     */
    public Boolean alterCredential(String crdid, String dbname, String dbhost, String password) {
        Debug.log("crdid=",crdid,"dbname:",dbname,"dbhost:",dbhost,"password:",password);
        if (dbhelper.Connect()) {
            try {
                Object rv = dbhelper.executeOracleFunction("F_ALTER_CREDENTIAL(?,?,?,?)", crdid, dbname, dbhost, password);
                if ((int) rv == 1) {
                    Debug.log("成功更改凭证");
                } else if ((int) rv == -1) {
                    Debug.log("凭证不存在，无法修改");
                    return false;
                }
            } catch (SQLException e) {
                Debug.error(e);
                return false;
            }
        }
        return true;
    }
    /**
     * 得到指定用户的凭证信息
     * 返回值：DBIResultSet，返回所有凭证信息
     */
    public DBIResultSet getCredential(String sid) {
        DBIResultSet result = null;
        String id = null;

        if (dbhelper.Connect()) {
            try {
                String table[]={"T_DATABASE_INFO,T_DATABASE_CERTIFICATION,T_DI_USER "};
                result = dbhelper.runJoinSelect("name,host,T_DATABASE_CERTIFICATION.password,cid,T_DATABASE_CERTIFICATION.username ",table ,
                        "T_DATABASE_INFO.did=T_DATABASE_CERTIFICATION.did and T_DI_USER.USERID=T_DATABASE_INFO.USERID and usession='" + sid + "'");
                Debug.log("credential result row count=",result.rowCount());
            } catch (Exception e) {
                Debug.error(e.getMessage());
            }
        }

        return result;
    }
    /**
     * 检验凭证
     * 返回值：boolean，成功返回true，失败返回false
     */
    public Boolean validiateCreditial(String dbscode, String dbhost, String dbname, String dbuser, String dbpwd, int dbcode) {
        Boolean status = false;
        //check wether the infomation provaided is correct
        if (DatabaseConfig.DatabaseCode.check(dbcode)) {
            DatabaseConfig dbc = new DatabaseConfig(dbcode, DatabaseConfig.DatabaseDriver.chooseDriver(dbcode),
                    DatabaseConfig.JDBCHostPrefix.autoGenHost(dbcode, dbhost, dbname),
                    dbuser, dbpwd);
            DatabaseHelper test = new DatabaseHelper(dbc);
            if (test.Connect()) {
                status = true;
            }
        }
        return status;
    }

    public static void main(String[] args) {
        CredentialManager a = new CredentialManager();
        Debug.log("validiateCreditial:",a.validiateCreditial(String.valueOf(DatabaseConfig.DatabaseCode.DATABASE_MYSQL),
                "cd.kcs.akakanch.com", "dbitest", "dbitest", "dbitest",DatabaseConfig.DatabaseCode.DATABASE_MYSQL));
        Boolean q = a.addCredential("cd.kcs.akakanch.com", "dbitest", "dbitest", "dbitest",
                "BCD0E71D46CB1F0C332886736DB63255", String.valueOf(DatabaseConfig.DatabaseCode.DATABASE_MYSQL));
        Debug.log("addCredential:",q);
        /*
        q= a.deleteCredential("11DAD71A91396AAEE1B8D19DE406FDBD");
        Debug.log("deleteCredential:",q);
        q= a.alterCredential("11DAD71A91396AAEE1B8D19DE406FDBD","change name","change host","change password");
        Debug.log("alterCredential:",q);
        DBIResultSet s=a.getCredential("11DAD71A91396AAEE1B8D19DE406FDBD");
        Debug.log("getCredential:",s.getRows());
        q=a.validiateCreditial("", "change host", "change name", "", "", 0);
        Debug.log("validiateCreditial:",q);
*/
    }

}
