#ifndef _PERSONFUNC_H_
#define _PERSONFUNC_H_

Person addPerson(int n);
void editPerson(Person* pp, int field);

void generateRandomString(char str[], int n);
Person generatePerson(int n);
void printPerson(Person p);
int comparePersons(Person p1, Person p2);

#endif