/**********************************************************************
 Copyright: HQYJ
 Author: yeoman
 Date: 2021-01-12
 Description: 设备控制结果，邮件响应
 *********************************************************************/

#include "devicereponse.h"

int sendemail(int cfd, const struct mail *pmail, const struct subject_ctl *subject)
{
    //从pmail中获取接收方地址作为发送方地址
    //从pmail中获取发送方地址作为接收方地址
    //从filename的命名管道中读取subject    _ctl结构体的信息存入subject,
    //判断subject
    //subject.result == 0
    //subject.result == -1
    //getcurrtime()获取更新时间
    //将上述内容上按照附带的回复邮件格式连接buf中
    //将buf中的内容发送sockfd，成功返回0 失败结束进程
    return 0;
}

char* getcurrtime()
{
    //获取当前时间秒数
    time_t tim = time(NULL);
    //将秒数转为字符串形式的时间并返回
    return ctime(&tim);
}
