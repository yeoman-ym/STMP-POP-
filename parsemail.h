#ifndef PARSEMAIL_H
#define PARSEMAIL_H

#include "common.h"
#include "base64.h"
#include <stdio.h>
#include <string.h>

/* ***************************************************************
 * Summary: SMTP协议通信、接收邮件
 * Parameters: socket套接字，邮件结构体指针
 * Calls: welcome_admin_menu(), welcome_stu_menu()
 * Return: 接收成功返回0 失败返回-1
 * Others: 通过SMTP建立Server与Client之间的连接，接收客户端的邮件。
 * ***************************************************************/
int verusername(const char * username, struct table *usertable);
int verpassword(const char * password, struct table *usertable);
int parsemail(struct mail * pmail, struct subject_ctl *subject);

#endif
