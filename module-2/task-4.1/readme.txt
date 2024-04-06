Функции DoubleList.h:
Item* InsertValue(Person val, Item* head) - В список head добавляется элемент val, измененный список возвращается
Item* DeleteIndex(int id, Item* head) - Из списка head удаляется элемент с индексом id, измененный список возвращается
Item* DeleteList(Item* head) - Возвращает пустой список
void PrintList(Item* head) - Вывод списка

Функции PersonFunc.h:
void generateRandomString(char str[], int n) - Создание строки из n случайных латинских символов (нужна для функции generatePerson)
Person generatePerson(int n) - Структура Person заполняется случайными строками
void printPerson(Person p) - Вывод структуры Person
int comparePersons(Person p1, Person p2) - Сравнение двух структур Person (нужно для функции списка InsertValue)