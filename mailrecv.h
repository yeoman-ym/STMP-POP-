/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: SMTP通讯过程，邮件接收，存储；关键信息提取
 *********************************************************************/

#ifndef MAILRECV_H
#define MAILRECV_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "parsemail.h"
#include "base64.h"

/* ***************************************************************
 * Summary: 得到用户名
 * Parameters: sockfd文件描述符，验证表结构体
 * Calls: decode64() verusername()
 * Return: 接收成功返回0 失败返回-1
 * Others: 接收sockfd数据
 * ***************************************************************/
int getusername(int sockfd, struct table *p);            //SMTP

/* ***************************************************************
 * Summary: 获取用户密码
 * Parameters: sockfd文件描述符，验证表结构体
 * Calls: decode64() versuername()
 * Return: 接收成功返回0 失败返回-1
 * Others: 获取用户密码存入验证表中
 * ***************************************************************/
int getpassword(int sockfd, struct table *p);

/* ***************************************************************
 * Summary: 截取邮件发送者的地址
 * Parameters: sockfd文件描述符，邮件结构体
 * Calls:
 * Return: 接收成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int getFromAddress(int sockfd, struct mail *pmail);

/* ***************************************************************
 * Summary: 截取邮件接收者的地址
 * Parameters: sockfd文件描述符，邮件结构体
 * Calls:
 * Return: 接收成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int getToAddress(int sockfd, struct mail *pmail);

/* ***************************************************************
 * Summary: 截取邮件主体内容
 * Parameters: sockfd文件描述符，邮件结构体
 * Calls:
 * Return: 接收成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int getbody(int sockfd, struct mail *pmail);

/* ***************************************************************
 * Summary: 截取邮件附件内容
 * Parameters: sockfd文件描述符，邮件结构体
 * Calls:
 * Return: 接收成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int getslave (int sockfd, struct mail *pmail);

/* ***************************************************************
 * Summary: 获取用户名
 * Parameters: sockfd文件描述符，验证表结构体
 * Calls:
 * Return: 接收成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int getuser_pop(int sockfd, struct table *p);           //POP3

/* ***************************************************************
 * Summary: 获取用户密码
 * Parameters: sockfd文件描述符，验证表结构体
 * Calls:
 * Return: 接收成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int getpass_pop(int sockfd, struct table *p);

#endif

