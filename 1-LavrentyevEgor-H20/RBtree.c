#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "RBtree.h"
#pragma warning(disable: 6011)
#pragma warning(disable: 4996)

int x = 1, y = 1;

RBtree_t* LeftRotate(RBtree_t* root, RBtree_t* x)
{
	if (!x)
	{
		return 0;
	}

	RBtree_t* y = NULL;
	if (x->right)
	{
		y = x->right;
		x->right = y->left;
		if (y->left)
		{
			y->left->parent = x;
		}
	}

	if (y)
	{
		y->parent = x->parent;
		y->left = x;
	}

	if (x->parent)
	{
		if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	else
	{
		root = y;
	}

	x->parent = y;
	return root;
}

RBtree_t* RightRotate(RBtree_t* root, RBtree_t* x)
{
	if (!x)
	{
		return 0;
	}

	RBtree_t* y = NULL;
	if (x->left)
	{
		y = x->left;
		x->left = y->right;
		if (y->right)
		{
			y->right->parent = x;
		}
	}

	if (y)
	{
		y->parent = x->parent;
		y->right = x;
	}

	if (x->parent)
	{
		if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
	}
	else
	{
		root = y;
	}

	x->parent = y;
	return root;
}

RBtree_t* InsertFixup(RBtree_t* root, RBtree_t* x)
{
	while (x != root && x->parent->color == RED)
	{
		if (x->parent == x->parent->parent->left)
		{
			RBtree_t* y = x->parent->parent->right;
			if (y != NULL && y->color == RED)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->right)
				{
					x = x->parent;
					root = LeftRotate(root, x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				root = RightRotate(root, x->parent->parent);
			}

		}
		else
		{
			RBtree_t* y = x->parent->parent->left;
			if (y != NULL && y->color == RED)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->left)
				{
					x = x->parent;
					root = RightRotate(root, x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				root = LeftRotate(root, x->parent->parent);
			}
		}
	}

	root->color = BLACK;
	return root;
}

RBtree_t* Insert(RBtree_t* root, int data)
{
	if (!root)
	{
		root = (RBtree_t*)malloc(sizeof(RBtree_t));
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->color = BLACK;
	}
	else
	{
		RBtree_t* cur = root;
		RBtree_t* parent = NULL;
		while (cur)
		{
			if (cur->data == data)
			{
				return root;
			}
			parent = cur;
			cur = cur->data > data ? cur->left : cur->right;
		}

		RBtree_t* node = (RBtree_t*)malloc(sizeof(RBtree_t));
		if (!node)
		{
			return 0;
		}

		node->data = data;
		node->left = NULL;
		node->right = NULL;
		node->parent = parent;
		node->color = RED;

		if (!parent)
		{
			root = node;
		}
		else
		{
			if (data < parent->data)
			{
				parent->left = node;
			}
			else
			{
				parent->right = node;
			}
		}
		root = InsertFixup(root, node);
	}

	return root;
}

RBtree_t* DeleteFixup(RBtree_t* root, RBtree_t* x)
{
	while (x != root && x->color == BLACK)
	{
		if (x->parent->right != NULL && x == x->parent->left)
		{
			RBtree_t* y = x->parent->right;
			if (y->color == RED)
			{
				y->color = BLACK;
				x->parent->color = RED;
				root = LeftRotate(root, x->parent);
				y = x->parent->right;
			}

			if (y->left != NULL && y->right != NULL && y->left->color == BLACK && y->right->color == BLACK)
			{
				y->color = RED;
				x = x->parent;
			}
			else
			{
				if (y->left != NULL && y->right != NULL && y->right->color == BLACK)
				{
					y->left->color = BLACK;
					y->color = RED;
					root = RightRotate(root, y);
					y = x->parent->right;
				}

				if (y->right != NULL)
				{
					y->color = x->parent->color;
					x->parent->color = BLACK;
					y->right->color = BLACK;
					root = LeftRotate(root, x->parent);
				}
				x = root;
			}
		}
		else if (x->parent->left)
		{
			RBtree_t* y = x->parent->left;
			if (y->color == RED)
			{
				y->color = BLACK;
				x->parent->color = RED;
				root = RightRotate(root, x->parent);
				y = x->parent->left;
			}

			if (y->left != NULL && y->right != NULL && y->right->color == BLACK && y->left->color == BLACK)
			{
				y->color = RED;
				x = x->parent;
			}
			else
			{
				if (y->left != NULL && y->right != NULL && y->left->color == BLACK)
				{
					y->right->color = BLACK;
					y->color = RED;
					root = LeftRotate(root, y);
					y = x->parent->left;
				}

				if (y->left)
				{
					y->color = x->parent->color;
					x->parent->color = BLACK;
					y->left->color = BLACK;
					root = RightRotate(root, x->parent);
				}

				x = root;
			}
		}
	}

	x->color = BLACK;
	return root;
}

RBtree_t* Delete(RBtree_t* root, int data)
{
	RBtree_t* cur = root;
	RBtree_t* x = NULL;
	while (cur)
	{
		if (data == cur->data)
		{
			x = cur;
			break;
		}
		else
		{
			cur = cur->data > data ? cur->left : cur->right;
		}
	}

	if (!x)
	{
		return root;
	}

	RBtree_t* y = NULL;
	if (x->left == NULL || x->right == NULL)
	{
		y = x;
	}
	else
	{
		y = x->right;
		while (y->left)
		{
			y = y->left;
		}
	}

	RBtree_t* y_child = NULL;
	if (y->left)
	{
		y_child = y->left;
	}
	else
	{
		y_child = y->right;
	}

	if (y_child)
	{
		y_child->parent = y->parent;
	}

	if (y->parent)
	{
		if (y == y->parent->left)
		{
			y->parent->left = y_child;
		}
		else
		{
			y->parent->right = y_child;
		}
	}
	else
	{
		root = y_child;
	}

	if (y != x)
	{
		x->data = y->data;
	}
	if (y->color == BLACK && y_child != NULL) {
		root = DeleteFixup(root, y_child);
	}
	if (y != NULL) {
		free(y);
	}

	return root;
}

void Destroy(RBtree_t* t)
{
	if (t)
	{
		Destroy(t->left);
		Destroy(t->right);
		free(t);
	}
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void PrintTree(RBtree_t* t, int y)
{
	if (t)
	{
		PrintTree(t->left, y + 2);
		gotoxy(x, y);
		printf("%d(%s)", t->data, t->color == RED ? "RED" : "BLACK");
		x += 6;
		PrintTree(t->right, y + 2);
	}
}

void Find(RBtree_t* root, int data)
{
	RBtree_t* cur = root;
	while (cur)
	{
		if (cur->data == data)
		{
			//puts("yes");
			return;
		}
		else
		{
			cur = cur->data > data ? cur->left : cur->right;
		}

	}

	//puts("no");
}

void Setup()
{
	RBtree_t* tree = NULL;
	int element;
	char action;
	int n = 1;
	while (scanf("%c %d", &action, &element) >= 1)
	{

		switch (action)
		{
		case 'a':
			tree = Insert(tree, element);
			y++;
			break;
		case 'r':
			tree = Delete(tree, element);
			y++;
			break;
		case 'f':
			Find(tree, element);
			y++;
			break;
		case 'q':
			Destroy(tree);
			y++;
			return;
		case 'p':
			x = 20;
			y++;
			PrintTree(tree, y);
			y += 10;
		}

	}
	Destroy(tree);
}