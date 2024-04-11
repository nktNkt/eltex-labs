#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	char program[256];
	char* argv2[64] = {0};
	char* token;
	const char d[2] = " ";
	int i = 0;
	pid_t pid;
	int rv;
	while (1) {
		printf("#> ");
		fgets(program, 256, stdin); program[strcspn(program, "\n")] = 0;
		if (strcmp(program, "q") == 0) break;

		token = strtok(program, d);
		for (i = 0; token != NULL; i++) {
			argv2[i] = token;
			token = strtok(NULL, d);
		}

		switch (pid = fork()) {
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			execv(argv2[0], argv2);
			exit(EXIT_FAILURE);
		default:
			wait(&rv);
			printf("\nExit code: %d\n", rv);
		}
	}
	exit(EXIT_SUCCESS);
}
