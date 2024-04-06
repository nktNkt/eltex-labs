#ifndef _DOUBLE_LIST_FUNC_H_
#define _DOUBLE_LIST_FUNC_H_

struct Item* InsertValue(Person val, struct Item* head);
struct Item* DeleteIndex(int id, struct Item* head);
struct Item* DeleteList(struct Item* head);
void PrintList(struct Item* head);

#endif
