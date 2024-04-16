#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int pipes[2];
	pid_t pid;
	int fd;
	fd = creat("numbers.txt", 0666);
	if (fd == -1) printf("Error on create numbers.txt\n");

	int nums = 1;
	if (argc == 2) nums = atoi(argv[1]);

	if (pipe(pipes) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	switch (pid = fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		close(pipes[0]);

		for (int i = 0, n = -999999; i < nums; i++) {
			n = rand() % 10000 - 5000;
			write(pipes[1], &n, sizeof(n));
		}

		close(pipes[1]);
		exit(EXIT_SUCCESS);
	default:
		close(pipes[1]);

		int buf = -999999;

		while(read(pipes[0], &buf, sizeof(buf)) > 0) {
			printf("%d\n", buf);
			if (fd != 1) write(fd, &buf, sizeof(buf));
		}

		wait(NULL);
		close(pipes[0]);
		exit(EXIT_SUCCESS);
	}

	close(fd);
	exit(EXIT_SUCCESS);
}
