/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-11
 Description: 初始化邮件体参数，套接字生成，进程建立，各模块按顺序调用
 *********************************************************************/
#include "common.h"
#include "parsemail.h"
#include "net.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sid = socket(AF_INET, SOCK_STREAM, 0);
    if(sid < 0)
    {
        perror("socket error");
        return -1;
    }

    struct sockaddr_in saddr = {};
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(10000);
    saddr.sin_addr.s_addr = inet_addr("192.168.37.132");

    if(bind(sid, (struct sockaddr *)&saddr, sizeof(saddr)))
    {
        perror("bind error");
        close(sid);
        return -1;
    }

    if(listen(sid,10))
    {
        perror("listen error");
        close(sid);
        return -1;
    }

    int cid = accept(sid, NULL, NULL);
    if(cid < 0)
    {
        perror("accept error");
        close(sid);
        return -1;
    }

    mail_t *mail = (mail_t *)malloc(sizeof(mail_t));
    handleconnection(cid, mail);

    struct subject_ctl ctrl = {};
    parsemail(mail, &ctrl);

    free(mail);
    mail = NULL;
}
