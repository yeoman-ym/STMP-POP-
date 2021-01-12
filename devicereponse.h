#ifndef DEVICEREPONSE_H
#define DEVICEREPONSE_H

/* ***************************************************************
 * Summary: SMTP协议通信、接收邮件
 * Parameters: socket套接字，邮件结构体指针
 * Calls: welcome_admin_menu(), welcome_stu_menu()
 * Return: 接收成功返回0 失败返回-1
 * Others: 通过SMTP建立Server与Client之间的连接，接收客户端的邮件。
 * ***************************************************************/
int sendemail(int cfd, const struct mail *pmail, const struct subject_ctl *subject);
//读取zhangsan_0.mail邮件文件的内容,发送到套接字

#endif
