/*
 * The MIT License
 *
 * *** Copyright © ChengShiyi (Miss Zhang)
 * *** Code created on  三月 04 2018
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
public class MySQLAdaptor extends DatabaseAdaptor {

    public String sql_getTypeName(String type) {
        switch(type){
            case "NUMBER":
                return "int";
            case "TEXT":
                return "text";
            default:
                return "";
        }
    }

    /**
     * 得到某种数据库的数字的全部类型<br/>
     * 返回值：String[]，返回带有全部类型字符串的字符数组
     */
    public String[] numberType() {
        return new String[]{};
    }

    /**
     * 返回根据指定的表名得到该表的全部列名的sql语句<br/>
     * 返回值：String，返回根据指定的表名得到该表的全部列名的sql语句
     */
    public String getColumnNamesByTable(String Table) {
        return "select column_name from information_schema.columns  where table_name='" + Table + "';";
    }

    /**
     * 返回根据指定的若干个表名得到所有表的全部列名的sql语句<br/>
     * 返回值：String，返回根据指定的若干个表名得到所有表的全部列名的sql语句
     */
    public String getColumnNames(String[] Tables) {
        return "select column_name from information_schema.columns  where table_name in ('" + String.join("','", Tables) + "');";
    }

    /**
     * 返回数据库的全部表的列表的sql语句<br/>
     * 返回值：String，返回数据库的全部表的列表的sql语句
     */
    public String getTableList() {
        return "show tables";
    }

    /**
     * 返回指定表的所有列的全部性质的sql语句<br/>
     * 返回值：String，返回指定表的所有列的全部性质的sql语句
     */
    public String getColumnSpecies(String Table) {
        return "SHOW COLUMNS FROM " + Table;
    }

    /**
     * 返回指定表的指定列的全部性质的sql语句<br/>
     * 返回值：String，返回指定表的所有列的全部性质的sql语句
     */
    public String getColumnSpeciesByName(String Column, String table) {
        return "SELECT *  "
                + "FROM information_schema.columns "
                + " WHERE column_name  =  '" + Column + "' and table_name = '" + table + "'";
    }

    /**
     * 返回一个查询的sql语句<br/>
     * 返回值：String，返回一个查询的sql语句
     */
    public String generateSelect(String querys, String table, String condition) {
        String sql = "select " + querys + " from " + table + " where " + condition;
        if (condition == "") {
            sql = "select " + querys + " from " + table;
        }
        return sql;
    }

    /**
     * 返回查找主键的sql语句<br/>
     * 返回值：String，返回查找主键的sql语句
     */
    public String findPrimaryKey(String table) {
        return "SELECT COLUMN_NAME "
                + "FROM INFORMATION_SCHEMA.COLUMNS "
                + "WHERE table_name =  '" + table + "' "
                + "AND COLUMN_KEY =  'PRI'";
    }

    /**
     * 返回查找外键的sql语句<br/>
     * 返回值：String，返回查找外键的sql语句
     */
    public String findForeignKey(String table) {
        return "select REFERENCED_COLUMN_NAME refColumn ,REFERENCED_TABLE_NAME refTable from INFORMATION_SCHEMA.KEY_COLUMN_USAGE  where TABLE_NAME='" + table + "'";
    }

    /**
     * 返回查找外键的sql语句<br/>
     * 返回值：String，返回查找外键的sql语句
     */
    public String findTablecolspe(String table) {
        return "select table_name,column_name,data_type from information_schema.columns  where table_name='" + table + "'";
    }

    /**
     * 根据数据库名返回数据库id<br/>
     * 返回值：String，返回根据数据库名返回数据库id的sql语句
     */
    public String findDid(String dbname) {
        String str = "select did from T_DATABASE_INFO where name='" + dbname + "'";
        return str;
    }

    /**
     * 根据列名返回引用列的id<br/>
     * 返回值：String，返回根据列名返回引用列的id的sql语句
     */
    public String findRefid(String columnname) {
        String str = "select colid from T_DATABASE_COLUMN "
                + "where columnname='" + columnname + "' and isPrimary=1";
        return "";
    }
}
