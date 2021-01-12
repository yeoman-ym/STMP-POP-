#ifndef DEVICEREPONSE_H
#define DEVICEREPONSE_H

/* ***************************************************************
 * Summary: 发送回复邮件
 * Parameters:
 * Calls:
 * Return:
 * Others:
 * ***************************************************************/
int sendemail(int cfd, const struct mail *pmail, const struct subject_ctl *subject);

#endif
