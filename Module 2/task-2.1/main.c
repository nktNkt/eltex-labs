#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Person.h"
#include "PersonFunc.h"

int main(int argc, char* argv[]) {
	Person contacts[50];
	int amount = 0;
	char command[16];		// input command
	char comEdit[16];		// edit

	while (1) {
		fgets(command, 16, stdin); command[strcspn(command, "\n")] = 0;

		if (strcmp(command, "add1") == 0) {
			contacts[amount] = addPerson(1);
			amount++;
			printf("done\n");
		}

		if (strcmp(command, "add2") == 0) {
			contacts[amount] = addPerson(2);
			amount++;
			printf("done\n");
		}

		if (strcmp(command, "edit") == 0) {
			printf("Number of person: ");
			fgets(comEdit, 16, stdin);
			int num = atoi(comEdit);
			if (num >= amount || num < 0) {
				printf("Out of range\n");
				continue;
			}
			printf("Field: ");
			fgets(comEdit, 16, stdin); comEdit[strcspn(comEdit, "\n")] = 0;
			if (strcmp(comEdit, "name") == 0) editPerson(contacts + num, 1);
			if (strcmp(comEdit, "job") == 0) editPerson(contacts + num, 2);
			if (strcmp(comEdit, "phones") == 0) editPerson(contacts + num, 3);
			if (strcmp(comEdit, "emails") == 0) editPerson(contacts + num, 4);
			if (strcmp(comEdit, "links") == 0) editPerson(contacts + num, 5);
			printf("done\n");
		}

		if (strcmp(command, "remove") == 0) {
			printf("Number of person: ");
			fgets(comEdit, 16, stdin);
			int numDel = atoi(comEdit);
			if (numDel >= amount || numDel < 0) {
				printf("Out of range\n");
				continue;
			}
			for (int i = numDel; i < amount - 1; i++) {
				contacts[i] = contacts[i + 1];
			}
			amount--;
		}

		if (strcmp(command, "print") == 0) {
			for (int i = 0; i < amount; i++) {
				printf("=====================\n");
				printf("Name: %s %s\n", contacts[i].fullName.firstName, contacts[i].fullName.lastName);
				printf("Job: %s, %s\n", contacts[i].job.workLocation, contacts[i].job.workPosition);
				printf("Phones:\n");
				for (int j = 0; j < 5; j++) printf("  %s\n", contacts[i].phones[j]);
				printf("Emails:\n");
				for (int j = 0; j < 5; j++) printf("  %s\n", contacts[i].emails[j]);
				printf("Personal links:\n");
				for (int j = 0; j < 5; j++) printf("  %s - %s\n", contacts[i].links[j].messenger, contacts[i].links[j].link);
			}
		}

		if (strcmp(command, "exit") == 0) break;
	}

	return 0;
}
