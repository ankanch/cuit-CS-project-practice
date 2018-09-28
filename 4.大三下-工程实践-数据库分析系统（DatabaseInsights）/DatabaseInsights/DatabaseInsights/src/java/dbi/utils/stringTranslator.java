/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Apr 09 2018
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

import dbi.localization.lang;
import dbi.localization.langID;

/**
 *
 * @author kanch
 */
public class stringTranslator {

    private static lang localization = null;

    /*
    * convert user status to text based on status code
     */
    public static String translateUserStatusCode(lang local, int code) {
        switch (code) {
            case 1:
                return local.getString(langID.USER_STATUS_UNVERFIED);//"Unverfied";
            case 0:
                return local.getString(langID.USER_STATUS_NORMAL);//"Normal";
            case -1:
                return local.getString(langID.USER_STATUS_RESTRICTED);//"Restricted";
        }
        return local.getString(langID.USER_STATUS_UNKNOW);//"Unknow";
    }
    

    public static void main(String[] args) {
        lang l = null;
        l = GlobeVar.OBJ_LOCALIZATION_CHINESE;
        System.out.println("base lang point Chinese=" + l.getString(langID.USER_STATUS_NORMAL));
        l = GlobeVar.OBJ_LOCALIZATION_ENGLISH;
        System.out.println("base lang point English=" + l.getString(langID.USER_STATUS_NORMAL));
        //System.out.println(manager.validateUser("vicky", "123"));
    }
}
