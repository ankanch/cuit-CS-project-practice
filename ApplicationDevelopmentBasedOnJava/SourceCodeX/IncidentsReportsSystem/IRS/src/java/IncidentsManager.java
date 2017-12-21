/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.sql.DataSource;

/**
 * 事件管理类， 该类用于获取事件，删除事件，隐藏事件，给事件进行可信度标记等
 *
 * @author kanch
 */
public class IncidentsManager {
    
    String myDriver = DatabaseConfig.driver;
    String myUrl = DatabaseConfig.host;

    //获取指定位置的sum条事件
    public ArrayList<Incident> getIncidents(String latlng, String sum) {
        ArrayList<Incident> al = new ArrayList();
        String[] ll = latlng.replace(" ", "").split(",");
        //
        double lat = Double.parseDouble(ll[0]);
        double lng = Double.parseDouble(ll[1]);
        double minLat = lat - 0.2;
        double maxLat = lat + 0.2;
        double minLng = lng - 0.2;
        double maxLng = lng + 0.2;
        
        System.out.println(ll[0] + "," + ll[1]);
        try {
            // 创建数据库连接
            Class.forName(myDriver);
            Connection conn = DriverManager.getConnection(myUrl, DatabaseConfig.user, DatabaseConfig.password);
            // 创建数据库语句
            String query = "SELECT * FROM INCIDENTS WHERE ( LAT> " + Double.toString(minLat)
                    + " AND LAT< " + Double.toString(maxLat)
                    + " ) AND ( LNG> " + Double.toString(minLng)
                    + " AND LNG< " + Double.toString(maxLng)
                    + " ) LIMIT 0," + sum;
            System.out.println(query);
            // 创建对应Java Statement
            Statement st = conn.createStatement();
            // 执行数据库语句
            ResultSet rs = st.executeQuery(query);
            // 遍历获取结果
            while (rs.next()) {
                Incident ii = new Incident();
                ii.id = rs.getInt("IID");
                ii.credit = rs.getString("ICREDIT");
                ii.description = rs.getString("IDESCRIPTION");
                ii.latlng = Double.toString(rs.getDouble("LAT")) + ", " + Double.toString(rs.getDouble("LNG")) ;
                ii.type = rs.getString("ITYPE");
                ii.reportTime = rs.getString("IREPORTTIME");
                ii.reportedby = rs.getInt("IWHOADD");
                ii.printInfo();
                al.add(ii);
            }
            st.close();
        } catch (Exception e) {
            System.err.println("错误：无法从数据库中读取数据，可能是网络问题或者驱动问题。");
            System.err.println(e.getMessage());
        }
        return al;
    }
    
    public Boolean addIncident(Incident ii) {
        try {
            // 创建数据库连接
            Class.forName(myDriver);
            Connection conn = DriverManager.getConnection(myUrl, DatabaseConfig.user, DatabaseConfig.password);
            // 创建数据库语句并填充
            String query = "INSERT INTO INCIDENTS(ITYPE, IREPORTTIME, IDESCRIPTION, LAT,LNG, IWHOADD,ICREDIT,ILOCATION,IPRECISELOCATION)"
                    + " values (?, ?, ?, ?, ?, ?,'1','no location','N/A')";
            PreparedStatement preparedStmt = conn.prepareStatement(query);
            preparedStmt.setString(1, ii.type);
            preparedStmt.setString(2, ii.reportTime);
            preparedStmt.setString(3, ii.description);
            String[] latlng = ii.latlng.replace(" ", "").split(",");
            double lat = Double.parseDouble(latlng[0]);
            double lng = Double.parseDouble(latlng[1]);
            preparedStmt.setDouble(4, lat);
            preparedStmt.setDouble(5, lng);
            preparedStmt.setInt(6, ii.reportedby);
            // 执行数据库语句
            preparedStmt.execute();
            conn.close();
        } catch (Exception e) {
            System.err.println("错误：事件插入数据库失败！ 事件经纬度：" + ii.latlng);
            System.err.println(e.getMessage());
            return false;
        }
        return true;
    }
    
}
