#pragma once

typedef struct str_t {
	char* str;
	struct str_t* next;
	struct str_t* prev;
} str_t;

typedef struct {
	str_t* head;
	str_t* tail;
} list_t;

list_t* CreateList(void);
void DestroyList(list_t* list);
str_t* CreateNode(char* str);
void PushFront(list_t* list, char* str);
char* PopFront(list_t* list);
void PushBack(list_t* list, char* str);
void InsBefore(list_t* list, str_t* old, char* str);
void InsecSortList(list_t** list);