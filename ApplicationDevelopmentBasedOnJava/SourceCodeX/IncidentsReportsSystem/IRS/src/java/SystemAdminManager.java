/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *用户管理系统管理员
 * 对应数据表：SYSADMIN
 * @author kanch
 */
import java.sql.*;
import java.util.ArrayList;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.sql.DataSource;
public class SystemAdminManager {
    String myDriver = DatabaseConfig.driver;
    String myUrl = DatabaseConfig.host;
    String myUser = DatabaseConfig.user;
    String myPassword = DatabaseConfig.password;

    //注册系统管理员
    //uname指定管理员用户名，upass指定管理员密码
    public Boolean registSysadmin(String uname, String upass){
        try{
            Class.forName(myDriver);
            Connection conn = DriverManager.getConnection(myUrl, myUser, myPassword);
            Statement statement = conn.createStatement();
            String sql = "SELECT * FROM SYSADMIN";
            ResultSet rs = statement.executeQuery(sql);
            
            PreparedStatement psql;
            psql = conn.prepareStatement("insert into SYSADMIN(AUSERNAME,APASSWORD,ASTATUS) values(?,?,?)");
            psql.setString(1,uname);
            psql.setString(2,upass);
            psql.setInt(3,0);
            psql.executeUpdate();
            psql.close();
            rs.close();
            conn.close();
        }catch(Exception e){
            System.err.println("error!");
            System.err.println(e.getMessage());
            return false;
        }
        System.out.println("注册成功！！");
        return true;
    }
    
    //修改系统管理员密码
    //aid指定管理员id，newpass指定新密码
    public Boolean alterPassword(String aid,String newpass){
        try{
            Class.forName(myDriver);
            Connection conn = DriverManager.getConnection(myUrl, myUser, myPassword);
            Statement statement = conn.createStatement();
            String sql = "SELECT * FROM SYSADMIN";
            ResultSet rs = statement.executeQuery(sql);
            
            PreparedStatement psql;
            psql = conn.prepareStatement("update SYSADMIN set APASSWORD = ? where AID = ?");
            psql.setString(1,newpass);
            psql.setString(2,aid);
            psql.executeUpdate();
            psql.close();
            rs.close();
            conn.close();
        }catch(Exception e){
            System.err.println("error!");
            System.err.println(e.getMessage());
            return false;
        }
        System.out.println("修改成功！！");
        return true;
    }
    
    //检验系统管理员是否存在
    //uname指定用户名，upass指定密码
    public Boolean checkSysadmin(String uname,String upass){
        try{
            Class.forName(myDriver);
            Connection conn = DriverManager.getConnection(myUrl, myUser, myPassword);
            Statement statement = conn.createStatement();
            String sql = "SELECT * FROM SYSADMIN where AUSERNAME = '"+uname+"' and APASSWORD = '"+upass+"'";
            ResultSet rs = statement.executeQuery(sql);
            
            while(rs.next()){
                    System.out.println("存在此用户！！");
                    System.out.println(rs.getString("AUSERNAME")+rs.getString("APASSWORD"));
                    return true;
            }
            rs.close();
            conn.close();
        }catch(Exception e){
            System.err.println("error!");
            System.err.println(e.getMessage());
        }
        System.out.println("不存在此用户！！");
        return false;
    }
    
    //删除系统管理员
    // uid指定系统管理员id
    public Boolean deleteSysadmin(String uid){
        try{
            Class.forName(myDriver);
            Connection conn = DriverManager.getConnection(myUrl, myUser, myPassword);
            Statement statement = conn.createStatement();
            String sql = "SELECT * FROM SYSADMIN";
            ResultSet rs = statement.executeQuery(sql);
            
            PreparedStatement psql;
            psql = conn.prepareStatement("delete from SYSADMIN where AID = ?");
            psql.setString(1,uid);
            psql.executeUpdate();
            psql.close();
            rs.close();
            conn.close();
        }catch(Exception e){
            System.err.println("error!");
            System.err.println(e.getMessage());
            return false;
        }
        System.out.println("删除成功！！");
        return true;
    }
    
}
