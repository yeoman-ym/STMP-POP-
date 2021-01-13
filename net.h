/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 建立网络连接的套接字
 *********************************************************************/

#ifndef NET_H
#define NET_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "base64.h"
#include "parsemail.h"
#include "mailrecv.h"
#include "devicecontrol.h"
#include "devicereponse.h"

/* ***************************************************************
 * Summary: 回复邮件
 * Parameters: 套接字socket,
 * Calls:
 * Return: 成功返回0 失败返回-1
 * Others: SMTP锁步
 * ***************************************************************/
int handleconnection(int sockfd, struct mail *pmail);

/* ***************************************************************
 * Summary: 回复邮件1封
 * Parameters: 套接字socket,验证表结构体
 * Calls: getuser_pop() getpass_pop() verusername() verpassword() updatecurrtime()
 * Return: 成功返回0 失败返回-1
 * Others: 由于smtp server有处理动作， 监听到共享内存的标志值为1，回复邮件——POP3锁步
 * ***************************************************************/
int pop3Connection(int cfd, struct subject_ctl *subject, mail_t *pmail);

#endif
