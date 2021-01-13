/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 邮件解析——字符串搜索并提取
 *********************************************************************/

#ifndef PARSEMAIL_H
#define PARSEMAIL_H

#include "common.h"
#include "base64.h"
#include <stdio.h>
#include <string.h>

/* ***************************************************************
 * Summary: 验证用户名
 * Parameters: 输入用户名参数，验证表结构体
 * Calls:
 * Return: 成功返回0 失败返回-1
 * Others: 将username和结构体的记录做对比，成功就是验证通过
 * ***************************************************************/
int verusername(const char *username, struct table *usertable);

/* ***************************************************************
 * Summary: 验证密码
 * Parameters: 输入密码参数，验证表结构体
 * Calls:
 * Return: 成功返回0 失败返回-1
 * Others: 将password和结构体的记录做对比，成功就是验证通过
 * ***************************************************************/
int verpassword(const char *password, struct table *usertable);

/* ***************************************************************
 * Summary: 解析邮件主题字
 * Parameters: pmail邮件结构体，subject 控制结构体
 * Calls:
 * Return: 成功返回0 失败返回-1
 * Others: 解析邮件的主题字放置到到结构体subject中
 * ***************************************************************/
int parsemail(struct mail *pmail, struct subject_ctl *subject);

#endif
