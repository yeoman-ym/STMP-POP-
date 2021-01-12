/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 根据主题字完成设备控制及应用程序更新
 *********************************************************************/

#include "devicecontrol.h"

int subjectcontrol(const struct mail *pmail, struct subject_ctl *subject)
{
    if(NULL == pmail || NULL == subject)
        return -1;

    //取出结构体subject中的命令字command
    char commandbuf[4] = "";
    strcpy(commandbuf, subject->command);

    //判断命令是否为控制命令字
    if(!strcmp(commandbuf, "8LED") || !strcmp(commandbuf, "7SHU") || !strcmp(commandbuf, "MOTO"))
    {
        if(emitcommand(pmail, subject) < 0)
        {
            subject->result = -1;
            perror("emitcommand error");
            return -1;
        }
        subject->result = 0;
    }
    subject->result = -1;

    //判断subject是否为changeTable
    if(!strcmp(commandbuf, "CHANGTABLE"))
    {
        if(emitupdate(pmail, subject) < 0)
        {
            subject->result = -1;
            perror("emitupdate error");
            return -1;
        }
        //更新成功表示
        sprintf(subject_data, "%s Update Success!", pmail->subject);
        subject->result = 0;
    }

    return 0;
}

int emitupdate(const struct mail *pmail, struct subject_ctl *subject)
{
    if(NULL == pmail || NULL == subject)
        return -1;

    //从subject中取出命令字
    char commandbuf[16] = "";
    strcpy(commandbuf, subject->command);

    //判断命令字是否为changTable
    if(!strcmp(commandbuf, "changeTable"))
    {
        //以清空写打开table.txt文件
        FILE *fp = fopen("table.txt", "w+");
        if(NULL == fp)
        {
            perror("open error");
            return -1;
        }

        //从mail结构体中取出附件内容
        char buf[MAX_ATTA] = "";
        strncpy(buf, pmail->atta, strlen(pmail->atta));

        //将内容写入table.txt文件中
        if(fprintf(fp, "%s", buf))
        {
            perror("fprintf error");
            fclose(fp);
            return -1;
        }
        printf("updata ok\n");
        fclose(fp);
    }
    return 0;
}

int emitcommand(const struct mail *pmail, struct subject_ctl *subject)
{
    if(NULL == subject || NULL == pmail)
    {
        perror("emitcommand data error");
        return -1;
    }

    //从subject提取命令字
    char commandbuf[4] = "";
    char buf[128] = "";
    strcpy(commandbuf, subject->command);

    //命令字是8LED
    if(!strcmp(commandbuf, "8LED"))
    {
        //提取灯号和信号
        sprintf(buf, "%s %d %d error", subject->command, subject->bulb, subject->bulb_ctl);
        if(subject->bulb < 0 || subject->bulb > 8 || subject->bulb_ctl < 0 || subject->bulb_ctl > 1)
        {
            perror("8LED error");
            //subject更新
            sprintf(subject_data, "%s Control faild", pmail->subject);
            subject->result = -1;
            return -1;
        }
        //控制成功表示
        sprintf(subject_data, "%s Control Success!", pmail->subject);
        //调用用信号灯控制函数——显示状态
        printf("The %d bulb of state is %d.\n", subject->bulb, subject->bulb_ctl);
        subject->result = 0;

        if(!subject->result)
        {
            sprintf(buf, "%s %d %d OK", subject->command, subject->bulb, subject->bulb_ctl);
        }
    }

    //命令字是7SHU
    else if(!strcmp(commandbuf, "7SHU"))
    {
        //提取显示信号
        sprintf(buf, "%s %d error", subject->command, subject->signal);
        if(subject->signal < 0 || subject->signal > 99)
        {
            perror("7SHU error");
            //subject更新
            sprintf(subject_data, "%s Control faild", pmail->subject);
            subject->result = -1;
            return -1;
        }
        //控制成功表示
        sprintf(subject_data, "%s Control Success!", pmail->subject);

        //调用数码管控制函数——数码管状态
        printf("The digital tube %d ON.\n", subject->signal);
        subject->result = 0;

        if(!subject->result)
        {
            sprintf(buf, "%s %d OK", subject->command, subject->signal);
        }
    }

    //命令字是MOTO
    else if(!strcmp(commandbuf, "MOTO"))
    {
        //提取转速数据
        sprintf(buf, "%s %d error", subject->command, subject->revo);
        if(subject->revo < 0 || subject->revo > 1000)
        {
            perror("MOTO error");
            //subject更新
            sprintf(subject_data, "%s Control faild", pmail->subject);
            subject->result = -1;
            return -1;
        }
        //控制成功表示
        sprintf(subject_data, "%s Control Success!", pmail->subject);

        //调用电机控制函数———显示电机状态
        printf("The motor speed is %d\n", subject->revo);
        subject->result = 0;

        if(!subject->result)
        {
            sprintf(buf, "%s %d OK", subject->command, subject->revo);
        }
    }
    else
        return -1;
    return 0;
}

char *getcreatmailname(const char *username, char *mailname)
{
    if(NULL == username || NULL == mailname)
    {
        perror("getcreatmailname error");
        return NULL;
    }

    char mail[128] = "";
    const char *format = "%s_%d.mail";
    for(int i = 0; i < 10; i++)
    {
        sprintf(mail, format, username, i);
        if(!access(mail, F_OK))
            continue;
        if(open(mail, O_WRONLY | O_CREAT | O_TRUNC, 0666) > 0)
        {
            strcpy(mailname, mail);
            break;
        }
    }
    return mailname;
}

char *getsendmailname(const char *username, char *mailname)
{
    if(NULL == username || NULL == mailname)
    {
        perror("getsendmailname error");
        return NULL;
    }

    char mail[128] = "";
    const char *format = "%s_%d.mail";
    for(int i = 10; i > -1; i--)
    {
        sprintf(mail, format, username, i);
        if(!access(mail, F_OK))
        {
            strcpy(mailname, mail);
            return mailname;
        }
        else
            continue;
    }
    return NULL;

}
int createmail(const struct mail *pmail, const char *mailname)
{
    if(NULL == pmail || NULL == mailname)
    {
        perror("createmail error");
        return -1;
    }

    FILE *fp = fopen(mailname, "w");
    if(NULL == fp)
    {
        perror("fopen error");
        return -1;
    }

    //将名字分割出来
    char name[16] = "";
    strcpy(name, pmail->send);
    char *str = strtok(name, "@");

    fprintf(fp, "Message-ID: <001101c93cc4$1ed2ae30$5400a8c0@liuxiao\
            forever>\r\nFrom: \"%s\" <%s>\r\nTo: <%s>\r\nSubject:%s \r\nMIME-Version\
            : 1.0\r\nContent-Type: multipart/alternative; \r\nX-Priority\
            : 3..X-MSMail-Priority: Normal\r\nX-Mailer: Microsoft Outlook Express\
            6.00.2900.3138\r\nX-MimeOLE: Produced By Microsoft MimeOLE \
            V6.00.2900.3198\r\n\r\n",str,pmail->send,pmail->recv,subject_data);
    fclose(fp);
    return 0;
}
