/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Mar 06 2018
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

import dbi.db.adaptor.DatabaseConfig;
import dbi.localization.langChinese;
import dbi.localization.langEnglish;
import dbi.mgr.credential.CredentialManager;
import dbi.mgr.report.ReportManager;
import dbi.mgr.user.UserManager;

/**
 *
 * @author kanch
 */
public class GlobeVar {

    // globe status code 
    public static String SERVLET_IDENTIFIER_ERROR = "!@ERR!";
    public static String SERVLET_IDENTIFIER_SUCCESS = "!@SUCC!";

    // globe database configures
    public static String CONFIG_DATABASE_HOST = "FILL YOUR OWN DATA HERE" ; 
    public static String CONFIG_DATABASE_USER = "FILL YOUR OWN DATA HERE" ; 
    public static String CONFIG_DATABASE_PASSWORD = "FILL YOUR OWN DATA HERE" ; 
    public static String CONFIG_EMAIL_SENDGRID_APIKEY = "FILL YOUR OWN DATA HERE" ; 
    public static String CONFIG_DATABASE_DRIVER = DatabaseConfig.DatabaseDriver.ORACLE_12C;
    public static final DatabaseConfig VAR_DATABASE_CONFIG = new DatabaseConfig(DatabaseConfig.DatabaseCode.DATABASE_ORACLE_12C,
            GlobeVar.CONFIG_DATABASE_DRIVER, GlobeVar.CONFIG_DATABASE_HOST, GlobeVar.CONFIG_DATABASE_USER, GlobeVar.CONFIG_DATABASE_PASSWORD);

    // globe manager object
    public static UserManager OBJ_MANAGER_USER = new UserManager();
    public static CredentialManager OBJ_MANAGER_CREDENTIAL = new CredentialManager();
    public static ReportManager OBJ_MANAGER_REPORT = new ReportManager();

    //localization objs
    public static langChinese OBJ_LOCALIZATION_CHINESE = new langChinese();
    public static langEnglish OBJ_LOCALIZATION_ENGLISH = new langEnglish();

}
