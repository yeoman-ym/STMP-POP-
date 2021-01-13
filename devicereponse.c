/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 设备控制结果，邮件响应
 *********************************************************************/

#include "devicereponse.h"

int sendemail(int sockfd, const char *mailname)
{
    if(sockfd < 2 || mailname == NULL)
    {
        perror("sendemail error");
        return -1;
    }

    int fp = open(mailname, O_RDONLY);
    if(fp < 0)
    {
        perror("open error");
        return -1;
    }

    char buf[1024] = "";
    read(fp, buf, sizeof(buf));
    write(sockfd, buf, strlen(buf));

    close(fp);
    unlink(mailname);
    return 0;
}

char* getcurrtime()
{
    //获取当前时间秒数
    time_t tim = time(NULL);
    //将秒数转为字符串形式的时间并返回
    return ctime(&tim);
}
