/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * 本类用于管理订阅用户
 * 对于数据表： Users
 * @author kanch
 */
public class SubscirableManager {
    
    //检查指定邮箱的用户是否已经注册
    // email，要检查的邮箱
    public Boolean checkEmail(String email){
        
        return true;
    }
    
    //用于向数据库增加新的订户
    // email指定用户邮箱，subscible自动订阅地点
    public Boolean registUser(String email,String subscrible){
        
        return true;
    }
    
    //用户修改用户邮箱
    // uid指定要修改的用户， newMail指定更改后的邮箱
    public Boolean alterUserEmail(String uid,String newMail){
      
        return true;
    }
    
    //用于从数据库删除一个用户
    // uid指定要删除用户的UID字段
    public Boolean removeUser(String uid){
        
        return true;
    }
    
    public Boolean alterSubscrible(){
        //不忙写这一个
        return true;
    }
    
    
}
