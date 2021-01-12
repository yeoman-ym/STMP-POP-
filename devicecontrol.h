/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 设备控制及验证文件的更新
 *********************************************************************/

#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <stdio.h>
#include <string.h>
#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static char subject_data[128] = "";

/* ***************************************************************
 * Summary: 主题字控制
 * Parameters: 邮件结构体 subject_ctl结构体
 * Calls: emitcommand() emitupdate()
 * Return: 成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int subjectcontrol(const struct mail *pmail, struct subject_ctl *subject);

/* ***************************************************************
 * Summary: 更新程序控制
 * Parameters: 邮件结构体 subject_ctl结构体
 * Calls:
 * Return: 成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int emitupdate(const struct mail *pmail, struct subject_ctl *subject);

/* ***************************************************************
 * Summary: 命令字控制
 * Parameters: subject_ctl结构体
 * Calls:
 * Return: 成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int emitcommand(const struct mail *pmail, struct subject_ctl *subject);

/* ***************************************************************
 * Summary: 获取创建的邮件名
 * Parameters:
 * Calls:
 * Return: 成功返回创建好的邮件名 失败返回NULL
 * Others: 根据控制结果组装邮件要保存的文件 规则：zhangsan_0.mail
 * ***************************************************************/
char *getcreatmailname(const char *username, char *mailname);

/* ***************************************************************
 * Summary: 发送邮件
 * Parameters:
 * Calls:
 * Return: 成功返回 失败返回
 * Others: pop3流程中，发送控制结果邮件，先获得文件名，最后要删除
 * ***************************************************************/
char *getsendmailname(const char *username, char *mailname);

/* ***************************************************************
 * Summary: 组装邮件
 * Parameters:
 * Calls:
 * Return: 成功返回 失败返回
 * Others: 根据控制结果组装邮件按照mail.doc文件格式。strcat(),sprintf()
 * ***************************************************************/
int createmail(const struct mail *pmail, const char *mailname);

#endif
