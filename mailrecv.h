#ifndef MAILRECV_H
#define MAILRECV_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "parsemail.h"
#include "base64.h"

int getusername(int sockfd, struct table *p);            //SMTP
int getpassword(int sockfd, struct table *p);
int getFromAddress(int sockfd, struct mail *pmail);
int getToAddress(int sockfd, struct mail *pmail);
int getbody(int sockfd, struct mail *pmail);
int getslave (int sockfd, struct mail *pmail);

int getuser_pop(int sockfd, struct table *p);           //POP3
int getpass_pop(int sockfd, struct table *p);

#endif

