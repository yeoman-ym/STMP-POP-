#ifndef DAEMON_H
#define DAEMON_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <syslog.h>
#include "common.h"
#include "parsemail.h"
#include "net.h"
#include "devicecontrol.h"
#include <pthread.h>

typedef int (*workfun_t)(const void *);

/*功能:创建守护进程
 *@rootdir:服务器根目录
 @newmode:新服务器根目录权限
 @serverdata:传入创建服务器需要的数据
 @serverwork:创建服务器的函数指针
 * */
int create_daemon(const char *rootdir,mode_t newmode,const void *serverdata,workfun_t serverwork);

int create_tcpserver(const void *data);

void *pthread_fun(void *args);

#endif
