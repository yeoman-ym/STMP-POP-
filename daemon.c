#include "daemon.h"

int create_daemon(const char *rootdir,mode_t newmode,const void *serverdata,workfun_t serverwork)
{
    if(NULL == rootdir || NULL == serverdata)
        return -1;

    pid_t pid = fork();
    if(pid < 0)
    {
        return -1;
    }
    else if(pid > 0)
    {
        exit(0);
    }
    else if(0 == pid)
    {
        pid_t sid = setsid();
        if(sid < 0)
        {
            syslog(LOG_ERR,"tcp server setsid error %d\n",getpid());
            return -1;
        }

        if(chdir(rootdir) < 0)
        {
            syslog(LOG_ERR,"tcp server chdir error %d\n",getpid());
            return -1;
        }

        if(umask(newmode) < 0)
        {
            return -1;
        }

        int newfd = open("/dev/null",O_RDWR);
        if(newfd < 0)
        {
            return -1;
        }

        dup2(newfd,STDIN_FILENO);
        dup2(newfd,STDOUT_FILENO);
        dup2(newfd,STDERR_FILENO);

        syslog(LOG_INFO,"tcp server start %s %d\n",__FILE__,getpid());
        serverwork(serverdata);
        syslog(LOG_INFO,"tcp server stop %s %d\n",__FILE__,getpid());
    }
    return 0;
}

int create_tcpserver(const void *data)
{
    if(NULL == data)
        return -1;

    data_t *mydata = (data_t *)data;
    int sid = socket(AF_INET, SOCK_STREAM, 0);
    if(sid < 0)
    {
        perror("socket error");
        return -1;
    }

    struct sockaddr_in saddr = {};
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(mydata->port);
    saddr.sin_addr.s_addr = inet_addr(mydata->ip);    //客户端ip地址(ubuntu)

    if(bind(sid, (struct sockaddr *)&saddr, sizeof(saddr)))
    {
        perror("bind error");
        close(sid);
        return -1;
    }

    if(listen(sid,10))
    {
        perror("listen error");
        close(sid);
        return -1;
    }

    int cid = -1;
    pthread_t tid = 0;
    while(1)
    {
        cid = accept(sid, NULL, NULL);
        if(cid < 0)
        {
            perror("accept error");
            close(sid);
            return -1;
        }
        pthread_create(&tid, NULL, pthread_fun, &cid);
    }
    close(sid);
    return 0;
}

void *pthread_fun(void *args)
{
    pthread_detach(pthread_self());
    int *p = (int *)args;
    int cid = *p;

    //SMTP锁步 流程接收邮件
    mail_t *mail = (mail_t *)malloc(sizeof(mail_t));
    handleconnection(cid, mail);

    //解析邮件
    struct subject_ctl ctrl = {};
    parsemail(mail, &ctrl);

    //控制设备或更新程序或更新密码文件
    subjectcontrol(mail, &ctrl);

    //获取新建邮件文件名
    char *filename = mail->filename;
    char filedata[128] = "";
    getcreatmailname(filename, filedata);

    //组装邮件并写入邮件名
    createmail(mail, filedata);

    while(1)
    {
        //POP3流程回复邮件
        pop3Connection(cid, &ctrl, mail);
    }

    free(mail);
    mail = NULL;

    shutdown(cid, SHUT_RDWR);
    close(cid);
    pthread_exit(NULL);
}
