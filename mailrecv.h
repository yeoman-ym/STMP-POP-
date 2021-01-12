#ifndef MAILRECV_H
#define MAILRECV_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "parsemail.h"
#include "base64.h"

/* ***************************************************************
 * Summary: SMTP协议通信、接收邮件
 * Parameters: socket套接字，邮件结构体指针
 * Calls: welcome_admin_menu(), welcome_stu_menu()
 * Return: 接收成功返回0 失败返回-1
 * Others: 通过SMTP建立Server与Client之间的连接，接收客户端的邮件。
 * ***************************************************************/
int getusername(int sockfd, struct table *p);            //SMTP
int getpassword(int sockfd, struct table *p);
int getFromAddress(int sockfd, struct mail *pmail);
int getToAddress(int sockfd, struct mail *pmail);
int getbody(int sockfd, struct mail *pmail);
int getslave (int sockfd, struct mail *pmail);

int getuser_pop(int sockfd, struct table *p);           //POP3
int getpass_pop(int sockfd, struct table *p);

#endif

