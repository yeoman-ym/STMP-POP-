/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 建立网络连接的套接字
 *********************************************************************/

#include "net.h"

int handleconnection(int sockfd, struct mail *pmail)                      //SMTP锁步
{
    if(sockfd < 2 || NULL == pmail)
        return -1;

    const char * response220 = "220 192.168.2.151 ok\r\n";                //服务器端IP地址
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

int pop3connection(int sockfd, mail_t *pmail)   //pop3锁步
{
    if(sockfd < 2 || NULL == pmail)
    {
        perror("pop3Connection error");
        return -1;
    }

    //读取sockfd的内容
    char buf[1024] = {0};

    const char *pop3_server = "+OK pop3 mail server ready\r\n";
    const char *pop3_ok = "+OK\r\n";
    const char *pop3_stat = "+OK 1 300\r\n";
    const char *pop3_list = "+OK 1 message\r\n1 300 \r\n.\r\n";
    const char *pop3_retr = "+OK 120 octets\r\n";

    //Sever发送字符命令： +OK
    write(sockfd, pop3_server, strlen(pop3_server));

    //调用getusre_pop() 截取用户邮箱名，成功调用verusername()函数验证用户名
    table_t table = {};
    bzero(&table, sizeof(table));
    if(getuser_pop(sockfd, &table))
    {
        perror("name error");
        close(sockfd);
        return -1;
    }

    //Server发送字符命令
    write(sockfd, pop3_ok, strlen(pop3_ok));
    //调用getPass() 截取密码，成功后进行密码验证
    if(getpass_pop(sockfd, &table))
    {
        perror("pass error");
        close(sockfd);
        return -1;
    }

    strcpy(pmail->filename, table.username);
    //Server发送字符命令+OK\r\n
    write(sockfd, pop3_ok, strlen(pop3_ok));
    //接收并判断Client发送 STAT
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "STAT", 4))
    {
        perror("STAT error");
        close(sockfd);
        return -1;
    }

    //Server发送字符命令：+OK 1 300\r\n
    write(sockfd, pop3_stat, strlen(pop3_stat));
    //接收并判断Client发送请求： LIST
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "LIST", 4))
    {
        perror("LIST error");
        close(sockfd);
        return -1;
    }

    //Server发送字符命令
    write(sockfd, pop3_list, strlen(pop3_list));
    read(sockfd, buf, sizeof(buf)-1);

    //接收并判断Client请求，RETR 1是则进行一系列步骤
    if(strncmp(buf, "RETE 1", 6))
    {
        perror("RETE error");
        close(sockfd);
        return -1;
    }

    //接收并判断Client请求，DELE 1是则进行一系列步骤
    write(sockfd, pop3_retr, strlen(pop3_retr));
    const char *filename = pmail->filename;
    char myfile[128] = "";

    //获取发送邮件名
    getsendmailname(filename, myfile);
    sendemail(sockfd, myfile);
    write(sockfd, "\r\n.\r\n", 5);
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "DELE 1", 6))
    {
        perror("DELE error");
        close(sockfd);
        return -1;
    }

    //接收并判断Client请求，QUIT 1是则进行一系列步骤
    write(sockfd, pop3_ok, strlen(pop3_ok));
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "QUIT", 4))
    {
        perror("QUIT error");
        close(sockfd);
        return -1;
    }

    //关闭套接字，返回pop3main中
    write(sockfd, pop3_ok, strlen(pop3_ok));
    close(sockfd);
    return 0;
}

