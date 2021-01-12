#include "net.h"

int handleconnection(int sockfd, struct mail *pmail)                      //SMTP锁步
{
    if(sockfd < 2 || NULL == pmail)
        return -1;

    const char * response220 = "220 192.168.2.151 ok\r\n";
    const char * response250_HELO = "250-192.168.1.113\r\n250-PIPELINING\r\n250-SIZE 52428800\r\n250-AUTH LOGIN PLAIN\r\n250-AUTH=LOGIN\r\n250-MAILCOMPRESS\r\n250 BITMIME\r\n";
    const char * response334_user = "334 VXNlcm5hbWU6\r\n";
    const char * response334_pass = "334 UGFzc3dvcmQ6\r\n";
    const char * response235 = "235 Authenticatin successful\r\n";
    const char * response250_ok = "250 OK\r\n";
    const char * response_354 = "354 End data with <CR><LF>.<CR><LF>\r\n";
    const char * response_221 = "221 Bye\r\n";

    //向Cline发送数字220，SMTP Server连接开始，220代表域服务准备就绪
    write(sockfd, response220, strlen(response220));
    //接收并判断Clint发送的字符EHLO或HELO，如果是进行下面步骤，否则关闭
    char buf[1024] = "";
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "HELO", 4) && strncmp(buf, "EHLO", 4))
    {
        perror("HELO or EHLO error");
        return -1;
    }

    //向Client发送数字250，代表请求的命令成功完成
    write(sockfd, response250_HELO, strlen(response250_HELO));
    //接收并判断Client的AUTH LOGIN 命令信息，如果是进行下面步骤，不是就关闭socket
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "AUTH LOGIN", 10))
    {
        perror("AUTH LOGIN error");
        return -1;
    }

    //向Client发送数字334_user
    write(sockfd, response334_user, strlen(response334_user));
    table_t table = {};
    //接收Client发送的用户名，成功进行下面步骤，失败结束进程
    if(getusername(sockfd, &table))
    {
        perror("getusername error");
        return -1;
    }

    //向Client发送数字334_pass
    write(sockfd, response334_pass, strlen(response334_pass));
    //接收Client发送的密码，接收成功进行下面步骤，否则结束进程
    if(getpassword(sockfd, &table))
    {
        perror("getpassword error");
        return -1;
    }

    //向Client发送数字235
    write(sockfd, response235, strlen(response235));
    //接收Client发送的发送方地址，接收成功进行下面步骤，否则结束进程
    if(getFromAddress(sockfd, pmail))
    {
        perror("getFromAddress error");
        return -1;
    }

    //向Client发送数字250_ok
    write(sockfd, response250_ok, strlen(response250_ok));
    //接收Client发送的接收方地址
    if(getToAddress(sockfd, pmail))
    {
        perror("getToAddress error");
        return -1;
    }

    //向Client发送数字250
    write(sockfd, response250_ok, strlen(response250_ok));
    //接收并判断Client发送命令DATA，成功进行下面的步骤，否则结束进程
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "DATA", 4))
    {
        perror("DATA error");
        return -1;
    }

    //向Client发送数字354，表示可以发送邮件内容确认
    write(sockfd, response_354, strlen(response_354));
    //接收Client发送的的数据
    if(getbody(sockfd, pmail))
    {
        perror("getbody error");
        return -1;
    }

    //向Client发送数字250
    write(sockfd, response250_ok, strlen(response250_ok));
    //接收并判断发送的是不是QUIT\r\n
    read(sockfd, buf, sizeof(buf)-1);
    if(strncasecmp(buf, "QUIT", 4))
    {
        perror("QUIT error");
        return -1;
    }

    //向Client发送数字221 bye
     write(sockfd, response_221, strlen(response_221));
    return 0;
}

int pop3Connection(int cfd, struct subject_ctl *subject, mail_t *pmail);   //pop3锁步

