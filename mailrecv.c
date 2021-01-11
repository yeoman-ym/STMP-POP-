#include "mailrecv.h"

int getusername(int sockfd, struct table *pmail)            //SMTP
{
    char buf[128] = "";
    read(sockfd, buf, sizeof(buf)-1);
    //base64_decode();
    //verusername();

    return 0;
}
int getpassword(int sockfd, struct table *pmail)
{
    char buf[128] = "";
    read(sockfd, buf, sizeof(buf)-1);
    return 0;
}
int getFromAddress(int sockfd, struct mail *pmail)
{
    char buf[128] = "";
    read(sockfd, buf, sizeof(buf)-1);
    return 0;
}
int getToAddress(int sockfd, struct mail *pmail)
{
    char buf[128] = "";
    read(sockfd, buf, sizeof(buf)-1);
    return 0;
}
int getbody(int sockfd, struct mail *pmail)
{
    read(sockfd, pmail->raw, sizeof(pmail->raw)-1);

    read(sockfd, pmail->raw, sizeof(pmail->raw)-1);

    char buf[128] = "";
    read(sockfd, buf, sizeof(buf)-1);
    return 0;
}
int getslave (int sockfd, struct mail *pmail)
{
    return 0;
}

int getuser_pop(int sockfd, struct table *p)           //POP3
{
    return 0;
}
int getpass_pop(int sockfd, struct table *p)
{
    return 0;
}
