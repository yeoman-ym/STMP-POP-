/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-11
 Description: 初始化邮件体参数，套接字生成，进程建立，各模块按顺序调用
 *********************************************************************/
#include "daemon.h"

//服务器做成守护进程，并且线程分离
//客户端做成守护进程，无线程分离

int main()
{
    data_t sdata = {}, cdata = {};
    bzero(&sdata, sizeof(sdata));
    bzero(&cdata, sizeof(cdata));
    strcpy(sdata.ip, "192.168.2.151");    //服务器IP地址——无法同步net.c内的IP地址，修改需手动
    strcpy(cdata.ip, "192.168.2.111");    //客户端IP地址
    sdata.port = 10000;                   //服务器端口
    cdata.port = 10001;

    create_daemon(".", 0600, &sdata, create_tcpserver);
    create_daemon(".", 0600, &cdata, create_tcpconsum);
    return 0;
}
