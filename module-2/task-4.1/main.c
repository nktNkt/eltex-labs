#include <stdlib.h>
#include <time.h>
#include "Person.h"
#include "PersonFunc.h"
#include "DoubleList.h"
#include "DoubleListFunc.h"

int main() {
	srand(time(NULL));
	
	struct Item* head = NULL;
	Person p = { 0 };

	for (int i = 0; i < 10; i++) {
		p = generatePerson(rand() % 2 + 1);
		head = InsertValue(p, head);
	}
	PrintList(head);
	printf("== == == == == == == == == == == == ==\n\n\n");

	head = DeleteIndex(3, head);
	head = DeleteIndex(0, head);
	PrintList(head);
	printf("== == == == == == == == == == == == ==\n\n\n");

	head = DeleteList(head);
	PrintList(head);


	return 0;
}