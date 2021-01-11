#ifndef COMMON_H
#define COMMON_H

#define MAX_MAIL (8 * 1024)
#define MAX_ATTA (7 * 1024)
#define USERFILE "table.txt"

typedef struct mail
{
    char send [80];             //发送者地址
    char recv[80];              //接收者地址
    char subject[80];           //主题字
    char filename[80];          //文件名
    char raw [MAX_MAIL];        //邮件内容
    char atta [MAX_ATTA];       //附件内容
    int len;                    //附件长度
}mail_t;

typedef struct subject_ctl
{
    char command[16];           //命令字    8LED 7SHU MOTO CHANGETABLE
    int bulb;                   //灯的号数(1~8)
    int signal;                 //七段数码管显示信号(0~99)
    int revo;                   //电机转数(0,1000)
    int bulb_ctl;               //控制信号（0关灯，1开灯）
    int result;                 //0表示控制成功，－1表示控制失败
}ctrl_t;

typedef struct table
{
    char username[10];          //邮件用户名
    char password[10];          //用户密码
}table_t;

#endif