#ifndef _DOUBLE_LIST_H_
#define _DOUBLE_LIST_H_

struct Item {
	Person value;
	struct Item* next;
	struct Item* prev;
};

#endif