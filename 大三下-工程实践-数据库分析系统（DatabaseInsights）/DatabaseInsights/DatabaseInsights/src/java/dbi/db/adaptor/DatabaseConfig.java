/*
 * The MIT License
 *
 * *** Copyright © ChengShiyi (Miss Zhang)
 * *** Code created on  三月 01 2018
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

/**
 *
 * @author Miss Zhang
 */
public class DatabaseConfig {

    private int database;
    private String driver;
    private String host;
    private String user;
    private String password;
    private String dbname;

    public DatabaseConfig(int database, String driver, String host, String user, String password) {
        this.driver = driver;
        this.host = host;
        this.user = user;
        this.password = password;
        this.database = database;
    }

    public String getDriver() {
        return driver;
    }

    public String getHost() {
        return host;
    }

    public String getUsername() {
        return user;
    }

    public String getPassword() {
        return password;
    }

    public int getDatabase() {
        return database;
    }

    public static class DatabaseCode {

        public static int DATABASE_ORACLE_12C = 1000;
        public static int DATABASE_MYSQL = 2000;
        public static int DATABASE_SQL_SERVER = 3000;

        public static boolean check(int dbcode) {
            int[] codelist = new int[]{1000, 2000, 3000};
            for (int i : codelist) {
                if (i == dbcode) {
                    return true;
                }
            }
            return false;
        }
    }

    public static class DatabaseDriver {

        public static String ORACLE_12C = "oracle.jdbc.driver.OracleDriver";
        public static String MYSQL = "org.gjt.mm.mysql.Driver";
        public static String SQLSERVER = "...";

        public static String chooseDriver(int dbcode) {
            if (dbcode == DatabaseCode.DATABASE_ORACLE_12C) {
                return ORACLE_12C;
            } else if (dbcode == DatabaseCode.DATABASE_MYSQL) {
                return MYSQL;
            } else if (dbcode == DatabaseCode.DATABASE_SQL_SERVER) {
                return SQLSERVER;
            }
            return ORACLE_12C;
        }
    }

    public static class JDBCHostPrefix {

        public static String ORACLE_THIN = "jdbc:oracle:thin:@//";
        public static String MYSQL = "jdbc:mysql://";

        public static String makeUpJDBCHost(String prefix, String host, String dbname) {
            return prefix + host + "/" + dbname;
        }

        public static String autoGenHost(int dbcode, String host, String dbname) {
            if (dbcode == DatabaseCode.DATABASE_ORACLE_12C) {
                return makeUpJDBCHost(ORACLE_THIN, host, dbname);
            } else if (dbcode == DatabaseCode.DATABASE_MYSQL) {
                return makeUpJDBCHost(MYSQL, host, dbname + "?useSSL=false");
            }
            return makeUpJDBCHost(ORACLE_THIN, host, dbname);
        }
    }

}
