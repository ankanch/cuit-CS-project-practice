/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.sql.DataSource;
import java.sql.*;
import java.util.*;
/**
 * 本类用于管理订阅用户
 * 对于数据表： Users
 * @author kanch
 */
public class SubscirableManager {
    
    //检查指定邮箱的用户是否已经注册
    // email，要检查的邮箱
    public Boolean checkEmail(String email){
        String myDriver = DatabaseConfig.driver;
        String myUrl = DatabaseConfig.host;
        try{
        	Class.forName(myDriver);
        	Connection conn = DriverManager.getConnection(myUrl, DatabaseConfig.user,DatabaseConfig.password);
        	Statement state = conn.createStatement();
        	String sql = "select * from USERS where UEMAIL ='"+email+"'";
        	ResultSet re = state.executeQuery(sql);
        	if(re.next()){
        		System.out.println("已经注册");
        	}
        	else{
        		System.out.println("还未注册");
        	}
        }
        catch(Exception e){
        	System.err.println("CheckEmail got an exception");
        	System.err.println(e.getMessage());
        }
        return true;
    }
    
    //用于向数据库增加新的订户
    // email指定用户邮箱，subscible自动订阅地点
    public Boolean registUser(String email,String subscrible){
        String myDriver = DatabaseConfig.driver;
        String myUrl = DatabaseConfig.host;
                try{
            Class.forName(myDriver);
            Connection conn = DriverManager.getConnection(myUrl, DatabaseConfig.user,DatabaseConfig.password);
           Statement statement = conn.createStatement();
            String sql = "SELECT * FROM USERS";
            ResultSet rs = statement.executeQuery(sql);
            
            PreparedStatement psql;
            psql = conn.prepareStatement("insert into USERS(UEMAIL,USTATUS,USUBSCRIABE) values(?,?,?)");
            psql.setString(1,email);
            psql.setInt(2,0);
            psql.setString(3,subscrible);
            psql.executeUpdate();
            psql.close();
            rs.close();
            conn.close();
        }
        catch(Exception e){
        	System.err.println("RegistUser got an exception");
        	System.err.println(e.getMessage());
        }
        return true;
    }
    
    //用户修改用户邮箱
    // uid指定要修改的用户， newMail指定更改后的邮箱
    public Boolean alterUserEmail(String uid,String newMail){     
        String myDriver = DatabaseConfig.driver;
        String myUrl = DatabaseConfig.host;
        int Inuid = Integer.parseInt(uid);
              try{
          	Class.forName(myDriver);
                Connection conn = DriverManager.getConnection(myUrl, DatabaseConfig.user,DatabaseConfig.password);
        	//Statement state = conn.createStatement();
                String sql = "update USERS set UEMAIL = ? where UID = ?"; 
                PreparedStatement psmt = conn.prepareStatement(sql);
                psmt.setString(1, newMail);
                psmt.setInt(2, Inuid);
        	psmt.execute();
        	conn.close();
        }
        catch(Exception e){
        	System.err.println("AlterUserEmail got an exception");
        	System.err.println(e.getMessage());
        }
        return true;
    }
    
    //用于从数据库删除一个用户
    // uid指定要删除用户的UID字段
    public Boolean removeUser(String uid){
        String myDriver = DatabaseConfig.driver;
        String myUrl = DatabaseConfig.host;
                try{
         	Class.forName(myDriver);
       Connection conn = DriverManager.getConnection(myUrl, DatabaseConfig.user,DatabaseConfig.password);
        	Statement state = conn.createStatement();
        	String sql = "delete from USERS where UID = uid";
        	state.executeUpdate(sql);
        }
        catch(Exception e){
        	System.err.println("RemoveUser got an exception");
        	System.err.println(e.getMessage());
        }
        return true;
    }
    
    public Boolean alterSubscrible(){
        //不忙写这一个
        return true;
    }
    
    
}
