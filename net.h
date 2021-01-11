#ifndef NET_H
#define NET_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "base64.h"
#include "parsemail.h"
#include "mailrecv.h"

int handleconnection(int sockfd, struct mail *pmail);                      //SMTP锁步
int pop3Connection(int cfd, struct subject_ctl *subject, mail_t *pmail);   //pop3锁步

#endif
