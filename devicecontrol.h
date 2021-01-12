#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

/* ***************************************************************
 * Summary: SMTP协议通信、接收邮件
 * Parameters: socket套接字，邮件结构体指针
 * Calls: welcome_admin_menu(), welcome_stu_menu()
 * Return: 接收成功返回0 失败返回-1
 * Others: 通过SMTP建立Server与Client之间的连接，接收客户端的邮件。
 * ***************************************************************/
int subjectcontrol(const struct mail *pmail, struct subject_ctl *subject);
int emitupdate(const struct mail *pmail, struct subject_ctl *subject);
int emitcommand(struct subject_ctl *subject);
char *getcreatmailname(const char *username, char *mailname);
char *getsendmailname(const char *username, char *mailname);
int createmail(const struct mail *pmail, struct subject_ctl *subject);
char* getcurrtime();

#endif
