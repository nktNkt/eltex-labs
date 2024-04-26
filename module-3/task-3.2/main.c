#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgbuf.h"

int main(int argc, char *argv[]) {
	key_t key = ftok("./main1.c", 1);
	char strbuf[1024];
	char command[4];
	int msqid = msgget(key, IPC_CREAT | 0600);
	long mt_from, mt_to;

	struct msgbuf message;
	memset(&(message.mtext), 0, 1024);

	if (argc > 2) {
		mt_from = atol(argv[1]);
		mt_to = atol(argv[2]);
	}
	else {
		mt_from = 100;
		mt_to = 200;
	}
	printf("Sender = %ld\n", mt_from);
	printf("Receiver = %ld\n\n", mt_to);

	if (mt_from == 255 || mt_to == 255) exit(EXIT_FAILURE);

	printf("s - send message\n");
	printf("g - receive message\n");
	printf("ex - exit\n\n");

	while (1) {
		printf("# ");
		fgets(command, 4, stdin); command[strcspn(command, "\n")] = 0;

		if (strcmp(command, "g") == 0) {
			message.mtype = 255;
			msgrcv(msqid, &message, 1024, mt_from, IPC_NOWAIT);
			if (message.mtype == 255) printf("No new messages.\n");
			else printf("%s\n", message.mtext);
		}
		else if (strcmp(command, "s") == 0) {
			fgets(strbuf, 1024, stdin);
			message.mtype = mt_to;
			strcpy(message.mtext, strbuf);
			msgsnd(msqid, &message, sizeof(long) + strlen(message.mtext) + 1, 0);
		}
		else if (strcmp(command, "ex") == 0) {
			break;
		}
		else printf("Unknown command\n");
	};

	exit(0);
}
