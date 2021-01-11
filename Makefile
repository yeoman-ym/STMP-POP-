smtp_pop : base64.o parsemail.o mailrecv.o net.o central.o \
	devicecontrol.o devicereponse.o
	gcc base64.o parsemail.o mailrecv.o net.o central.o \
		devicecontrol.o devicereponse.o -o smtp_pop
	rm -rf *.o
%.o : %.c
	gcc -g -Wall -c *.c
