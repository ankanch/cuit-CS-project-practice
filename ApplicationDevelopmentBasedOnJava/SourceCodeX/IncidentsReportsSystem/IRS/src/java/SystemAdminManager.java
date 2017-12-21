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
public class SystemAdminManager {
    
    //注册系统管理员
    //uname指定管理员用户名，upass指定管理员密码
    public Boolean registSysadmin(String uname, String upass){
        
        return true;
    }
    
    //修改系统管理员密码
    //aid指定管理员id，newpass指定新密码
    public Boolean alterPassword(String aid,String newpass){
        
        return true;
    }
    
    //检验系统管理员是否存在
    //uname指定用户名，upass指定密码
    public Boolean checkSysadmin(String uname,String upass){
        
        return true;
    }
    
    //删除系统管理员
    // uid指定系统管理员id
    public Boolean deleteSysadmin(String uid){
        
        return true;
    }
    
}
