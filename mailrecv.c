#include "mailrecv.h"

int getusername(int sockfd, struct table *pmail)            //SMTP
{
    char buf[128] = "";
    //从sockfd中接收数据，将数据存入buf中recv
    int len = read(sockfd, buf, sizeof(buf)-1);
    //将buf[len-2]去掉\r\n
    buf[len-2] = '\0';

    //对buf进行解码
    char *str = base64_decode(buf);
    //用户名验证，成功进行下面步骤，失败关闭socket
    if(verusername(str, pmail))
    {
        perror("verusername error");
        close(sockfd);
        return -1;
    }

    //将str的值复制到验证表结构体table中
    strncpy(pmail->username, str, strlen(str));
    return 0;
}

int getpassword(int sockfd, struct table *pmail)
{
    char buf[128] = "";
    //接收数据，存入buf中
    int len = read(sockfd, buf, sizeof(buf)-1);
    //将buf[len-2]去掉\r\n
    buf[len-2] = '\0';

    //用户名解码存入str
    char *str = base64_decode(buf);
    //调用函数进行密码验证，成功进行下面步骤，失败则调用
    if(verpassword(str, pmail))
    {
        perror("verpassword error");
        return -1;
    }

    strncpy(pmail->password, str, strlen(str));
    return 0;
}

int getFromAddress(int sockfd, struct mail *pmail)
{
    char buf[128] = "";
    //读取数据存入buf中
    read(sockfd, buf, sizeof(buf)-1);
    //从buf中查找<> 中间的数据，找到后就是发送方的地址，作为回复邮件的接收方地址
    char *start = strstr(buf, '<');
    if(NULL == start)
    {
        perror("index error");
        return -1;
    }

    char *end = strstr(start+1, '>');
    if(NULL == end)
    {
        perror("index error");
        return -1;
    }

    int count = end - start + 1;
    char temp[128] = "";
    strncpy(temp, start+1, count);
    strcpy(pmail->send, temp);

    return 0;
}

int getToAddress(int sockfd, struct mail *pmail)
{
    char buf[128] = "";
    read(sockfd, buf, sizeof(buf)-1);
    //从buf中查找<> 中间的数据，找到后就是发送方的地址，作为回复邮件的接收方地址
    char *start = strstr(buf, '<');
    if(NULL == start)
    {
        perror("index error");
        return -1;
    }

    char *end = strstr(start+1, '>');
    if(NULL == end)
    {
        perror("index error");
        return -1;
    }

    int count = end - start + 1;
    char temp[128] = "";
    strncpy(temp, start+1, count);
    strcpy(pmail->recv, temp);

    return 0;
}
int getbody(int sockfd, struct mail *pmail)
{
    //read(sockfd, pmail->raw, sizeof(pmail->raw)-1);
    //read(sockfd, pmail->raw, sizeof(pmail->raw)-1);

    char buf[MAX_MAIL] = "";
    int len = read(sockfd, buf, sizeof(buf)-1);
    if(len < 0)
    {
        perror("read error");
        return -1;
    }

    //将buf内容存入邮件结构体中
    strcpy(pmail->raw, buf);
    //读取附件内容
    char *start = strstr(buf, "filename=");
    if(NULL == start)
    {
        getslave(sockfd, pmail);
        return 0;
    }
    else
    {
        char *end = strstr(start, "\r\n\r\n");
        int len = end - start + 1;
        //将附件内容复制给邮件结构体
        strncpy(pmail->atta, start, len);
    }

    //邮件主体内容不明确
    if(strstr(buf,"\t\n.\r\n") == NULL)
    {
        read(sockfd, buf, sizeof(buf));
    }
    return 0;
}

//附件内容与文档叙述不符
int getslave (int sockfd, struct mail *pmail)
{
    char buf[MAX_ATTA] = "";
    read(sockfd, buf, sizeof(buf)-1);
    //附件起始位置
    char *start = strstr(buf, "filename=");

    if(NULL == start)
    {
        perror("find error");
        return -1;
    }

    //附件结束位置
    char *end = strstr(start, "\r\n\r\n");
    if(NULL == end)
    {
        perror("find end error");
        return -1;
    }

    return 0;
}

int getuser_pop(int sockfd, struct table *p)           //POP3
{
    //参数判断
    //从sockfd接收数据，存入buf
    //判断接收到的数据是否为空，无数据继续接收，不为空就继续下面步骤
    //查找USER之后的用户名存入str
    //进行用户名验证
    //verusername();
    //str的值复制到table结构体中，用户名复制到sender中
    return 0;
}

int getpass_pop(int sockfd, struct table *p)
{

    //参数判断
    //从sockfd接收数据，存入buf
    //判断接收到的数据是否为空，无数据继续接收，不为空就继续下面步骤
    //查找USER之后的用户名存入str
    //进行用户名验证
    //verpassword();
    //str的值复制到table结构体中
    return 0;
}
