/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 设备控制结果，邮件响应——POP3通讯过程
 *********************************************************************/

#ifndef DEVICEREPONSE_H
#define DEVICEREPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* ***************************************************************
 * Summary: 发送回复邮件
 * Parameters:
 * Calls:
 * Return:
 * Others:
 * ***************************************************************/
int sendemail(int sockfd, const char *mailname);

/* ***************************************************************
 * Summary: 获得当前时间
 * Parameters: void
 * Calls:
 * Return: 成功返回字符串形式的时间 失败返回NULL
 * Others:
 * ***************************************************************/
char* getcurrtime();

#endif
