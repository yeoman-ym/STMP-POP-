/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-11
 Description: 初始化邮件体参数，套接字生成，进程建立，各模块按顺序调用
 *********************************************************************/
#include "daemon.h"

//服务器做成守护进程

int main()
{
    data_t data = {};
    bzero(&data, sizeof(data));
    strcpy(data.ip, "192.168.2.151");    //服务器IP地址
    data.port = 10000;                   //服务器端口

    create_daemon(".", 0600, &data, create_tcpserver);
    return 0;
}
