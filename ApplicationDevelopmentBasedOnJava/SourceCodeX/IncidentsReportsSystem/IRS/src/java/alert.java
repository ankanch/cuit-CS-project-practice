/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kanch
 */
import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

public class alert {

    //服务器地址
    public static final String HOST = "smtp.163.com";
    //协议
    public static final String PROTOCOL = "smtp";
    //端口
    public static final int PORT = 25;
    //邮箱帐号
    public static final String FROM = "kanchpybot@163.com";
    //填写自己的授权码
    public static final String PWD = "XYZ2017python";
    //发送人昵称,这个自定义
    public static final String nick = "Incidents Report 事件警报通知";

    /**
     * 获取Session邮件
     *
     * @return session
     */
    private static Session getSession() {
        Properties props = new Properties();
        props.put("mail.smtp.host", HOST);//设置服务器地址
        props.put("mail.store.protocol", PROTOCOL);//设置协议
        props.put("mail.smtp.port", PORT);//设置端口
        props.put("mail.smtp.auth", "true");

        Authenticator authenticator = new Authenticator() {
            @Override
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication(FROM, PWD);
            }

        };
        Session session = Session.getDefaultInstance(props, authenticator);
        return session;
    }

    /**
     * 发送信息至邮箱
     *
     * @param title	邮箱标题
     * @param toEmail	接收邮箱
     * @param content	邮件内容
     * @throws AddressException
     * @throws MessagingException
     */
    public static void send(String title, String toEmail, String content) throws AddressException, MessagingException {
        Session session = getSession();
        Message msg = new MimeMessage(session);
        //设置发送内容
        msg.setFrom(new InternetAddress(nick + "<" + FROM + ">"));
        InternetAddress[] address = {new InternetAddress(toEmail)};
        msg.setRecipients(Message.RecipientType.TO, address);
        msg.setSubject(title);
        msg.setSentDate(new Date());
        msg.setContent(content, "text/html;charset=utf-8");
        //发送信息
        Transport.send(msg);
    }

}
