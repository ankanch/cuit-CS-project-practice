/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *用于管理二级管理员
 * 对应数据库表：L2ADMIN
 * @author kanch
 */
public class L2AdminManager {
    
    //注册二级管理员
    //uname指定管理员用户名，upass指定管理员密码
    public Boolean registL2admin(String uname, String upass){
        
        return true;
    }
    
    //修改二级管理员密码
    //aid指定管理员id，newpass指定新密码
    public Boolean alterPassword(String aid,String newpass){
        
        return true;
    }
    
    //检验二级管理员是否存在
    //uname指定用户名，upass指定密码
    public Boolean checkL2admin(String uname,String upass){
        
        return true;
    }
    
    //禁用二级管理员
    //uid指定要禁用的二级管理员id
    public Boolean suspendL2admin(String uid){
        
        return true;
    }
    
    //删除二级管理员
    // uid指定二级管理员id
    public Boolean deleteL2admin(String uid){
        
        return true;
    }
    
}
