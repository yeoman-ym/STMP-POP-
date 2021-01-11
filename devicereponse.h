#ifndef DEVICEREPONSE_H
#define DEVICEREPONSE_H

int sendemail(int cfd, const struct mail *pmail, const struct subject_ctl *subject);
//读取zhangsan_0.mail邮件文件的内容,发送到套接字

#endif
