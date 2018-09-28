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
package dbi.localization;

import dbi.utils.GlobeVar;
import javax.servlet.http.HttpServletRequest;

/** <h3>Base Language Pack</h3>
 * This class is used for localization There are two type of string here, one
 * for debug, the other for user interface
 *
 * @author kanch
 */
public class lang {

    /*
    * function to get localization language by ID
     */
    public String getString(final int id) {
        return "Please Call From Subclass";
    }

    /*
    * This function can detect user local then return corresponding localization language obj
    * from GlobeVar
     */
    public static lang detectLang(HttpServletRequest request) {
        String local = request.getLocale().toString();
        if (local.equals("en_US")) {
            return GlobeVar.OBJ_LOCALIZATION_ENGLISH;
        } else if (local.equals("zh_CN")) {
            return GlobeVar.OBJ_LOCALIZATION_CHINESE;
        }
        return null;
    }

    /*
    * This function can detect user local then return corresponding localization language obj
    * from GlobeVar
     */
    public static lang detectLang(String langcode) {
        if (langcode.equals("en_US")) {
            return GlobeVar.OBJ_LOCALIZATION_ENGLISH;
        } else if (langcode.equals("zh_CN")) {
            return GlobeVar.OBJ_LOCALIZATION_CHINESE;
        }
        return null;
    }
}
