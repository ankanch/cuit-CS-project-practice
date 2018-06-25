/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on May 24 2018
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

import java.util.Base64;

/**
 *
 * @author kanch
 */
public class DataValidation {

    public static boolean containsNULL(Object... objs) {
        for (Object obj : objs) {
            if (obj == null) {
                return true;
            }
        }
        return false;
    }

    public static String encodeToBase64(String s) {
        return Base64.getEncoder().encodeToString((s.getBytes()));
    }

    public static String decodeFromBase64(String s) {
        return new String(Base64.getDecoder().decode(s));
    }

    public static int findMin(DBIResultSet dbirs,int colnum) {
        int minint = Integer.MAX_VALUE;
        for (int i = 1; i <= dbirs.rowCount(); i++) {
            int v = Integer.parseInt(dbirs.getData(i, colnum, String.class));
            if (v < minint) {
                minint = v;
            }
        }
        return minint;
    }

    public static int findMax(DBIResultSet dbirs, int colnum) {
        int maxint = Integer.MIN_VALUE;
        for (int i = 1; i <= dbirs.rowCount(); i++) {
            int v = Integer.parseInt(dbirs.getData(i, colnum, String.class));
            if (v > maxint) {
                maxint = v;
            }
        }
        return maxint;
    }

    public static int getAverage(DBIResultSet dbirs, int colnum) {
        double sum = 0;
        for (int i = 1; i <= dbirs.rowCount(); i++) {
            sum += Integer.parseInt(dbirs.getData(i, colnum, String.class));
        }
        return (int)(sum/dbirs.rowCount());
    }

}
