/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kanch
 */
public class Incident {

    //事件属性定义
    public int id = 0;
    public String type = "";
    public String reportTime = "";
    public String credit = "";
    public String description = "";
    public int reportedby = 1;
    public String roughLocation = "";
    public String latlng = "";

    public void printInfo() {
        System.out.format("%d, %s, %s, %d\n", id, description, credit, reportedby);
    }

}
