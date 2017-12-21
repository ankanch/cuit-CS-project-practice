/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *本文件记录个各种图标文件的路径地址
 * 为了方便，同时使用下面的字符串来定义事件类型
 *
 * @author kanch
 */
public class IconStrings {

    public static String icon_car_stolen = "/IncidentsReport/static/icons/car_stolen";
    public static String icon_fire = "/IncidentsReport/static/icons/fire";
    public static String icon_kidnapping = "/IncidentsReport/static/icons/kidnapping";
    public static String icon_lie = "/IncidentsReport/static/icons/lie";
    public static String icon_robbery = "/IncidentsReport/static/icons/robbery";
    public static String icon_stolen = "/IncidentsReport/static/icons/stolen";
    public static String icon_violence = "/IncidentsReport/static/icons/violence";

    public static String decideType(String tstr) {
        switch (tstr) {
            case "汽车偷窃":
                return "/IncidentsReport/static/icons/car_stolen";
            case "火灾":
                return "/IncidentsReport/static/icons/fire";
            case "绑架":
                return "/IncidentsReport/static/icons/kidnapping";
            case "欺诈":
                return "/IncidentsReport/static/icons/lie";
            case "抢劫":
                return "/IncidentsReport/static/icons/robbery";
            case "入室盗窃":
                return "/IncidentsReport/static/icons/stolen";
            case "暴力事件":
                return "/IncidentsReport/static/icons/violence";
        }
        return tstr;
    }

}
