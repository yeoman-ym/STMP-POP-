#ifndef PARSEMAIL_H
#define PARSEMAIL_H

#include "common.h"
#include "base64.h"
#include <stdio.h>
#include <string.h>

int verusername(const char * username, struct table *usertable);
int verpassword(const char * password, struct table *usertable);
int parsemail(struct mail * pmail, struct subject_ctl *subject);

#endif
