#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <mqueue.h>

#define QUEUE_NAME_1   "/myqueue1"
#define QUEUE_NAME_2   "/myqueue2"
#define SIZE           1024

int main(int argc, char *argv[]) {
	char strbuf[SIZE];
	char command[4];

	const char* qn1 = QUEUE_NAME_1;
	const char* qn2 = QUEUE_NAME_2;

	long mt_from, mt_to;

	mqd_t ds1, ds2;
	struct mq_attr queue_attr;
	queue_attr.mq_maxmsg = 128;
	queue_attr.mq_msgsize = SIZE;

	mt_from = 100;
	mt_to = 200;
	if (argc > 1) if (atol(argv[1]) == 2) {
		mt_from = 200;
		mt_to = 100;
		qn1 = QUEUE_NAME_2;
		qn2 = QUEUE_NAME_1;
	}

	printf("Sender = %ld\n", mt_from);
	printf("Receiver = %ld\n\n", mt_to);

	if ((ds1 = mq_open(qn1, O_RDWR | O_NONBLOCK, 0666, &queue_attr)) == (mqd_t)-1) {
		perror("Creating queue 1 error");
		exit(EXIT_FAILURE);
	}

	if ((ds2 = mq_open(qn2, O_RDWR | O_NONBLOCK, 0666, &queue_attr)) == (mqd_t)-1) {
		perror("Creating queue 2 error");
		exit(EXIT_FAILURE);
	}

	printf("s - send message\n");
	printf("g - receive message\n");
	printf("ex - exit\n\n");

	while (1) {
		printf("# ");
		fgets(command, 4, stdin); command[strcspn(command, "\n")] = 0;

		if (strcmp(command, "g") == 0) {
			int prio;
			memset(strbuf, 0, 1024);
			if (mq_receive(ds1, strbuf, SIZE, &prio) == -1) {
				perror("Cannot receive");
			}
			else printf("%s\n", strbuf);
		}
		else if (strcmp(command, "s") == 0) {
			fgets(strbuf, 1024, stdin);
			if (mq_send(ds2, strbuf, strlen(strbuf), mt_to) == -1) {
				perror("Sendind message error");
			}
		}
		else if (strcmp(command, "ex") == 0) {
			break;
		}
		else printf("Unknown command\n");
	};

	exit(0);
}
