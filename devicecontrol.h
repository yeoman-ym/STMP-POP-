#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <stdio.h>
#include <string.h>
#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* ***************************************************************
 * Summary: 主题字控制
 * Parameters: 邮件结构体 subject_ctl结构体
 * Calls: emitcommand() emitupdate()
 * Return: 成功返回0 失败返回-1
 * Others:
 * ***************************************************************/
int subjectcontrol(const struct mail *pmail, struct subject_ctl *subject);
int emitupdate(const struct mail *pmail, struct subject_ctl *subject);
int emitcommand(struct subject_ctl *subject);
char *getcreatmailname(const char *username, char *mailname);
char *getsendmailname(const char *username, char *mailname);
int createmail(const struct mail *pmail, struct subject_ctl *subject);
char* getcurrtime();

#endif
