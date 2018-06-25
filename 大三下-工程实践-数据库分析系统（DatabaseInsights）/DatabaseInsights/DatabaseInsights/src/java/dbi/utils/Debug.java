/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Apr 12 2018
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

/**
 * Display debug messages in server log
 *
 * @author kanch
 */
public class Debug {

    private static String MSG_HEADER = "DBI|DEBUG|";

    /*
    * print a series string into the server logs
    * strings will be split by space
     */
    public static void log(String... msgs) {
        String callerClassName = new Exception().getStackTrace()[1].getClassName();
        String methordName = Thread.currentThread().getStackTrace()[2].getMethodName();
        System.out.print(MSG_HEADER + " LOG |@" + callerClassName + "::" + methordName + "|:::>>>");
        for (String s : msgs) {
            System.out.print(s);
            System.out.print(" ");
        }
        System.out.print("\n");
    }

    /*
    * print a series string into the server logs
    * strings will be split by space
     */
    public static void log(Object... msgs) {
        String callerClassName = new Exception().getStackTrace()[1].getClassName();
        String methordName = Thread.currentThread().getStackTrace()[2].getMethodName();
        System.out.print(MSG_HEADER + " LOG |@" + callerClassName + "::" + methordName + "|:::>>>");
        for (Object o : msgs) {
            System.out.print(String.valueOf(o));
            System.out.print(" ");
        }
        System.out.print("\n");
    }

    /*
    * print error message into the server logs
    * strings will be split by space
     */
    public static void error(String... msgs) {
        String callerClassName = new Exception().getStackTrace()[1].getClassName();
        String methordName = Thread.currentThread().getStackTrace()[2].getMethodName();
        System.out.print(MSG_HEADER + "ERROR|@" + callerClassName + "::" + methordName + "|:::>>>");
        for (String s : msgs) {
            System.out.print(s);
            System.out.print(" ");
        }
        System.out.print("\n");
    }

    /*
    * print error message into the server logs
    * strings will be split by space
     */
    public static void error(Object... msgs) {
        String callerClassName = new Exception().getStackTrace()[1].getClassName();
        String methordName = Thread.currentThread().getStackTrace()[2].getMethodName();
        System.out.print(MSG_HEADER + "ERROR|@" + callerClassName + "::" + methordName + "|:::>>>");
        for (Object o : msgs) {
            System.out.print(String.valueOf(o));
            System.out.print(" ");
        }
        System.out.print("\n");
    }

    public static void main(String... args) {
        Debug.log("this", "is", "a", "test", "message", "!");
        Debug.error("this", "is", "a", "test", "message", "!");
        Debug.log("this", 1212, "a", "test", "message", "!");
        Debug.error("this", 44.55, "a", "test", "message", "!");
    }

}
