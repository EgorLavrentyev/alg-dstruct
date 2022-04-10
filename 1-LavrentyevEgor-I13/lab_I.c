#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define T 5

typedef struct BPlusTree_t
{
	int isLeaf;  //1 - leaf, 0 - not leaf
	int key_num;
	int keys[2 * T];
	struct BPlusTree_t* parent;
	struct BPlusTree_t* children[2 * T + 1];
	struct BPlusTree_t* left;
	struct BPlusTree_t* right;
}BPlusTree_t;

BPlusTree_t* CreateTree(void)
{
	BPlusTree_t* tree = (BPlusTree_t*)malloc(sizeof(BPlusTree_t));
	if (!tree)
	{
		return NULL;
	}

	for (int i = 0; i <= 2 * T; i++)
	{
		tree->children[i] = NULL;
	}

	tree->isLeaf = 1;
	tree->key_num = 0;
	tree->parent = NULL;
	tree->left = NULL;
	tree->right = NULL;

	return tree;
}

void DestroyTree(BPlusTree_t* tree)
{
	if (!tree)
	{
		return;
	}

	if (tree->isLeaf == 0)
	{
		for (int i = 0; i <= tree->key_num; i++)
		{
			DestroyTree(tree->children[i]);
		}
	}

	free(tree);
	return;
}

BPlusTree_t* FindLeaf(BPlusTree_t* tree, int key)
{
	if (!tree)
	{
		return NULL;
	}

    int i = 0;
	BPlusTree_t* cur = tree;
	while (cur->isLeaf == 0)
	{
		for (i = 0; i <= cur->key_num; i++)
		{
			if ((i == cur->key_num) || (key < cur->keys[i]))
			{
				cur = cur->children[i];
				break;
			}
		}
	}

	return cur;
}

int Find(BPlusTree_t* tree, int key)
{
	BPlusTree_t* node = FindLeaf(tree, key);

	if (tree)
	{
		for (int i = 0; i < node->key_num; i++)
		{
			if (node->keys[i] == key)
			{
				return 1;
			}
		}
	}

	return 0;
}

int FindMinimum(BPlusTree_t* tree)
{
	for (int i = 0; i < 2 * T; i++)
	{
		if (tree->children[i])
		{
			return FindMinimum(tree->children[i]);
		}
	}

	return tree->keys[0];
}

void FixKeys(BPlusTree_t* node, int key)
{
	BPlusTree_t* parent = node->parent;
	int i = 0;

	while (parent)
	{
		while ((i < parent->key_num) && (parent->keys[i] < key))
		{
			i++;
		}

		if (i < parent->key_num)
		{
            int min = FindMinimum(parent->children[i + 1]);
			if (parent->keys[i] != min)
			{
				parent->keys[i] = min;
			}
		}

		parent = parent->parent;
	}

	return;
}

void Split(BPlusTree_t** tree, BPlusTree_t* node)
{
    int key = 0;
    int pos = 0;

    BPlusTree_t* new_tree = CreateTree();
    new_tree->isLeaf = 0;

    if (node->right != NULL)
    {
        new_tree->right = node->right;
        node->right->left = new_tree;
        node->right = new_tree;
        new_tree->left = node;
    }
    else
    {
        new_tree->right = node->right;
        node->right = new_tree;
        new_tree->left = node;
    }

    key = node->keys[T];
    new_tree->key_num = T - 1;
    node->key_num = T;

    for (int i = 0; i < new_tree->key_num; i++)
    {
        new_tree->keys[i] = node->keys[i + T + 1];
        new_tree->children[i] = node->children[i + T + 1];
        node->children[i + T + 1] = NULL;
    }

    new_tree->children[new_tree->key_num] = node->children[2 * T];
    node->children[2 * T] = NULL;

    if (node->isLeaf == 1)
    {
        new_tree->key_num++;
        new_tree->isLeaf = 1;

        for (int i = new_tree->key_num - 1; i >= 1; i--)
        {
            new_tree->keys[i] = new_tree->keys[i - 1];

        }

        new_tree->keys[0] = node->keys[T];
    }

    if (node == *(tree))
    {
        (*tree) = (BPlusTree_t*)malloc(sizeof(BPlusTree_t));

        if ((*tree) == NULL)
        {
            return;
        }

        (*tree)->keys[0] = key;
        (*tree)->children[0] = node;
        (*tree)->children[1] = new_tree;

        for (int i = 0; i < 2 * T + 1; i++)
        {
            if (new_tree->children[i] != NULL)
            {
                new_tree->children[i]->parent = new_tree;
            }

            if (node->children[i] != NULL)
            {
                node->children[i]->parent = node;
            }
        }

        (*tree)->isLeaf = 0;
        (*tree)->parent = NULL;
        (*tree)->left = NULL;
        (*tree)->right = NULL;

        for (int i = 2; i < 2 * T + 1; i++)
        {
            (*tree)->children[i] = NULL;
        }

        (*tree)->key_num = 1;
        node->parent = (*tree);
        new_tree->parent = (*tree);
    }
    else
    {
        new_tree->parent = node->parent;

        while ((pos < node->parent->key_num) && (node->parent->keys[pos] < key))
        {
            pos++;
        }

        for (int i = node->parent->key_num; i >= pos; i--)
        {
            node->parent->keys[i] = node->parent->keys[i - 1];
        }

        for (int i = node->parent->key_num + 1; i >= pos + 2; i--)
        {
            node->parent->children[i] = node->parent->children[i - 1];
        }

        for (int i = 0; i < 2 * T; i++)
        {
            if (new_tree->children[i] != NULL)
            {
                new_tree->children[i]->parent = new_tree;
            }
        }

        node->parent->keys[pos] = key;
        node->parent->children[pos + 1] = new_tree;
        node->parent->key_num++;

        if (node->parent->key_num == 2 * T)
        {
            Split(tree, node->parent);
        }
    }

    return;
}

void Add(BPlusTree_t** tree, int key)
{
    BPlusTree_t* leaf = FindLeaf((*tree), key);

    if (!leaf)
    {
        return;
    }

    int pos = 0;

    for (int i = 0; i < leaf->key_num; i++)
    {
        if (leaf->keys[i] == key)
        {
            return;
        }
    }

    while (pos < leaf->key_num && leaf->keys[pos] < key)
    {
        ++pos;
    }

    for (int i = leaf->key_num; i >= pos + 1; i--)
    {
        leaf->keys[i] = leaf->keys[i - 1];
    }

    leaf->keys[pos] = key;
    leaf->key_num++;

    if (leaf->key_num == 2 * T)
    {
        Split(tree, leaf);
    }

    return;
}

void DeleteInNode(BPlusTree_t* tree, BPlusTree_t* node, int key);
void Merge(BPlusTree_t* tree, BPlusTree_t* node, int key)
{
    BPlusTree_t* parent = node->parent;
    BPlusTree_t* right = node->right;
    BPlusTree_t* left = node->left;
    BPlusTree_t* tmp = NULL;

    if (right && (right->parent == node->parent))
    {
        for (int i = 0; i < right->key_num; i++)
        {
            node->keys[node->key_num] = right->keys[i];
            node->children[node->key_num + 1] = right->children[i];

            if (right->children[i] != NULL)
            {
                right->children[i]->parent = node;
            }

            node->key_num++;
        }

        node->children[node->key_num + 1] = right->children[right->key_num];

        if (right->children[right->key_num])
        {
            right->children[right->key_num]->parent = node;
        }

        if (right->right)
        {
            right->right->left = node;
        }

        node->right = right->right;

        DeleteInNode(tree, node->parent, FindMinimum(right));
        FixKeys(node, key);
    }
    else
    {
        for (int i = 0; i < node->key_num; i++)
        {
            left->keys[left->key_num] = node->keys[i];
            left->children[left->key_num + 1] = node->children[i];

            if (node->children[i] != NULL)
            {
                node->children[i]->parent = left;
            }

            left->key_num++;
        }

        left->children[left->key_num + 1] = node->children[node->key_num];

        if (node->children[node->key_num])
        {
            node->children[node->key_num]->parent = left;

        }

        left->right = node->right;

        if (node->right)
        {
            node->right->left = left;
        }

        DeleteInNode(tree, left->parent, FindMinimum(node));
        FixKeys(left, key);
    }
    return;
}

void DeleteInNode(BPlusTree_t* tree, BPlusTree_t* node, int key)
{
    int i = 0;
    int pos = 0;

    while ((pos < node->key_num) && (node->keys[pos] < key))
    {
        pos++;
    }
    for (int i = pos; i < node->key_num; i++)
    {
        node->keys[i] = node->keys[i + 1];
    }
    for (int i = pos + 1; i <= node->key_num; i++)
    {
        node->children[i] = node->children[i + 1];
    }
    for (int i = node->key_num + 1; i < 2 * T + 1; i++)
    {
        *(node->children + i) = NULL;
    }

    node->key_num--;

    if (node == tree)
    {
        for (int i = 0; i < 2 * T + 1; i++)
        {
            if (node->children[i] != NULL)
            {
                if (node->children[i]->key_num == 0)
                {
                    node->children[i] = NULL;
                }
            }
        }

        if ((tree->key_num == 0) && tree->children[0])
        {
            tree = tree->children[0];
        }

        return;
    }

    if (node->key_num >= 1)
    {
        FixKeys(node, key);
    }
    else
    {
        if (node->key_num < T - 1)
        {
            BPlusTree_t* right = node->right;
            BPlusTree_t* left = node->left;

            if (left && (left->key_num > (T - 1)) && (left->parent == node->parent))
            {
                left->key_num--;
                node->key_num++;

                for (int i = 1; i < node->key_num; i++)
                {
                    node->keys[i] = node->keys[i - 1];
                    node->children[i] = node->children[i - 1];
                }

                node->children[node->key_num] = node->children[node->key_num - 1];
                node->keys[0] = left->keys[left->key_num];
                node->children[0] = left->children[left->key_num + 1];
                left->children[left->key_num + 1] = NULL;

                if (node->children[0])
                {
                    node->children[0]->parent = node;
                }

                FixKeys(node, key);
            }
            else
            {
                if (right && (right->key_num > (T - 1)) && (right->parent == node->parent))
                {
                    node->key_num++;
                    node->keys[node->key_num - 1] = right->keys[0];
                    node->children[node->key_num] = right->children[0];

                    if (node->children[node->key_num])
                    {
                        node->children[node->key_num]->parent = node;
                    }

                    for (int i = 0; i < right->key_num; i++)
                    {
                        right->keys[i] = right->keys[i + 1];
                        right->children[i] = right->children[i + 1];
                    }

                    for (int i = 0; i < 2 * T; i++)
                    {
                        if ((right->children[i] == right->children[i + 1]) && right->children[i])
                        {
                            right->children[i + 1] = NULL;
                            break;
                        }
                    }

                    right->key_num--;
                    FixKeys(node, key);
                }
                else
                {
                    Merge(tree, node, key);
                }
            }
        }
    }

    return;
}

void Delete(BPlusTree_t* tree, int key)
{
    if (!tree)
    {
        return;
    }

    if (Find(tree, key) == 0)
    {
        return;
    }

    BPlusTree_t* leaf = FindLeaf(tree, key);
    DeleteInNode(tree, leaf, key);

    return;
}

int main(void)
{
    char sym;
    int key;
    BPlusTree_t* tree = CreateTree();

    while (fscanf(stdin, "%c %d", &sym, &key) > 0)
    {
        if (sym == 'a')
        {
            Add(&tree, key);
        }

        if (sym == 'r')
        {
            Delete(tree, key);
        }

        if (sym == 'f')
        {
            if (Find(tree, key) == 1)
            {
                printf("yes\n");
            }
            else
            {
                printf("no\n");
            }
        }
    }

    DestroyTree(tree);

    return 0;
}