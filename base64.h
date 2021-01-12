#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BASE64_PAD64 '='

/* ***************************************************************
 * Summary: SMTP协议通信、接收邮件
 * Parameters: socket套接字，邮件结构体指针
 * Calls: welcome_admin_menu(), welcome_stu_menu()
 * Return: 接收成功返回0 失败返回-1
 * Others: 通过SMTP建立Server与Client之间的连接，接收客户端的邮件。
 * ***************************************************************/
char* base64_encode(const char *data);
char* base64_decode(const char *bdata);

#endif
