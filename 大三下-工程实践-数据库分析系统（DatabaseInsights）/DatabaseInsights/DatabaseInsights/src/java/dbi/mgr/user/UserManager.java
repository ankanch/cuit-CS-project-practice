/*
 * The MIT License
 *
 * **** Copyright © Long Zhang(kanch).
 * **** Email: kanchisme@gmail.com
 * **** Code created on Feb 28 2018
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
package dbi.mgr.user;

import dbi.db.adaptor.DatabaseConfig;
import dbi.db.adaptor.DatabaseHelper;
import dbi.localization.lang;
import dbi.utils.DBIResultSet;
import dbi.utils.Debug;
import dbi.utils.GlobeVar;
import dbi.utils.stringTranslator;
import java.sql.Connection;
import java.sql.SQLException;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author kanch
 */
public class UserManager {

    private Connection conn;
    private final DatabaseConfig dbconfig = GlobeVar.VAR_DATABASE_CONFIG;
    private final DatabaseHelper dbhelper = new DatabaseHelper(dbconfig);

    /**
    * 当用户登陆后检验usersession是否正确<br/>
    * 返回值：boolean，正确为true，错误为false
     */
    public Boolean validateSession(String sid) {
        if (dbhelper.Connect()) {
            try {
                int ret = dbhelper.executeOracleFunction("F_VALIDATE_SESSION(?)", sid);
                if (ret == -1) {  // ret = -1 stands for didn't login yet
                    return false;
                }
            } catch (SQLException e) {
                Debug.error(e.getMessage());
                return false;
            }
        } else {
            return false;
        }
        return true;
    }

    /**
    * 检验给定用户的密码是否正确<br/>
    * 返回值：boolean，正确为true，错误为false
     */
    public Boolean checkPassword(String sid, String oldpass) {
        try {
            String condition = " USESSION=''{0}'' AND PASSWORD=''{1}''";
            if (dbhelper.Connect()) {
                DBIResultSet re = dbhelper.runSelect("USERID",
                        "T_DI_USER",
                        MessageFormat.format(condition, sid, oldpass));
                if (re.rowCount() > 0) {
                    return true;
                }
            }
            dbhelper.Disconnect();
        } catch (Exception e) {
            Debug.error(e.getMessage());
            return false;
        }
        return false;
    }

    /**
    * 登陆<br/>
    * 返回值：boolean，成功为true，失败为false
     */
    public Boolean loginInUser(String username, String password, String session_id) {
        if (dbhelper.Connect()) {
            try {
                int ret = dbhelper.executeOracleFunction("F_LOGIN_USER(?,?,?)", username, password, session_id);
                if (ret == -1) {  // ret = -1 stands for username isn't exists or password incorrect
                    return false;
                }
            } catch (SQLException e) {
                Debug.error(e.getMessage());
                return false;
            }
        } else {
            return false;
        }
        return true;
    }

    /**
    * 根据用户名，密码，邮件来注册用户<br/>
    * 返回值：boolean，成功为true，失败为false
     */
    public Boolean registerUser(String username, String password, String email) {
        if (dbhelper.Connect()) {
            try {
                int ret = dbhelper.executeOracleFunction("F_CREATE_USER(?,?,?)", username, password, email);
                if (ret == -1) {  // ret = -1 stands for user already exist
                    return false;
                }
            } catch (SQLException e) {
                Debug.error(e.getMessage());
                return false;
            }
        } else {
            return false;
        }
        return true;
    }

    /**
    * This function used to get user info, for render some part of console<br/>
    * 返回值HashMap，返回用户信息键值对
     */
    public HashMap<String, String> getUserInfo(lang local, String session) {
        HashMap<String, String> info = new HashMap<>();
        if (dbhelper.Connect()) {
            DBIResultSet rs = dbhelper.runSelect("USERID,USERNAME,STATUS,LASTLOGIN,EMAIL", "T_DI_USER", "USESSION='" + session + "'");
            ArrayList<Object> row = rs.getRow(1);
            info.put("USERID", (String) row.get(0));
            info.put("USERNAME", (String) row.get(1));
            Debug.log("(String) row.get(2) =", row.get(2));
            info.put("STATUS", stringTranslator.translateUserStatusCode(local, Integer.valueOf((String) row.get(2))));
            info.put("LASTLOGIN", (String) row.get(3));
            info.put("EMAIL", (String) row.get(4));
        }
        return info;
    }

    /**
    * sign out a user by clear current session id of the user.<br/>
    * 返回值：boolean，成功为true，失败为false
     */
    public Boolean signoutUser(String session) {
        try {
            if (dbhelper.Connect()) {
                if (dbhelper.runSQL("UPDATE T_DI_USER SET USESSION='' WHERE USESSION='" + session + "'")) {
                    return true;
                }
            }
        } catch (Exception e) {
            Debug.error(e.getMessage());
        }
        return false;
    }

    /**
    * sign out a user by clear current session id of the user.<br/>
    * 返回值：boolean，成功为true，失败为false
     */    
    public Boolean disableUser(int usession) {
        try {
            if (dbhelper.Connect()) {
                String condition = "USESSION='" + usession + "'";
                HashMap<String, Object> kvs = new HashMap<>();
                kvs.put("STATUS", -100);
                if (dbhelper.runUpdate("T_DI_USER", kvs, condition)) {
                    return true;
                }
            }
            dbhelper.Disconnect();
        } catch (Exception e) {
            Debug.error(e.getMessage());
        }
        return false;
    }

    /**
    * We only allow user to change his email and password<br/>
    * 返回值：boolean，成功为true，失败为false
     */
    public Boolean alterUser(String usession, HashMap<String, Object> changed_key_value) {
        String condition = " USESSION='" + usession + "'";
        try {
            if (dbhelper.Connect()) {
                if (dbhelper.runUpdate("T_DI_USER", changed_key_value, condition)) {
                    return true;
                }
            }
            dbhelper.Disconnect();
        } catch (Exception e) {
            Debug.error(e.getMessage());
        }
        return false;
    }
    /**
    * 根据指定usession返回该用户的全部数据库名称<br/>
    * 返回值：DBIResultSet，每一行是一个数据库名称
     */
    public final DBIResultSet getUserDatabases(String usession) {
        DBIResultSet re = new DBIResultSet();
        try {
            String condition = "T_DATABASE_INFO.userid=T_DI_USER.userid and usession=''{0}''";
            if (dbhelper.Connect()) {
                String table[] = {"T_DATABASE_INFO", "T_DI_USER"};
                re = dbhelper.runJoinSelect("NAME",
                        table,
                        MessageFormat.format(condition, usession));
            }
            dbhelper.Disconnect();
        } catch (Exception e) {
            Debug.error(e.getMessage());
        }
        return re;
    }
    /**
    * 查找指定用户指定数据库的全部表名<br/>
    * 返回值：DBIResultSet，每一行是一个表名
     */
    public final DBIResultSet getUserTables(String usession, String database) {
        DBIResultSet re = new DBIResultSet();
        try {
            String condition = "T_DATABASE_TABLE.DID=T_DATABASE_INFO.DID and T_DI_USER.USERID=T_DATABASE_INFO.USERID\n"
                    + "and usession=''{0}'' and name=''{1}''";
            if (dbhelper.Connect()) {
                String table[] = {"T_DATABASE_TABLE", "T_DI_USER", "T_DATABASE_INFO"};
                re = dbhelper.runJoinSelect("tname",
                        table,
                        MessageFormat.format(condition, usession, database));
            }
            dbhelper.Disconnect();
        } catch (Exception e) {
            Debug.error(e.getMessage());
        }
        return re;
    }
    
    /**
    * 根据指定usession返回该用户的全部数据库的host<br/>
    * 返回值：DBIResultSet，每一行是一个数据库host
     */
    public final DBIResultSet getUserDatabasehost(String usession) {
        DBIResultSet re = new DBIResultSet();
        try {
            String condition = "T_DATABASE_INFO.userid=T_DI_USER.userid and usession=''{0}''";
            if (dbhelper.Connect()) {
                String table[] = {"T_DATABASE_INFO", "T_DI_USER"};
                re = dbhelper.runJoinSelect("host",
                        table,
                        MessageFormat.format(condition, usession));
            }
            dbhelper.Disconnect();
        } catch (Exception e) {
            Debug.error(e.getMessage());
        }
        return re;
    }
    /**
     * get user id (UID) by session id. 
     * if session is invalid, return -1
     */
    public final int getUIDbySessionID(String usession) {
        try {
            String condition = "USESSION=''{0}''";
            if (dbhelper.Connect()) {
                DBIResultSet re = dbhelper.runSelect("USERID","T_DI_USER",MessageFormat.format(condition,usession));
                dbhelper.Disconnect();
                if(re.rowCount() > 0){
                    return  Integer.valueOf((String)re.getRow(1).get(0));
                }
            }
        } catch (Exception e) {
            Debug.error(e.getMessage());
        }
        return -1;
    }

    public static void main(String[] args) {
        UserManager manager = new UserManager();
        DBIResultSet result=manager.getUserDatabases("30975E7ADB577CD3CD051823729AED26");
        Debug.log("getUserDatabases:",result.getRows());
        result=manager.getUserTables("30975E7ADB577CD3CD051823729AED26","DatabaseInsights");
        Debug.log("getUserTables:",result.getRows());
        Boolean b=manager.validateSession("30975E7ADB577CD3CD051823729AED26");
        Debug.log("validateSession:",b);
        b=manager.checkPassword("30975E7ADB577CD3CD051823729AED26", "123");
        Debug.log("checkPassword:",b);
        //b=manager.loginInUser("TEST_P", "TEST_P", "30975E7ADB577CD3CD051823729AED26");
        Debug.log("loginInUser:",b);
        
        Debug.log("getUserTables=",manager.getUserTables("5FF53CD720E945128945DE815D6E2047", "DatabaseInsights"));
    }

}
