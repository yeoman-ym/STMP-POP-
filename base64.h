/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-11
 Description: 源字符串解码和编码——base64方式
 *********************************************************************/

#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BASE64_PAD64 '='

/* ***************************************************************
 * Summary: base64编码
 * Parameters: 字符串
 * Calls: malloc()
 * Return: 编码后的字符串
 * Others:
 * ***************************************************************/
char* base64_encode(const char *data);

/* ***************************************************************
 * Summary: base64解码
 * Parameters: 字符串
 * Calls: malloc()
 * Return: 解码后的字符串
 * Others:
 * ***************************************************************/
char* base64_decode(const char *bdata);

#endif
