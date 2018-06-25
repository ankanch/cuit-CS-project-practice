/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Apr 19 2018
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

import java.util.ArrayList;

/**
 * Class for Data Exchange between frontend and backend Data will be transfered
 * to a 2D Table with status and a message,followed by data. Format:
 * Status,message,data(if applicable)
 *
 * @author kanch
 */
public class DBIDataExchange {

    private static final String SP_STATUS = "<@SUS>";
    private static final String SP_MESSAGE = "<@MSG>";
    private static final String SP_COLUMN = "<@C>";
    private static final String SP_ROW = "<@R>";

    public DBIDataExchange() {
    }

    public static String makeupStatusCode(boolean status) {
        String result = String.valueOf(status) + SP_STATUS + "no message" + SP_MESSAGE + "no data";
        return result;
    }

    public static String makeupStatusCode(boolean status, String message) {
        String result = String.valueOf(status) + SP_STATUS + message + SP_MESSAGE + "no data";
        return result;
    }

    public static String makeupReturnData(boolean status, String message, Object data) {
        String result = String.valueOf(status) + SP_STATUS + message + SP_MESSAGE;
        result += String.valueOf(data);
        return result;
    }

    public static String makeupReturnData(boolean status, String message, Object[] data) {
        String result = String.valueOf(status) + SP_STATUS + message + SP_MESSAGE;
        for (Object obj : data) {
            result += String.valueOf(obj) + SP_COLUMN;
        }
        return result;
    }

    public static String makeupReturnData(boolean status, String message, Object[][] data) {
        String result = String.valueOf(status) + SP_STATUS + message + SP_MESSAGE;
        for (Object[] objlist : data) {
            String row = "";
            for (Object obj : objlist) {
                row += String.valueOf(obj) + SP_COLUMN;
            }
            result += row + SP_ROW;
        }
        return result;
    }

    public static String makeupReturnData(boolean status, String message, ArrayList<ArrayList<Object>> data) {
        String result = String.valueOf(status) + SP_STATUS + message + SP_MESSAGE;
        for (ArrayList<Object> objlist : data) {
            String row = "";
            for (Object obj : objlist) {
                row += String.valueOf(obj) + SP_COLUMN;
            }
            result += row + SP_ROW;
        }
        return result;
    }

    public static String makeupInternalExchangeData(ArrayList<ArrayList<Object>> data) {
        String result = "";
        result = data.stream().map((objlist) -> {
            String row = "";
            row = objlist.stream().map((obj) -> String.valueOf(obj) + SP_COLUMN).reduce(row, String::concat);
            return row;
        }).map((row) -> row + SP_ROW).reduce(result, String::concat);
        return result;
    }

    public static DBIResultSet parse(String data) {
        DBIResultSet ret = new DBIResultSet();
        String[] dat = data.split(SP_MESSAGE);
        String[] rows;
        if (dat.length > 1) {
            rows = dat[1].split(SP_ROW);
        } else {
            rows = dat[0].split(SP_ROW);
        }
        for (String row : rows) {
            String[] cols = row.split(SP_COLUMN);
            ret.addRow(cols);
        }
        return ret;
    }

    public static void main(String[] args) {
        String[] a = {"test1", "test2", "test3"};
        String[][] c = {{"test1", "text11"}, {"test2", "text22"}, {"test3", "text33"}};
        ArrayList<ArrayList<Object>> b = new ArrayList<>();
        ArrayList<Object> b1 = new ArrayList<>();
        b1.add("1");
        ArrayList<Object> b2 = new ArrayList<>();
        b2.add("2");
        b.add(b1);
        b.add(b2);
        Debug.log("Arraylist b=", b);
        String xa = DBIDataExchange.makeupReturnData(true, "this is a test message", a);
        String xb = DBIDataExchange.makeupReturnData(true, "this is a test message", c);
        String xc = DBIDataExchange.makeupReturnData(true, "this is a test message", b);
        Debug.log(xa);
        Debug.log(xb);
        Debug.log(xc);
    }

}
