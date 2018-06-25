/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch) , ChengShiyi (Miss Zhang) 
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
package dbi.utils;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author Miss Zhang
 */
public class DBIResultSet {

    private ArrayList<ArrayList<Object>> rs;
    private ArrayList<Object> srow = new ArrayList<>();

    public DBIResultSet() {
        rs = new ArrayList<>();
    }

    public DBIResultSet(ArrayList<Object> row) {
        rs = new ArrayList<>();
        rs.add(row);
    }

    /*
    * Convert ResultSet to DBIResultSet
     */
    public DBIResultSet(ResultSet rs) {
        this.rs = new ArrayList<>();
        try {
            while (rs.next()) {
                for (int i = 0; i < rs.getMetaData().getColumnCount(); i++) {
                    addToRow(rs.getString(i + 1));
                }
                finishRow();
            }
        } catch (SQLException e) {
            Debug.error(e.getMessage());
        }
    }

    /**
     * add current row to result set to makeup new result set.
     */
    public final void addRow(ArrayList<Object> row) {
        rs.add(row);
    }

    public final void addRow(Object[] row) {
        rs.add(new ArrayList<>(Arrays.asList(row)));
    }

    public Object setValue(int row, int col, Object val) {
        ArrayList<Object> orgrow = rs.get(row - 1);
        orgrow.set(col - 1, val);
        rs.set(row - 1, orgrow);
        return val;
    }

    /**
     * add current data to one temporery row
     */
    public final void addToRow(Object data) {
        srow.add(data);
    }

    /**
     * finish the row created by addToRow function. then add it to the table rs
     */
    public final ArrayList<Object> finishRow() {
        ArrayList<Object> newrow = new ArrayList<>(srow);
        rs.add(newrow);
        srow.clear();
        return newrow;
    }

    /*
    * get designed row by row number which row must no less than 1
     */
    public final ArrayList<Object> getRow(int i) {
        assert (i > 0);
        return rs.get(i - 1);
    }

    /**
     * get data at row x, col y. x,y both start from 1. NOT 0;
     */
    public final Object getData(int row, int col) {
        return rs.get(row - 1).get(col - 1);
    }

    public final <T> T getData(int row, int col, Class<T> cname) {
        Object obj = getData(row, col);
        return cname.cast(obj);
    }

    // get all rows of current DBIResultSet
    public final ArrayList<ArrayList<Object>> getRows() {
        return rs;
    }

    /**
     * parse DBIResultSet to ArrayList<Object>, only works when DBIResultSet is
     * n*1 or 1*n
     */
    public ArrayList<Object> toArray1D() {
        ArrayList<Object> arr = new ArrayList<Object>();
        if (rowCount() == 1) {
            for (Object obj : rs.get(0)) {
                arr.add(obj);
            }
        } else if (colCount() == 1) {
            for (ArrayList<Object> obj : rs) {
                arr.add(obj.get(0));
            }
        }
        return arr;
    }

    /**
     * parse DBIResultSet to ArrayList<Object>, only works when DBIResultSet is
     * n*1 or 1*n
     */
    public <T> ArrayList<T> toArray1D(Class<T> cname) {
        ArrayList<T> arr = new ArrayList<>();
        if (rowCount() == 1) {
            for (Object objo : rs.get(0)) {
                arr.add((cname.cast(objo)));
            }
        } else if (colCount() == 1) {
            for (ArrayList<Object> objo : rs) {
                arr.add(cname.cast(objo.get(0)));
            }
        }
        return arr;
    }

    /**
     * return row count
     */
    public final int rowCount() {
        return rs.size();
    }

    /**
     * return column count per row. if no rows,return 0.
     */
    public final int colCount() {
        if (rs.size() > 0) {
            return rs.get(0).size();
        }
        return 0;
    }

    @Override
    public String toString() {
        String ret = rs.size() + "x";
        if (rs.size() > 0) {
            ret += rs.get(0).size() + " ";
        } else {
            ret += "0 ";
        }
        return "DBIResultSet[ " + ret + "table]{data= " + rs + " }";
    }

    //public final DBIResultSet map(func)
    public static void main(String[] args) {
        DBIResultSet b = new DBIResultSet();
        b.addToRow(1);
        b.addToRow(2);
        b.finishRow();
        b.addToRow(2);
        b.addToRow(4);
        b.finishRow();
        b.addToRow(1);
        b.addToRow(8);
        b.finishRow();
        Debug.log("b=", b);
        Debug.log("b.getData(1,1)=", b.getData(1, 1));
    }
}
