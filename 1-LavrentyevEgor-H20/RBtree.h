#pragma once
typedef enum {
	RED,
	BLACK
}color_t;

typedef struct RBtree_t {
	int data;
	struct RBtree_t* left;
	struct RBtree_t* right;
	struct RBtree_t* parent;
	color_t color;
}RBtree_t;

RBtree_t* LeftRotate(RBtree_t* root, RBtree_t* x);
RBtree_t* RightRotate(RBtree_t* root, RBtree_t* x);
RBtree_t* InsertFixup(RBtree_t* root, RBtree_t* x);
RBtree_t* Insert(RBtree_t* root, int data);
RBtree_t* DeleteFixup(RBtree_t* root, RBtree_t* x);
RBtree_t* Delete(RBtree_t* root, int data);
void Destroy(RBtree_t* t);
void gotoxy(int x, int y);
void PrintTree(RBtree_t* t, int y);
void Find(RBtree_t* root, int data);
void Setup();