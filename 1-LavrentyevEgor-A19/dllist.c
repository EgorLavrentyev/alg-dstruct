#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dllist.h"



list_t* CreateList(void)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	if (list)
	{
		list->head = list->tail = NULL;
	}
	else
	{
		printf("Malloc error");
		exit(0);
	}
	return list;
}

void DestroyList(list_t* list)
{
	if (!list)
	{
		exit(1);
	}
	str_t* tmp = list->head;
	str_t* next;

	do 
	{

		next = tmp->next;
		free(tmp);
		tmp = next;

	} while (tmp->next);

	list->tail = NULL;
	list->head = NULL;
	free(tmp);
	free(list);
}

str_t* CreateNode(char* str)
{
	if (!str)
	{
		exit(1);
	}
	str_t* node = malloc(sizeof(str_t));
	if (node)
	{
		node->next = node->prev = NULL;
		node->str = str;
	}
	else
	{
		printf("Malloc error");
		exit(0);
	}

	return node;
}

void PushFront(list_t* list, char* str)
{
	if (!list || !str)
	{
		exit(1);
	}
	str_t* node = CreateNode(str);

	node->next = list->head;
	list->head = node;
	if (list->tail == NULL)
	{
		list->tail = node;
	}
	
}

char* PopFront(list_t* list)
{
	if (!list)
	{
		exit(1);
	}
	if (list->head == NULL)
	{
		printf("Empty list");
		exit (2);
	}

	str_t* tmp;
	char* data;

	tmp = list->head;
	list->head = list->head->next;

	if (tmp->next == NULL)
	{
		list->tail = NULL;
	}
	
	if (list->head)
	{
		list->head->prev = NULL;
	}
	data = tmp->str;
	free(tmp);
	return data;
}

void PushBack(list_t* list, char* str) 
{
	if (!list || !str)
	{
		exit(1);
	}
	str_t* node = CreateNode(str);
	
	node->prev = list->tail;

	if (!list->head)
	{
		list->head = list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}


void InsBefore(list_t* list, str_t* old, char* str)
{
	if (!list || !str || !old)
	{
		exit(1);
	}
	if (!old->prev)
	{
		PushFront(list, str);
		return;
	}
	str_t* node = CreateNode(str);
	node->prev = old->prev;
	old->prev->next = node;
	node->next = old;
	old->prev = node;
}


void InsecSortList(list_t** list)  //двойной указатель, чтобы потом его поменять на новый список
{
	if (!list || !(*list))
	{
		exit(1);
	}
	if (!(*list)->head)
	{
		return;
	}
	list_t* new = CreateList();     // новый отсортированный список
	str_t* cur = NULL;    //текущий элемент, для которого ищется место в отсортированном списке
	str_t* tmp = NULL;    //элемент отсортированного списка, с которым сравнивается текущий
	str_t* next = NULL;

	PushFront(new, PopFront(*list));   // перенос первого элемента

	cur = (*list)->head;

	while (cur)
	{
		tmp = new->head;
		while (tmp != NULL && (strcmp(cur->str, tmp->str) > 0 || strcmp(cur->str, tmp->str) == 0))  //пока не меньше
		{
			tmp = tmp->next;
		}
		if (!tmp)    //если дошли до конца
		{
			PushBack(new, cur->str);
		}
		else
		{
			InsBefore(new, tmp, cur->str);
		}

		next = cur->next; //удаление элемента из старого списка
		free(cur);
		cur = next;
	}

	free(*list);
	*list = new;
}
