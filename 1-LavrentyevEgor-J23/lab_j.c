#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 65536

typedef struct
{
	int key;          // -1 if empty
	char* str;
}TableSlot_t;

TableSlot_t* CreateTable(void)
{
	TableSlot_t* table = malloc(TABLE_SIZE * sizeof(TableSlot_t));

	if (!table)
	{
		printf("Memory allocation error");
		return NULL;
	}

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		table[i].key = -1;
		table[i].str = NULL;
	}

	return table;
}

void DestroyTable(TableSlot_t* table)
{
	if (!table)
		return;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i].key != -1)
			free(table[i].str);
	}

	free(table);
}

int H_1(int key)
{
	return key % TABLE_SIZE;
}

int H_2(int key)
{
	return key % (TABLE_SIZE - 1) + 1;
}

int Find(TableSlot_t* table, int key)
{
	if (!table)
		return -1;

	int index = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		index = (H_1(key) + i * H_2(key)) % TABLE_SIZE;
		if (table[index].key != -1)
		{
			if (table[index].key == key)
				return 1;
		}
		else
			return 0;
	}

	return 0;
}

void Add(TableSlot_t* table, int key, char* str)
{
	if (!table || !str)
		return;

	if (Find(table, key))
		return;
	int index = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		index = (H_1(key) + i * H_2(key)) % TABLE_SIZE;
		if (table[index].key == -1)
		{
			table[index].key = key;
			table[index].str = malloc(strlen(str) * sizeof(char) + 1);
			if (!table[index].str)
			{
				printf("Memory allocation error");
				return;
			}
			strcpy(table[index].str, str);
			return;
		}
	}

	printf("Not enough space");
}

void Remove(TableSlot_t* table, int key)
{
	if (!table)
		return;

	int index = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		index = (H_1(key) + i * H_2(key)) % TABLE_SIZE;
		if (table[index].key == key)
		{
			table[index].key = -1;
			free(table[index].str);
			return;
		}
	}
	return;
}

int main(void)
{
	TableSlot_t* table = CreateTable();
	char sym;
	int key;

	while (fscanf(stdin, "%c %d", &sym, &key) > 0)
	{
		if (sym == 'a')
		{
			Add(table, key, " ");
		}

		if (sym == 'r')
		{
			Remove(table, key);
		}

		if (sym == 'f')
		{
			if (Find(table, key))
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
		}
	}

	DestroyTable(table);

	return 0;
}