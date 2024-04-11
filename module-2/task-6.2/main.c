#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Person.h"
#include "PersonFunc.h"
#include "DoubleList.h"
#include "DoubleListFunc.h"

int main() {
	srand(time(NULL));
	int amount = 0;
	char command[16];
	char comEdit[16];
	struct Item* contacts = NULL;
	Person p = { 0 };

	while (1) {
		printf("# ");
		fgets(command, 16, stdin); command[strcspn(command, "\n")] = 0;

		if (strcmp(command, "add1") == 0) {
			p = addPerson(1);
			contacts = InsertValue(p, contacts);
			amount++;
			printf("done\n");
		}

		if (strcmp(command, "add2") == 0) {
			p = addPerson(2);
			contacts = InsertValue(p, contacts);
			amount++;
			printf("done\n");
		}
		
		if (strcmp(command, "gen1") == 0) {
			p = generatePerson(1);
			contacts = InsertValue(p, contacts);
			amount++;
			printf("done\n");
		}

		if (strcmp(command, "gen2") == 0) {
			p = generatePerson(2);
			contacts = InsertValue(p, contacts);
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

			struct Item* tmp = contacts;
			for (int i = 0; i < num; i++) tmp = tmp->next;
			p = tmp->value;
			printf("Field: ");
			fgets(comEdit, 16, stdin); comEdit[strcspn(comEdit, "\n")] = 0;
			if (strcmp(comEdit, "name") == 0) editPerson(&p, 1);
			if (strcmp(comEdit, "job") == 0) editPerson(&p, 2);
			if (strcmp(comEdit, "phones") == 0) editPerson(&p, 3);
			if (strcmp(comEdit, "emails") == 0) editPerson(&p, 4);
			if (strcmp(comEdit, "links") == 0) editPerson(&p, 5);
			tmp->value = p;
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

			contacts = DeleteIndex(numDel, contacts);
			amount--;
			printf("done\n");
		}

		if (strcmp(command, "print") == 0) PrintList(contacts);

		if (strcmp(command, "exit") == 0) break;
	}

	DeleteList(contacts);
	return 0;
}