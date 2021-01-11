#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

int subjectcontrol(const struct mail *pmail, struct subject_ctl *subject);
int emitupdate(const struct mail *pmail, struct subject_ctl *subject);
int emitcommand(struct subject_ctl *subject);
char *getcreatmailname(const char *username, char *mailname);
char *getsendmailname(const char *username, char *mailname);
int createmail(const struct mail *pmail, struct subject_ctl *subject);
char* getcurrtime();

#endif
