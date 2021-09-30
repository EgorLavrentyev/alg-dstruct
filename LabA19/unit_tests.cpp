#pragma warning(disable : 4996)
#include "gtest/gtest.h"
extern "C"
{
	#include "dllist.h"
}

TEST(CreateListTest, creatingList_expectHeadAndTail_0)
{
	list_t* list = CreateList();
	EXPECT_TRUE(!list->head);
	EXPECT_TRUE(!list->tail);
	free(list);
}

TEST(CreateNodeTest, creatingNodeFromChar)
{
	char str[] = "string";
	str_t* node = CreateNode(str);
	EXPECT_EQ(0, node->next);
	EXPECT_EQ(0, node->prev);
	EXPECT_TRUE(node->str, str);
	free(node);
}

TEST(PushFrontTest, pushingNewElementInFront_string2)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";
	
	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}
	
	list->head = (str_t*)malloc(sizeof(str_t));

	if (!list->head)
	{
		printf("Malloc error");
		exit(0);
	}
	
	list->tail = list->head;
	list->head->str = str1;
	list->head->next = NULL;
	list->head->prev = NULL;

	PushFront(list, str2);

	EXPECT_EQ(str2, list->head->str);
	EXPECT_TRUE(!list->head->prev);

	free(list->head->next);
	free(list->head);
	free(list);
}

TEST(PushFrontTest, pushingNewElementInFrontOfEmptyList_string)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string";
	if (list)
	{
		list->head = list->tail = NULL;
	}
	else
	{
		printf("Malloc error");
		exit(0);
	}

	PushFront(list, str1);
	EXPECT_EQ(str1, list->head->str);
	EXPECT_EQ(list->head, list->tail);

	free(list->head);
	free(list);

}

TEST(PopFrontTest, poppingElement_string1)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";
	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	str_t* node = (str_t*)malloc(sizeof(str_t));
	if (!node)
	{
		printf("Malloc error");
		free(list);
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));
	if (!list->head)
	{
		printf("Malloc error");
		free(node);
		free(list);
		exit(0);
	}

	list->head->str = str1;
	node->str = str2;
	list->head->next = node;
	list->head->prev = NULL;
	node->prev = list->head;
	node->next = NULL;
	list->tail = node;

	EXPECT_EQ(str1, PopFront(list));

	free(list->head);
	free(list);
}

TEST(PopFrontTest, checkingHeadAfterPoppingElement_string2)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";
	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	str_t* node = (str_t*)malloc(sizeof(str_t));
	if (!node)
	{
		printf("Malloc error");
		free(list);
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));
	if (!list->head)
	{
		printf("Malloc error");
		free(node);
		free(list);
		exit(0);
	}

	list->head->str = str1;
	node->str = str2;
	list->head->next = node;
	list->head->prev = NULL;
	node->prev = list->head;
	node->next = NULL;
	list->tail = node;

	PopFront(list);

	EXPECT_EQ(list->head->str, str2);

	free(list->head);
	free(list);
}

TEST(PopFrontTest, checkingHeadAndTailAfterPoppingLastElement_0)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";

	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));

	if (!list->head)
	{
		printf("Malloc error");
		free(list);
		exit(0);
	}

	list->tail = list->head;
	list->head->str = str1;
	list->head->next = NULL;
	list->head->prev = NULL;

	PopFront(list);
	EXPECT_TRUE(!list->head);
	EXPECT_TRUE(!list->tail);

	free(list);
}

TEST(PushBackTest, pushingNewElementInBack_string2)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";

	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));

	if (!list->head)
	{
		printf("Malloc error");
		exit(0);
	}

	list->tail = list->head;
	list->head->str = str1;
	list->head->next = NULL;
	list->head->prev = NULL;

	PushBack(list, str2);

	EXPECT_EQ(str2, list->tail->str);
	EXPECT_TRUE(!list->tail->next);

	free(list->head->next);
	free(list->head);
	free(list);
}

TEST(PushBackTest, pushingNewElementInBackOfEmptyList_string)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string";
	if (list)
	{
		list->head = list->tail = NULL;
	}
	else
	{
		printf("Malloc error");
		exit(0);
	}

	PushBack(list, str1);
	EXPECT_EQ(str1, list->head->str);
	EXPECT_EQ(list->head, list->tail);

	free(list->head);
	free(list);

}

TEST(InsBeforeTest, insertingNewElementInListBeforeOld_string3)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";
	char str3[] = "string3";
	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	str_t* node = (str_t*)malloc(sizeof(str_t));
	if (!node)
	{
		printf("Malloc error");
		free(list);
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));
	if (!list->head)
	{
		printf("Malloc error");
		free(node);
		free(list);
		exit(0);
	}

	list->head->str = str1;
	node->str = str2;
	list->head->next = node;
	list->head->prev = NULL;
	node->prev = list->head;
	node->next = NULL;
	list->tail = node;

	InsBefore(list, list->head->next, str3);
	EXPECT_EQ(str3, list->head->next->str);
	EXPECT_EQ(str3, list->tail->prev->str);

	free(list->head);
	free(list->tail->prev);
	free(list->tail);
	free(list);
}

TEST(InsBeforeTest, checkingHeadAfterInsertingBeforeFirstElement_string2)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";

	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));

	if (!list->head)
	{
		printf("Malloc error");
		free(list);
		exit(0);
	}

	list->tail = list->head;
	list->head->str = str1;
	list->head->next = NULL;
	list->head->prev = NULL;

	InsBefore(list, list->head, str2);
	EXPECT_EQ(str2, list->head->str);

	free(list->tail);
	free(list->head);
	free(list);
}

TEST(InsecSortListTest, sortingUnsortedList)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";
	char str3[] = "string3";
	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	str_t* node = (str_t*)malloc(sizeof(str_t));
	if (!node)
	{
		printf("Malloc error");
		free(list);
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));
	if (!list->head)
	{
		printf("Malloc error");
		free(node);
		free(list);
		exit(0);
	}
	
	list->tail = (str_t*)malloc(sizeof(str_t));
	if (!list->tail)
	{
		printf("Malloc error");
		free(list->head);
		free(node);
		free(list);
		exit(0);
	}

	list->head->str = str2;
	list->head->prev = NULL;
	list->head->next = node;
	node->str = str3;
	node->prev = list->head;
	node->next = list->tail;
	list->tail->str = str1;
	list->tail->next = NULL;
	list->tail->prev = node;

	InsecSortList(&list);

	EXPECT_TRUE(strcmp(list->head->str, list->head->next->str) < 0);
	EXPECT_TRUE(strcmp(list->head->next->str, list->tail->str) < 0);

	free(list->head);
	free(list->tail->prev);
	free(list->tail);
	free(list);
}

TEST(InsecSortListTest, sortingEmptyList)
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

	InsecSortList(&list);
	EXPECT_TRUE(!list->head);
	EXPECT_EQ(list->head, list->tail);
}

TEST(InsecSortListTest, sortingSortedList)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	char str1[] = "string1";
	char str2[] = "string2";
	char str3[] = "string3";
	if (!list)
	{
		printf("Malloc error");
		exit(0);
	}

	str_t* node = (str_t*)malloc(sizeof(str_t));
	if (!node)
	{
		printf("Malloc error");
		free(list);
		exit(0);
	}

	list->head = (str_t*)malloc(sizeof(str_t));
	if (!list->head)
	{
		printf("Malloc error");
		free(node);
		free(list);
		exit(0);
	}

	list->tail = (str_t*)malloc(sizeof(str_t));
	if (!list->tail)
	{
		printf("Malloc error");
		free(list->head);
		free(node);
		free(list);
		exit(0);
	}

	list->head->str = str1;
	list->head->prev = NULL;
	list->head->next = node;
	node->str = str2;
	node->prev = list->head;
	node->next = list->tail;
	list->tail->str = str3;
	list->tail->next = NULL;
	list->tail->prev = node;

	InsecSortList(&list);

	EXPECT_TRUE(strcmp(list->head->str, list->head->next->str) < 0);
	EXPECT_TRUE(strcmp(list->head->next->str, list->tail->str) < 0);

	free(list->head);
	free(list->tail->prev);
	free(list->tail);
	free(list);
}

int main(int argc, char* argv[]) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
