# *********************************************************************
# Copyright: HQYJ
# Author: yeoman
# Date: 2021-01-12
# Description: stmp_pop远程控制系统makefile文件
# ********************************************************************
smtp_pop : base64.o parsemail.o mailrecv.o net.o central.o \
	devicecontrol.o devicereponse.o daemon.o
	gcc base64.o parsemail.o mailrecv.o net.o central.o \
		devicecontrol.o daemon.o devicereponse.o -o smtp_pop
	rm -rf *.o
%.o : %.c
	gcc -g -Wall -c *.c
