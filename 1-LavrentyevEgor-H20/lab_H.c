#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "RBtree.h"
#include "BinaryTree.h"
#pragma warning(disable: 6011)
#pragma warning(disable: 4996)

#define ITERATIONS 1000

int main(void)
{

	//Setup();
	RBtree_t* RBtree = NULL;
	tree_t* Bintree = NULL;
	LARGE_INTEGER freq, t1, t2;
	double time1 = 0, time2 = 0, time3 = 0, time4 = 0;

	FILE* RB_ins = fopen("RB_ins.txt", "wt");
	FILE* RB_find = fopen("RB_find.txt", "wt");
	FILE* Bin_ins = fopen("Bin_ins.txt", "wt");
	FILE* Bin_find = fopen("Bin_find.txt", "wt");
	FILE* x = fopen("x.txt", "wt");

	QueryPerformanceFrequency(&freq);

	for (int i = 0; i < ITERATIONS; i++)
	{
		fprintf(x, "%d ", i+1);
		int element = rand() % (ITERATIONS * 10);
		for (int k = 0; k < 100; k++)
		{

			QueryPerformanceCounter(&t1);
			RBtree = Insert(RBtree, element);
			QueryPerformanceCounter(&t2);
			time1 += (float)(t2.QuadPart - t1.QuadPart) / freq.QuadPart;

			QueryPerformanceCounter(&t1);
			Find(RBtree, element);
			QueryPerformanceCounter(&t2);
			time2 += (float)(t2.QuadPart - t1.QuadPart) / freq.QuadPart;


			QueryPerformanceCounter(&t1);
			Bintree = Add(Bintree, element);
			QueryPerformanceCounter(&t2);
			time3 += (float)(t2.QuadPart - t1.QuadPart) / freq.QuadPart;

			QueryPerformanceCounter(&t1);
			Search(Bintree, element);
			QueryPerformanceCounter(&t2);
			time4 += (float)(t2.QuadPart - t1.QuadPart) / freq.QuadPart;

		}

		fprintf(RB_ins, "%.15lf ", time1 / 100.0);
		fprintf(RB_find, "%.15lf ", time2 / 100.0);
		fprintf(Bin_ins, "%.15lf ", time3 / 100.0);
		fprintf(Bin_find, "%.15lf ", time4 / 100.0);
	}

	fclose(RB_ins);
	fclose(RB_find);
	fclose(Bin_ins);
	fclose(Bin_find);
	fclose(x);
	Destroy(RBtree);
	DestroyTree(Bintree);

	return 0;
}