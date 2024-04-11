#include <stdlib.h>
#include "Person.h"
#include "DoubleList.h"

struct Item* InsertValue(Person val, struct Item* head) {
	struct Item* newItem;
	struct Item* tmp = head;
	newItem = malloc(sizeof(struct Item));
	newItem->value = val;

	if (NULL == head) {
		newItem->prev = NULL;
		newItem->next = NULL;
		head = newItem;
		return head;
	}
	while (comparePersons(tmp->value, newItem->value) > 0 && tmp->next)
		tmp = tmp->next;
	if (comparePersons(tmp->value, newItem->value) > 0) {
		newItem->prev = tmp;
		newItem->next = NULL;
		tmp->next = newItem;
	}
	else {
		newItem->prev = tmp->prev;
		newItem->next = tmp;
		if (tmp->prev) tmp->prev->next = newItem;
		else head = newItem;
		tmp->prev = newItem;
	}
	return head;
}

struct Item* DeleteIndex(int id, struct Item* head) {
	struct Item* tmp = head;

	if (NULL == head) return head;

	for (int i = 0; i < id && tmp; i++) tmp = tmp->next;
	if (!tmp) return head;

	if (tmp->next) tmp->next->prev = tmp->prev;
	if (tmp->prev) tmp->prev->next = tmp->next;

	if (tmp == head) head = head->next;

	free(tmp);
	return head;
}

struct Item* DeleteList(struct Item* head) {
	struct Item* tmp = head;
	struct Item* itemForRemove;
	if (NULL == head) return NULL;
	do {
		itemForRemove = tmp;
		tmp = tmp->next;
		free(itemForRemove);
	} while (tmp != NULL);
	return NULL;
}

void PrintList(struct Item* head) {
	struct Item* tmp = head;
	if (head == NULL) {
		printf("List empty!\n");
		return;
	}
	do {
		printPerson(tmp->value);
		printf("========================\n");
		tmp = tmp->next;
	} while (tmp != NULL);
	printf("\n");
}
