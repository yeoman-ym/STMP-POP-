#ifndef NET_H
#define NET_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "base64.h"
#include "parsemail.h"
#include "mailrecv.h"

/* ***************************************************************
 * Summary: SMTP协议通信、接收邮件
 * Parameters: socket套接字，邮件结构体指针
 * Calls: welcome_admin_menu(), welcome_stu_menu()
 * Return: 接收成功返回0 失败返回-1
 * Others: 通过SMTP建立Server与Client之间的连接，接收客户端的邮件。
 * ***************************************************************/
int handleconnection(int sockfd, struct mail *pmail);                      //SMTP锁步
int pop3Connection(int cfd, struct subject_ctl *subject, mail_t *pmail);   //pop3锁步

#endif
