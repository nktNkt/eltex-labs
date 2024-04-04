#include <stdio.h>
#include "Person.h"

Person addPerson(int n)
{
	Person newPerson = { 0 };
	printf("First name: "); fgets(newPerson.fullName.firstName, 20, stdin);
	printf("Last name: "); fgets(newPerson.fullName.lastName, 20, stdin);
	if (n == 2) {
		printf("Work location: "); fgets(newPerson.job.workLocation, 64, stdin);
		printf("Work position: "); fgets(newPerson.job.workPosition, 64, stdin);
		for (int i = 0; i < 5; i++) {
			printf("Phone %d: ", i); fgets(newPerson.phones[i], 15, stdin);
		}
		for (int i = 0; i < 5; i++) {
			printf("Email %d: ", i); fgets(newPerson.emails[i], 15, stdin);
		}
		for (int i = 0; i < 5; i++) {
			printf("Messenger %d: ", i); fgets(newPerson.links[i].messenger, 15, stdin);
			printf("Link %d: ", i); fgets(newPerson.links[i].link, 15, stdin);
		}
	}
	return newPerson;
}

void editPerson(Person* pp, int field) {
	if (field == 1) {
		printf("First name: "); fgets(pp->fullName.firstName, 20, stdin);
		printf("Last name: "); fgets(pp->fullName.lastName, 20, stdin);
	}
	if (field == 2) {
		printf("Work location: "); fgets(pp->job.workLocation, 64, stdin);
		printf("Work position: "); fgets(pp->job.workPosition, 64, stdin);
	}
	if (field == 3) {
		printf("Phones (max 5): ");
		for (int i = 0; i < 5; i++)
			fgets(pp->phones[i], 15, stdin);
	}
	if (field == 4) {
		printf("Emails (max 5): ");
		for (int i = 0; i < 5; i++)
			fgets(pp->emails[i], 15, stdin);
	}
	if (field == 5) {
		for (int i = 0; i < 5; i++) {
			printf("Messenger %d: ", i); fgets(pp->links[i].messenger, 15, stdin);
			printf("Link %d: ", i); fgets(pp->links[i].link, 15, stdin);
		}
	}
}