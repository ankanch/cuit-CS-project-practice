/*
 * The MIT License
 *
 * *** Copyright © ChengShiyi (Miss Zhang)
 * *** Code created on  四月 09 2018
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
package dbi.mgr.credential;

import dbi.localization.lang;
import dbi.localization.langID;
import dbi.utils.DBIResultSet;
import dbi.utils.GlobeVar;
import java.text.MessageFormat;

/**
 *
 * @author Miss Zhang
 */
public class CredentialBean {

    private String sessionID = null;
    private DBIResultSet re = null;
    private lang local = null;

    public CredentialBean() {
    }

    public void setSessionID(String sessionID) {
        this.sessionID = sessionID;
    }

    public void setLang(String langcode) {
        this.local = lang.detectLang(langcode);
    }

    public String getDBcount() {
        re = GlobeVar.OBJ_MANAGER_CREDENTIAL.getCredential(sessionID);
        return String.valueOf(re.rowCount());
    }

    public String getCertifications() {
        String table_content = "<table class=\"table table-striped\">"
                + "                <thead>"
                + "                    <tr>"
                + "                        <th scope=\"col\">#</th>"
                + "                        <th scope=\"col\">{0}</th>"
                + "                        <th scope=\"col\">{1}</th>"
                + "                        <th scope=\"col\">{2}</th>"
                + "                        <th scope=\"col\">{3}</th>"
                + "                        <th scope=\"col\">{4}</th>"
                + "                    </tr>"
                + "                </thead>"
                + "                <tbody>                    "
                + "                    @ROWDATA"
                + "                </tbody>"
                + "            </table>";
        table_content = MessageFormat.format(table_content, local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_DBNAME),
                local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_HOST),
                local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_ACCOUNT),
                local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_PASSWORD),
                local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_OPERATIONS));

        String no_data = "<div class=\"alert alert-warning alert-dismissible fade show\" role=\"alert\" id=\"alert_no_credentials\">"
                + "                @MESSAGE"
                + "                <button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">"
                + "                    <span aria-hidden=\"true\">×</span>"
                + "                </button>"
                + "            </div>";
        no_data = no_data.replace("@MESSAGE", local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TIP_NO_DATA));

        String rowtemp = "<tr id=\"credtable_row_{0}\">"
                + "                        <th scope=\"row\" style=\"vertical-align: inherit;\">{1}</th>"
                + "                        <td style=\"vertical-align: inherit;padding: 0rem;\">"
                + "                            <input id=\"credtable_row_{0}_col_1\" class=\"console-table-input\" value=\"{2}\" type=\"text\" name=\"dbname\" disabled=\"disabled\">"
                + "                        </td>"
                + "                        <td style=\"vertical-align: inherit;padding: 0rem;\">"
                + "                            <input id=\"credtable_row_{0}_col_2\" class=\"console-table-input\"  value=\"{3}\" type=\"text\" name=\"dbhost\"  disabled=\"disabled\">"
                + "                        </td>"
                + "                        <td style=\"vertical-align: inherit;padding: 0rem;\">"
                + "                            <input id=\"credtable_row_{0}_col_3\" class=\"console-table-input\"  value=\"{4}\" type=\"text\" name=\"dbaccount\" disabled=\"disabled\">"
                + "                        </td>"
                + "                        <td style=\"vertical-align: inherit;padding: 0rem;\">"
                + "                            <input id=\"credtable_row_{0}_col_4\" class=\"console-table-input\"  value=\"{5}\" type=\"password\" name=\"dbpassword\" disabled=\"disabled\">"
                + "                        </td>"
                + "                        <td>"
                + "                            <button id=\"credtable_row_{0}_edit\" type=\"button\" class=\"btn btn-secondary\" onclick=\"edit({0})\">@EDIT</button>"
                + "                            <button id=\"credtable_row_{0}_save\" type=\"button\" class=\"btn btn-success\" onclick=\"save({0})\" style=\"display: none;\">@SAVE</button>"
                + "                            <button type=\"button\" class=\"btn btn-danger\" onclick=\"del({0})\">@DELETE</button>"
                + "                        </td>"
                + "                   </tr>";
        rowtemp = rowtemp.replace("@EDIT", local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_OPERATION_EDIT))
                .replace("@SAVE", local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_OPERATION_SAVE))
                .replace("@DELETE", local.getString(langID.JSP_CONSOLE_CREDENTIAL_MGR_TABLE_OPERATION_DELETE));

        if (re.rowCount() > 0) {
            String certifications = "";
            for (int i = 1; i <= re.rowCount(); i++) {
                certifications += MessageFormat.format(rowtemp, re.getRow(i).get(3), i, re.getRow(i).get(0), re.getRow(i).get(1),re.getRow(i).get(4) , re.getRow(i).get(2));
            }
            return table_content.replace("@ROWDATA", certifications);
        }
        return no_data;
    }

}
