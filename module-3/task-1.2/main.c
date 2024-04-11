#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	if (argc == 1) exit(EXIT_SUCCESS);
	pid_t pid;
	switch (pid = fork()) {
	case -1:
		perror("fork");
		exit(EXIT_FAILURE);
	case 0:
		for (int i = 1; i < argc; i += 2) {
			printf("Child %d, input: %d, output: %d\n", getpid(), atoi(argv[i]), atoi(argv[i])*atoi(argv[i]));
		}
		exit(EXIT_SUCCESS);
	default:
		for (int i = 2; i < argc; i += 2) {
			printf("Parent %d, input: %d, output: %d\n", getpid(), atoi(argv[i]), atoi(argv[i])*atoi(argv[i]));
		}
	}
	exit(EXIT_SUCCESS);
}
