#ifndef PARSEMAIL_H
#define PARSEMAIL_H

#include "common.h"
#include "base64.h"
#include <stdio.h>
#include <string.h>

/* ***************************************************************
 * Summary:
 * Parameters:
 * Calls:
 * Return:
 * Others:
 * ***************************************************************/
int verusername(const char * username, struct table *usertable);
int verpassword(const char * password, struct table *usertable);

/* ***************************************************************
 * Summary: 解析邮件主题字
 * Parameters: pmail邮件结构体，subject 控制结构体
 * Calls:
 * Return: 成功返回0 失败返回-1
 * Others: 解析邮件的主题字放置到到结构体subject中
 * ***************************************************************/
int parsemail(struct mail * pmail, struct subject_ctl *subject);

#endif
