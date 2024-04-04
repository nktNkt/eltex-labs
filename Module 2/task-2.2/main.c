#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

#define N 5

int main(int argc, char* argv[])
{
	if (argc != 4) {
		printf("Not enough arguments\n");
		return 1;
	}
	char commands[N][16] = { "plus", "minus", "multiply", "divide", "mod"};
	int c = 0;
	int arg1 = atoi(argv[2]);
	int arg2 = atoi(argv[3]);

	for (c = 0; c < N && strcmp(argv[1], commands[c]); c++);

	if (c == 0) {
		printf("Result: %d\n", com_plus(arg1, arg2));
	}

	if (c == 1) {
		printf("Result: %d\n", com_minus(arg1, arg2));
	}

	if (c == 2) {
		printf("Result: %d\n", com_multiply(arg1, arg2));
	}

	if (c == 3) {
		printf("Result: %.2f\n", com_divide(arg1, arg2));
	}

	if (c == 4) {
		printf("Result: %d\n", com_mod(arg1, arg2));
	}

	if (c == N) {
		printf("Unknown command\n");
	}

	return 0;
}