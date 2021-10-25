#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memallocator.h"
#include <Windows.h>
#pragma warning (disable:4996)

#define ITERATIONS 1000
#define MAX_SIZE 100

int main(void)
{
	FILE* f1 = fopen("my_allocator.txt", "w");
	size_t size = (MAX_SIZE + memgetblocksize()) * ITERATIONS;
	LARGE_INTEGER t1, t2, freq;
	double time;
	double* results = (double*)malloc(ITERATIONS * sizeof(double));
	char** pointers = (char**)malloc(ITERATIONS * sizeof(char*));
	void* mem = malloc(size);

	meminit(mem, size);
	QueryPerformanceFrequency(&freq);

	for (int i = 0; i < ITERATIONS; i++) 
	{
		QueryPerformanceCounter(&t1);
		for (int k = 0; k < i; k++) 
		{
			pointers[k] = (char*)memalloc((int)rand() % MAX_SIZE);
		}

		for (int k = 0; k < i; k++) 
		{
			memfree(pointers[k]);
		}

		QueryPerformanceCounter(&t2);
		time = (float)(t2.QuadPart - t1.QuadPart) / freq.QuadPart;
		results[i] = time;
	}

	for (int i = 0; i < ITERATIONS; i++) 
	{
		fprintf(f1, "%lf ", results[i]);
	}

	fclose(f1);

	f1 = fopen("sys_allocator.txt", "w");
	for (int i = 0; i < ITERATIONS; i++) 
	{
		QueryPerformanceCounter(&t1);
		for (int k = 0; k < i; k++) 
		{
			pointers[k] = (char*)malloc((int)rand() % MAX_SIZE);
		}

		for (int k = 0; k < i; k++) 
		{
			free(pointers[k]);
		}

		QueryPerformanceCounter(&t2);
		time = (float)(t2.QuadPart - t1.QuadPart) / freq.QuadPart;
		results[i] = time;
	}

	for (int i = 0; i < ITERATIONS; i++) 
	{
		fprintf(f1, "%lf ", results[i]);
	}

	fclose(f1);

	free(results);
	free(pointers);
	free(mem);

	return 0;
}
