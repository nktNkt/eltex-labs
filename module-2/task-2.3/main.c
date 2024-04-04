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
	char commands[N][16] = { "plus", "minus", "multiply", "divide", "mod" };
	int c = 0;
	int arg1 = atoi(argv[2]);
	int arg2 = atoi(argv[3]);

	for (c = 0; c < N && strcmp(argv[1], commands[c]); c++);

	float (*operations) (int, int) = com_select(c);
	float result = operations(arg1, arg2);

	printf("Result: %.2f\n", result);

	return 0;
}