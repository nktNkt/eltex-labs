#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgbuf.h"

int main(int argc, char *argv[]) {
	key_t key = ftok("/home/nkt/eltex-labs/module-3/task-3.1/main1.c", 1);
	int msqid = msgget(key, IPC_CREAT | 0600);
	FILE* f = fopen("strings.txt", "r");
	char strbuf[256];

	struct msgbuf message;
	memset(&(message.mtext), 0, 1024);
	message.mtype = 10;

	while (fgets(strbuf, 256, f)) {
		strcpy(message.mtext, strbuf);
		msgsnd(msqid, &message, sizeof(long) + strlen(message.mtext) + 1, 0);
	};

	message.mtype = 255;
	strcpy(message.mtext, "endofmessage");
	msgsnd(msqid, &message, sizeof(long) + strlen(message.mtext) + 1, 0);
	printf("сообщение отправлено\n");

	fclose(f);
	exit(0);
}
