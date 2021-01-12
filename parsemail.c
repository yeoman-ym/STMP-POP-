#include "parsemail.h"

int verusername(const char * username, struct table *usertable)
{
    if(NULL == username || NULL == usertable)
        return -1;

    FILE *fp = fopen(USERFILE, "r");
    if(NULL == fp)
    {
        perror("fopen error");
        return -1;
    }

    struct table temp = {};
    while(fscanf(fp, "%s %s\n", temp.username, temp.password) != EOF)
    {
        if(!strcmp(username, temp.username))
        {
            memcpy(usertable, &temp, sizeof(temp));
            return 0;
        }
    }
    fclose(fp);
    return -1;
}
int verpassword(const char * password, struct table *usertable)
{
    if(NULL == password || NULL == usertable)
        return -1;

    if(!strcmp(password, usertable->password))
        return 0;

    return -1;
}

int parsemail(struct mail * pmail, struct subject_ctl * subject)
{
    //判断结构体pmail subject是否存在
    if(NULL == pmail || NULL == subject)
        return -1;

    //找到主题字前的位置
    const char *subject1 = "Subject:";
    //Subject 往后移动9个字符才是主题字的位置
    char *start = strstr(pmail->raw, subject1) + 9;
    if(NULL == start)
        return -1;
    //找到末尾结束的位置
    char *end = strstr(start, "\r\n") - 1;
    if(NULL == end)
        return -1;
    //主题字的长度
    int len = end - start + 1;

    char buf[128] = "";
    //主题字放入buf中
    strncpy(buf, start, len);
    //将buf进行分割
    const char *command = strtok(buf, " ");
    if(NULL == command)
        return -1;

    strcpy(subject->command, command);
    if(strcmp(command, "8LED"))
    {
        const char *bulb = strtok(NULL, " ");
        subject->bulb = atoi(bulb);
        const char *bulb_crl = strtok(NULL, " ");
        subject->bulb_ctl = atoi(bulb_crl);
    }
    else if(!strcmp(command, "7SHU"))
    {
        const char *num = strtok(NULL, " ");
        subject->signal = atoi(num);
    }
    else if(!strcmp(command, "MOTO"))
    {
        const char *revo = strtok(NULL, " ");
        subject->revo = atoi(revo);
    }
    else if(!strcmp(command, "CHANGTABLE"))
        ;
    else
        return -1;
    return 0;
}

#if 0
int main()
{
    const char *user = "zhangsan";
    const char *pass = "6666666";
    table_t table = {};
    if(verusername(user, &table))
    {
        perror("verusername error");
        return -1;
    }

    if(verpassword(pass, &table))
    {
        perror("verpassword error");
        return -1;
    }

    mail_t mail = {
        .raw = "fdsfdsfdsfsffdf   dsfaffdf Subject: 8LED 7 1\r\nDate:"
    };
    ctrl_t ctrl = {};
    memset(&ctrl, 0, sizeof(ctrl_t));
    if(parsemail(&mail, &ctrl))
    {
        perror("parsemail error");
        return -1;
    }
    printf("command = %s, bulb = %d, bulb_ctl = %d\n", ctrl.command, ctrl.bulb, ctrl.bulb_ctl);
}
#endif
