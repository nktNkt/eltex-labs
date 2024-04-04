#ifndef _PERSON_H_
#define _PERSON_H_

struct PersonName {
	char firstName[20];
	char lastName[20];
};

struct PersonJobInfo {
	char workLocation[64];
	char workPosition[64];
};

struct PersonLink {
	char messenger[32];
	char link[128];
};

typedef struct Person {
	struct PersonName fullName;
	struct PersonJobInfo job;
	char phones[5][15];
	char emails[5][64];
	struct PersonLink links[5];
} Person;

#endif