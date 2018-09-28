/*
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 04 2018
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
package dbi.mgr.report;

import java.text.MessageFormat;
import java.util.ArrayList;

/**
 *
 * @author kanch
 */
public class ReportBean {

    public ReportBean() {
    }

    public String generateReportTable(ArrayList<Report> replist) {
        String ret = "<table class=\"table table-striped\" id=\"report_table\"> "
                + "                <thead>               "
                + "                    <tr>                     "
                + "                        <th scope=\"col\">#</th>           "
                + "                        <th scope=\"col\">TITLE</th>       "
                + "                        <th scope=\"col\">DATE</th>                  "
                + "                        <th scope=\"col\">DESCRIPTION</th>                 "
                + "                        <th scope=\"col\">RELATION</th>                    "
                + "                        <th scope=\"col\">Operations</th>               "
                + "                    </tr>               "
                + "                </thead>           "
                + "                <tbody>                     "
                + "                    @DATA"
                + "                </tbody>            "
                + "            </table>";

        String rowtemp = "<tr id=\"rep_{5}\">   "
                + "                        <th scope=\"row\" style=\"vertical-align: inherit;\">{0}</th>     "
                + "                        <td style=\"vertical-align: inherit;padding: 0rem;\">      "
                + "                            {1}               "
                + "                        </td>                        "
                + "                        <td style=\"vertical-align: inherit;padding: 0rem;\">                            "
                + "                            {2}            "
                + "                        </td>                        <td style=\"vertical-align: inherit;padding: 0rem;\">                    "
                + "                            {3}                "
                + "                        </td>                      "
                + "                        <td style=\"vertical-align: inherit;padding: 0rem;\">                            "
                + "                            {4}"
                + "                        </td>                       "
                + "                        <td>   "
                + "                            <button type=\"button\" class=\"btn btn-primary\" onclick=\"inspect({0})\">DETAILS</button>                      "
                + "                            <button type=\"button\" class=\"btn btn-info\" onclick=\"view({0})\">View</button>                         "
                + "                            <button type=\"button\" class=\"btn btn-danger\" onclick=\"del({5},true)\">Delete</button>                      "
                + "                             <input type=\"text\" class=\"report-id\" value=\"{5}\" style=\"display:none\">"
                + "                             <input type=\"text\" class=\"report-relations\" value=\"{6}\" style=\"display:none\">"
                + "                             <input type=\"text\" class=\"report-fulldes\" value=\"{7}\" style=\"display:none\">"
                + "                             <input type=\"text\" class=\"report-fulltitle\" value=\"{8}\" style=\"display:none\">"
                + "                        </td>                   "
                + "                    </tr>";
        String rows = "";

        for (Report rep : replist) {
            rows += MessageFormat.format(rowtemp, replist.indexOf(rep) + 1,
                    terminated(rep.title, 10),
                    rep.generatedate,
                    terminated(rep.des, 20),
                    transReportRelations(rep.relations),
                    rep.id,
                    rep.relations,
                    rep.des,
                    rep.title);
        }

        return ret.replace("@DATA", rows);
    }

    public String transReportRelations(String relations) {
        if(relations == null){
            return "None";
        }
        if (relations.split(";").length > 1) {
            return "Multiple";
        }
        return "Single";
    }

    public String terminated(String s, int len) {
        if (s.length() >= len) {
            return s.substring(0, len);
        }
        return s;
    }
}
