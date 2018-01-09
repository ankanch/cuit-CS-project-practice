/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

/**
 *用于管理二级管理员
 * 对应数据库表：L2ADMIN
 * @author kanch
 */
public class L2AdminManager {
    
    /**
     * 获取指定登录名的二级管理员的ID(String)
     * @param uname 二级管理员登录名
     * @return  二级管理员ID
     */
    public int getL2AdminID(String uname){
        int l2AdminID = 0;
         try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
          
            String selectSql = "SELECT L2ID FROM L2ADMIN WHERE L2USERNAME = ?";
            PreparedStatement preparedStmt = conn.prepareStatement(selectSql);
            preparedStmt.setString(1, uname);
            ResultSet rs = preparedStmt.executeQuery();            
            
            while(rs.next()){
                l2AdminID = rs.getInt(1);
            }
            
            preparedStmt.close();
            //关闭数据库连接
            conn.close();		
	}catch(Exception e){
            System.err.println(e.getMessage().toString());
        }       
         return l2AdminID;
    }
    
    //注册二级管理员
    //uname指定管理员用户名，upass指定管理员密码
    public boolean registL2admin(String uname, String upass){
        boolean insertResult = false;
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            
            //不存在该二级管理员 
            if(false == checkL2adminByName(uname))
            {
                String insertSql = "INSERT INTO L2ADMIN(L2USERNAME, L2PASSWORD, L2STATUS) VALUES(?, ?, ?)";
                PreparedStatement preparedStmt = conn.prepareStatement(insertSql);
                preparedStmt.setString(1, uname);
                preparedStmt.setString(2, upass);
                preparedStmt.setInt(3, 1);
                preparedStmt.execute(); //执行插入二级管理员用户
                preparedStmt.close();
                insertResult = true;
            }
            else    //该二级管理员已存在
            {
                System.out.println("ERROR : the user has already existed");
            }
            
            //关闭数据库连接
            conn.close();		
	}catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        return insertResult;
    }
    
    //修改二级管理员密码
    //aid指定管理员id，newpass指定新密码
    public boolean alterPassword(String aid,String newpass){
        boolean alterResult = false;
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            
            //该二级管理员不存在
            if(false == checkL2adminByID(Integer.parseInt(aid)))
            {
                System.out.println("ERROR : the user does not exist");
            }
            else{
                String updateSql = "UPDATE L2ADMIN SET L2PASSWORD = ? WHERE L2ID = ?";
                PreparedStatement preparedStmt = conn.prepareStatement(updateSql);
                preparedStmt.setString(1, newpass);
                preparedStmt.setInt(2, Integer.parseInt(aid));
                //执行更新
                preparedStmt.executeUpdate();
                alterResult = true;
                //关闭连接
                preparedStmt.close();
            }
            //关闭数据库连接
            conn.close();
        }catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        return alterResult;
    }
    
    //检验二级管理员是否存在
    //uname指定用户名
    public boolean checkL2adminByName(String uname){
        boolean checkResult = false;
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            // 创建数据库语句
            String query = "SELECT COUNT(*) FROM L2ADMIN WHERE L2USERNAME = '" + uname  + "'";
            // 创建对应Java Statement
            Statement st = conn.createStatement();
            // 执行数据库语句
            ResultSet rs = st.executeQuery(query);
            //结果集数量
            int count = 0;
            while (rs.next()) { 
                count = rs.getInt(1); 
            }
            //二级管理员用户已经存在
            if(0 != count)
            {
                checkResult = true;
            }           
            st.close();
            conn.close();
        }catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        return checkResult;
    }
    
    /**
     * 判断登录名 密码是否正确
     * @param uname 登录名
     * @param upassword 密码
     * @return 
     */
    public boolean checkL2Admin(String uname, String upassword){
        boolean checkResult = false;
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            // 创建数据库语句
            String query = "SELECT COUNT(*) FROM L2ADMIN WHERE L2USERNAME = '" + uname  + "' AND L2PASSWORD = '" + upassword + "'";
            // 创建对应Java Statement
            Statement st = conn.createStatement();
            // 执行数据库语句
            ResultSet rs = st.executeQuery(query);
            //结果集数量
            int count = 0;
            while (rs.next()) { 
                count = rs.getInt(1); 
            }
            //二级管理员用户已经存在
            if(0 != count)
            {
                checkResult = true;
            }           
            st.close();
            conn.close();
        }catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        
        return checkResult;
    }
    
    //检验二级管理员是否存在
    //uname指定用户名
    public boolean checkL2adminByID(int uid){
        boolean checkResult = false;
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            // 创建数据库语句
            String query = "SELECT COUNT(*) FROM L2ADMIN WHERE L2ID = " + uid;
            // 创建对应Java Statement
            Statement st = conn.createStatement();
            // 执行数据库语句
            ResultSet rs = st.executeQuery(query);
            //结果集数量
            int count = 0;
            while (rs.next()) { 
                count = rs.getInt(1); 
            }
            //二级管理员用户已经存在
            if(0 != count)
            {
                checkResult = true;
            }           
            st.close();
            conn.close();
        }catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        return checkResult;
    }
    
    //禁用二级管理员
    //uid指定要禁用的二级管理员id
    public boolean suspendL2admin(String uid){
        boolean suspendResult = false;
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            
            //该二级管理员不存在
            if(false == checkL2adminByID(Integer.parseInt(uid)))
            {
                System.out.println("ERROR : the user does not exist");
            }
            else{
                String updateSql = "UPDATE L2ADMIN SET L2STATUS = ? WHERE L2ID = ?";
                PreparedStatement preparedStmt = conn.prepareStatement(updateSql);
                preparedStmt.setInt(1, 0);
                preparedStmt.setInt(2, Integer.parseInt(uid));
                //执行更新
                preparedStmt.executeUpdate();
                suspendResult = true;
                //关闭连接
                preparedStmt.close();
            }
            //关闭数据库连接
            conn.close();
        }catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        return suspendResult;
    }
    
    //删除二级管理员
    // uid指定二级管理员id
    public boolean deleteL2admin(String uid){
        boolean deleteResult = false;
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            
            //该二级管理员不存在
            if(false == checkL2adminByID(Integer.parseInt(uid)))
            {
                System.out.println("ERROR : the user does not exist");
            }
            else{
                String updateSql = "DELETE FROM L2ADMIN WHERE L2ID = ?";
                PreparedStatement preparedStmt = conn.prepareStatement(updateSql);
                preparedStmt.setInt(1, Integer.parseInt(uid));
                //执行更新
                preparedStmt.executeUpdate();
                deleteResult = true;
                //关闭连接
                preparedStmt.close();
            }
            //关闭数据库连接
            conn.close();
        }catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        return deleteResult;
    }
    
    
    public ArrayList<L2admin> getL2Admins(){
        ArrayList<L2admin> l2admins = new ArrayList<>();
        try{
            // 创建数据库连接
            Class.forName(DatabaseConfig.driver);
            Connection conn = DriverManager.getConnection(DatabaseConfig.host, DatabaseConfig.user,DatabaseConfig.password);
            String query = "SELECT * FROM L2ADMIN";
            // 创建对应Java Statement
            Statement st = conn.createStatement();
            // 执行数据库语句
            ResultSet rs = st.executeQuery(query);
            while(rs.next()){
                L2admin l2admin = new L2admin();
                l2admin.id = rs.getInt(1);
                l2admin.name = rs.getString(2);
                l2admin.password = rs.getString(3);
                l2admin.status = rs.getInt(4);
                
                l2admins.add(l2admin);
            }
            st.close();
            //关闭数据库连接
            conn.close();
        }catch(Exception e){
            System.err.println(e.getMessage().toString());
        }
        
        return l2admins;
    }
    
}
