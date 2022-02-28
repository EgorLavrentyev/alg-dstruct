#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "BinaryTree.h"

tree_t* Add(tree_t* t, int element)
{
	if (!t)
	{
		t = (tree_t*)malloc(sizeof(tree_t));
		t->key = element;
		t->left = t->right = NULL;
	}
	else
	{
		if (element < t->key)
		{
			t->left = Add(t->left, element);
		}
		else
		{
			if (element > t->key)
			{
				t->right = Add(t->right, element);

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
		}
		else
		{
			if (element > t->key)
			{
				t->right = Del(t->right, element);
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
	tree_t* cur = t;
	while (cur)
	{
		if (cur->key == element)
		{
			//puts("yes");
			return;
		}
		else
		{
			cur = cur->key > element ? cur->left : cur->right;
		}

	}

	//puts("no");
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