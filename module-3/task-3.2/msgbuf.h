#ifndef _MSGBUF_H_
#define _MSGBUF_H_

struct msgbuf {
	long mtype;
	char mtext[1024];
};

#endif
