#include "devicecontrol.h"

int subjectcontrol(const struct mail *pmail, struct subject_ctl *subject)
{
    if(NULL == pmail || NULL == subject)
        return -1;

    //取出结构体subject中的命令字command
    char commandbuf[16] = "";
    strcpy(commandbuf, subject->command);

    //判断命令是否为控制命令字
    if(!strcmp(commandbuf, "8LED"))
    {
        emitcommand(subject);
        return 0;
    }
    else if(!strcmp(commandbuf, "7SHU"))
    {
        emitcommand(subject);
        return 0;
    }
    else if(!strcmp(commandbuf, "Moto"))
    {
        emitcommand(subject);
        return 0;
    }

    //判断subject是否为changeTable
    if(!strcmp(commandbuf, "changeTable"))
    {
        emitupdate(pmail, subject);
        return 0;
    }
    else
        return -1;
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

        //从mail结构体中取出附件内容 --------取出失败
        //char name[10] = "";
        //char pass[10] = "";
        char *name = strtok(pmail->atta, " ");
        char *pass = strtok(NULL, " ");

        //将内容写入table.txt文件中
        if(fprintf(fp, "%s %s\n", name, pass))
        {
            perror("fprintf error");
            fclose(fp);
            return -1;
        }
    }
    return 0;
}

int emitcommand(struct subject_ctl *subject)
{
    if(NULL == subject)
        return -1;

    //从subject提取命令字
    char commandbuf[16] = "";
    strcpy(commandbuf, subject->command);
    //命令字是8LED
    if(!strcmp(commandbuf, "8LED"))
    {
        //提取灯号和信号
        //调用用信号灯控制函数
    }
    //命令字是7SHU
    else if(!strcmp(commandbuf, "7SHU"))
    {
        //提取显示信号
        //七段数码管控制函数
    }
    //命令字是MOTO
    else if(!strcmp(commandbuf, "MOTO"))
    {
        //提取转速数据
        //电机控制函数
    }
    return 0;
}
char *getcreatmailname(const char *username, char *mailname)
{
    return 0;
}
char *getsendmailname(const char *username, char *mailname)
{
    return 0;
}
int createmail(const struct mail *pmail, struct subject_ctl *subject);
{
    return 0;
}
char* getcurrtime()
{
    return NULL;
}


