#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int x = 1, y = 1;

typedef struct tree_t {
	int key;
	int height_diff;
	struct tree_t* left;
	struct tree_t* right;
} tree_t;


tree_t* Add(tree_t* t, int element)
{
	if (!t)
	{
		t = (tree_t*)malloc(sizeof(tree_t));
		t->key = element;
		t->left = t->right = NULL;
		t->height_diff = 0;
	}
	else
	{
		if (element < t->key)
		{
			t->left = Add(t->left, element);
			t->height_diff = GetHeightDiff(t);
		}
		else
		{
			if (element > t->key)
			{
				t->right = Add(t->right, element);
				t->height_diff = GetHeightDiff(t);

			}
			else
			{
				printf("Such an element already exists in the tree ");
			}
		}
	}
	return t;
}

tree_t* Del1(tree_t** q, tree_t* p)
{
	tree_t* r;
	if ((*q)->right)
	{
		r = Del1(&(*q)->right, p);
	}
	else
	{
		p->key = (*q)->key;
		r = *q;
		*q = (*q)->left;
	}
	return r;
}

tree_t* Del(tree_t* t, int element)
{
	tree_t* p;

	if (t)
	{
		if (element < t->key)
		{
			t->left = Del(t->left, element);
			t->height_diff = GetHeightDiff(t);
		}
		else
		{
			if (element > t->key)
			{
				t->right = Del(t->right, element);
				t->height_diff = GetHeightDiff(t);
			}
			else
			{
				p = t;
				if (!p->right)
				{
					t = p->left;
				}
				else
				{
					if (!p->left)
					{
						t = p->right;
					}
					else
					{
						p = Del1(&p->left, p);
						p->height_diff = GetHeightDiff(p);
					}

					free(p);
				}
			}
		}
	}
	return t;
}

void Search(tree_t* t, int element)
{
	if (!t)
		printf("Element %d - not found", element);
	else
		if (element == t->key)
			printf("Element %d - found", element);
		else if (element > t->key)
			Search(t->right, element);
		else
			Search(t->left, element);
}

int CountHeight(tree_t* node)
{
	int l = 0, r = 0, h = 0;
	
	if (!node)
		return 0;
	else
	{
		if (!node->left && !node->right)
			return 1;
		else
		{
			l = CountHeight(node->left);
			r = CountHeight(node->right);
			if (r > l)
				h = r + 1;
			else
				h = l + 1;
			return h;
		}
	}
}

int GetHeightDiff(tree_t* node)
{
	return CountHeight(node->left) - CountHeight(node->right);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void PrintTree(tree_t* t, int y)
{
	if (t)
	{
		PrintTree(t->left, y + 1);
		gotoxy(x, y);
		printf("%d(%d)", t->key, t->height_diff);
		x += 4;
		PrintTree(t->right, y + 1);
	}
}

void DestroyTree(tree_t* t)
{
	if (t)
	{
		DestroyTree(t->left);
		DestroyTree(t->right);
		free(t);
	}
}

int main(void)
{
	tree_t* tree = NULL;
	tree = Add(tree, 20);
	tree = Add(tree, 10);
	tree = Add(tree, 26);
	tree = Add(tree, 5);
	tree = Add(tree, 11);
	tree = Add(tree, 25);
	tree = Add(tree, 4);
	tree = Add(tree, 30);
	tree = Add(tree, 3);
	PrintTree(tree, y);
	printf("\n\n\n\n");

	tree = Del(tree, 20);
	tree = Del(tree, 5);
	x = 1;
	PrintTree(tree, y + 7);
	printf("\n\n\n\n");

	Search(tree, 30);
	printf("\n\n");
	Search(tree, 56);
	printf("\n\n");

	return 0;
}