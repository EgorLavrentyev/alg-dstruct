#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int T_size, D, m, tmp;
int* T = NULL;

unsigned int isSolved(int* result)
{
	int* sums = malloc(sizeof(int) * m);
	for (int i = 0; i < m; i++)
	{
		sums[i] = 0;
	}

	for (int i = 0; i < T_size; i++)
	{
		int k = result[i];
		sums[k - 1] += T[i];
	}

	for (int i = 0; i < m; i++)
	{
		if (sums[i] > D)
			return 0;
	}
	return 1;
}

void TaskManager(int* result)  //
{
	int i = 1;
	for (int k = 0; k < T_size; k++)
	{
		result[k] = 1;
	}

	while (i > 0)
	{
		i = T_size - 1;
		while (result[i] < m)
		{
			if (isSolved(result) == 1)
			{
				return;
			}
			result[i]++;
		}

		if (isSolved(result) == 1)
		{
			return;
		}

		while (i > 0)
		{
			result[i--] = 1;

			if (result[i] != m)
			{
				result[i]++;
				break;
			}
		}
	}

	result[0] = 0;   //if we are here then there is no solution
}

int main(void)
{

	FILE* f_input = fopen("input.txt", "rt");
	FILE* f_output = fopen("output.txt", "wt");
	int i = 0;

	fscanf(f_input, "%d %d %d", &T_size, &D, &m);
	T = malloc(sizeof(int) * T_size);
	int* result = malloc(sizeof(int) * T_size);  //array containing the indexes of employees for each task 
	while (fscanf(f_input, "%d", &tmp) != EOF)
	{
		T[i] = tmp;
		i++;
	}

	TaskManager(result);

	if (result[0] == 0)
		fprintf(f_output, "0");
	else
		for (int i = 1; i <= m; i++)
		{
			for (int k = 0; k < T_size; k++)
			{
				if (result[k] == i)
					fprintf(f_output, "%d ", k + 1);
			}
				
			fprintf(f_output, "\n");
		}

	fclose(f_input);
	fclose(f_output);

	return 0;
}