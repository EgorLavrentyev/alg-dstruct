#pragma once
typedef struct tree_t {
	int key;
	struct tree_t* left;
	struct tree_t* right;
} tree_t;

tree_t* Add(tree_t* t, int element);
tree_t* Del1(tree_t** q, tree_t* p);
tree_t* Del(tree_t* t, int element);
void Search(tree_t* t, int element);
void DestroyTree(tree_t* t);
