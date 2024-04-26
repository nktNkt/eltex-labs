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
	int message_recieved = 0;
	struct msgbuf message;

	message_recieved = msgrcv(msqid, &message, 1024, 0, 0);
	while (message.mtype != 255 && message_recieved) {
		printf("%s", message.mtext);
		message_recieved = msgrcv(msqid, &message, 1024, 0, 0);
	};

	if (message.mtype == 255) {
		printf("Обмен данными завершен (255).\n");
		msgctl(msqid, IPC_RMID, NULL);
	}

	exit(0);
}
