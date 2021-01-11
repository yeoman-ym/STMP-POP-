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

    write(sockfd, response220, strlen(response220));
    char buf[1024] = "";
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "HELO", 4) && strncmp(buf, "EHLO", 4))
    {
        perror("HELO or EHLO error");
        return -1;
    }

    write(sockfd, response250_HELO, strlen(response250_HELO));
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "AUTH LOGIN", 10))
    {
        perror("AUTH LOGIN error");
        return -1;
    }

    write(sockfd, response334_user, strlen(response334_user));
    table_t table = {};
    if(getusername(sockfd, &table))
    {
        perror("getusername error");
        return -1;
    }

    write(sockfd, response334_pass, strlen(response334_pass));
    if(getpassword(sockfd, &table))
    {
        perror("getpassword error");
        return -1;
    }

    write(sockfd, response235, strlen(response235));
    if(getFromAddress(sockfd, pmail))
    {
        perror("getFromAddress error");
        return -1;
    }

    write(sockfd, response250_ok, strlen(response250_ok));
    if(getToAddress(sockfd, pmail))
    {
        perror("getToAddress error");
        return -1;
    }

    write(sockfd, response250_ok, strlen(response250_ok));
    read(sockfd, buf, sizeof(buf)-1);
    if(strncmp(buf, "DATA", 4))
    {
        perror("DATA error");
        return -1;
    }

    write(sockfd, response_354, strlen(response_354));
    if(getbody(sockfd, pmail))
    {
        perror("getbody error");
        return -1;
    }

    write(sockfd, response250_ok, strlen(response250_ok));
    read(sockfd, buf, sizeof(buf)-1);
    if(strncasecmp(buf, "QUIT", 4))
    {
        perror("QUIT error");
        return -1;
    }

     write(sockfd, response_221, strlen(response_221));
    return 0;
}

int pop3Connection(int cfd, struct subject_ctl *subject, mail_t *pmail);   //pop3锁步

