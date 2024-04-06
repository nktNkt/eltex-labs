#include <stdio.h>
#include <string.h>
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

void generateRandomString(char str[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int randomChar = rand() % 26;
		if (rand() % 2) str[i] = 'a' + randomChar;
		else str[i] = 'A' + randomChar;
	}
	str[n - 1] = '\0';
}

Person generatePerson(int n) {
	Person newPerson = { 0 };

	generateRandomString(newPerson.fullName.firstName, 6);
	generateRandomString(newPerson.fullName.lastName, 6);
	if (n == 2) {
		generateRandomString(newPerson.job.workLocation, 64);
		generateRandomString(newPerson.job.workPosition, 64);
		for (int i = 0; i < 5; i++) {
			generateRandomString(newPerson.phones[i], 15);
			generateRandomString(newPerson.emails[i], 64);
			generateRandomString(newPerson.links[i].messenger, 32);
			generateRandomString(newPerson.links[i].link, 128);
		}
	}

	return newPerson;
}

void printPerson(Person p) {
	printf("Name: %s %s\n", p.fullName.firstName, p.fullName.lastName);
	if (p.job.workLocation[0]) printf("Job: %s, %s\n", p.job.workLocation, p.job.workPosition);
	printf("Phones:\n");
	for (int j = 0; j < 5; j++) if (p.phones[j][0]) printf("  %s\n", p.phones[j]);
	printf("Emails:\n");
	for (int j = 0; j < 5; j++) if (p.emails[j][0]) printf("  %s\n", p.emails[j]);
	printf("Personal links:\n");
	for (int j = 0; j < 5; j++) if (p.links[j].messenger[0]) printf("  %s - %s\n", p.links[j].messenger, p.links[j].link);
}

int comparePersons(Person p1, Person p2) {
	//res = p1 > p2
	// -1 -- N
	//  1 -- Y
	//  0 -- E
	int res;
	res = memcmp(p1.fullName.firstName, p2.fullName.firstName, sizeof(Person));
	return -res;
}