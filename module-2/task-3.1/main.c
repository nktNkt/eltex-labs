#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "func.h"

int main(int argc, char* argv[]) {
	char command[16];
	unsigned char uinput[64];
	int filemask, filemask2;
	struct stat stfile;

	while (1) {
		printf("Command: ");
		fgets(command, 16, stdin); command[strcspn(command, "\n")] = 0;

		if (strcmp(command, "1") == 0) {
			printf("Input access permission: ");
			fgets(uinput, 64, stdin); uinput[strcspn(uinput, "\n")] = 0;
			filemask = inputToBin(uinput);
			binPrint(filemask);
		}

		if (strcmp(command, "2") == 0) {
			printf("File name: ");
			fgets(uinput, 64, stdin); uinput[strcspn(uinput, "\n")] = 0;
			stat(uinput, &stfile);
			symPrint(stfile.st_mode);
			printf("%o\n", stfile.st_mode % 512);
			binPrint(stfile.st_mode);
		}

		if (strcmp(command, "3") == 0) {
			printf("File name: ");
			fgets(uinput, 64, stdin); uinput[strcspn(uinput, "\n")] = 0;
			stat(uinput, &stfile);
			printf("Edit: ");
			fgets(uinput, 64, stdin); uinput[strcspn(uinput, "\n")] = 0;
			stfile.st_mode = fileedit(stfile.st_mode, uinput);
			symPrint(stfile.st_mode);
			printf("%o\n", stfile.st_mode % 512);
			binPrint(stfile.st_mode);
		}

		if (strcmp(command, "0") == 0) break;
	}
	return 0;
}
