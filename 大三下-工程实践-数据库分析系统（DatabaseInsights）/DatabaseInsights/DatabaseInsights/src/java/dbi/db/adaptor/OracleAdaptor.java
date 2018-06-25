
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
public class OracleAdaptor extends DatabaseAdaptor {

    public String sql_getTypeName(String type) {
        switch (type) {
            case "NUMBER":
                return "NUMBER";
            case "TEXT":
                return "TEXT";
            default:
                return "";
        }
    }

    /**
     * 得到某种数据库的数字的全部类型<br/>
     * 返回值：String[]，返回带有全部类型字符串的字符数组
     */
    public String[] numberType() {
        String num[] = {"NUMBER", "BINARY_FLOAT", "BINARY_DOUBLE"};
        return num;
    }

    /**
     * 返回根据指定的表名得到该表的全部列名的sql语句<br/>
     * 返回值：String，返回根据指定的表名得到该表的全部列名的sql语句
     */
    public String getColumnNamesByTable(String TableName) {
        return "select column_name "
                + "from all_tab_columns  "
                + "where table_name = '" + TableName + "'";
    }

    /**
     * 返回根据指定的若干个表名得到所有表的全部列名的sql语句<br/>
     * 返回值：String，返回根据指定的若干个表名得到所有表的全部列名的sql语句
     */
    public String getColumnNames(String[] Tables) {
        return "select column_name from all_tab_columns where table_name in ('" + String.join("','", Tables) + "')";
    }

    /**
     * 返回数据库的全部表的列表的sql语句<br/>
     * 返回值：String，返回数据库的全部表的列表的sql语句
     */
    public String getTableList() {
        return "select table_name from user_tables";
    }

    /**
     * 返回指定表的所有列的全部性质的sql语句<br/>
     * 返回值：String，返回指定表的所有列的全部性质的sql语句
     */
    public String getColumnSpecies(String Table) {
        return "SELECT * FROM user_tab_columns WHERE TABLE_NAME='" + Table + "'";
    }

    /**
     * 返回指定表的指定列的全部性质的sql语句<br/>
     * 返回值：String，返回指定表的所有列的全部性质的sql语句
     */
    public String getColumnSpeciesByName(String Column, String table) {
        return "SELECT *  "
                + "FROM all_tab_columns "
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
        String findPrimaryKey = "select  column_name "
                + "from user_constraints con,user_cons_columns col "
                + "where\n"
                + "con.constraint_name=col.constraint_name and con.constraint_type='P' "
                + "and col.table_name='" + table + "'";
        return findPrimaryKey;
    }

    /**
     * 返回查找外键的sql语句<br/>
     * 返回值：String，返回查找外键的sql语句
     */
    public String findForeignKey(String table) {
        String findForeignKey = "select b.column_name refColumn "
                + "from user_constraints a "
                + "left  join user_cons_columns b on a.constraint_name = b.constraint_name "
                + "left  join user_cons_columns c on a.r_constraint_name = c.constraint_name "
                + "where a.constraint_type = 'R' and a.table_name = '" + table + "' ";
        return findForeignKey;
    }

    /**
     * 返回查找外键的sql语句<br/>
     * 返回值：String，返回查找外键的sql语句
     */
    public String findTablecolspe(String table) {
        return "select  c.TABLE_NAME,c.COLUMN_NAME,t.DATA_TYPE "
                + "from user_tab_columns  t,user_col_comments  c "
                + " where t.table_name = c.table_name"
                + " and t.column_name = c.column_name and t.table_name = '" + table + "'";
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
        return str;
    }
}
