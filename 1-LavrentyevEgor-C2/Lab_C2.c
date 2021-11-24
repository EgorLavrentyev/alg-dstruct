#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)
#pragma warning (disable:6031)

typedef struct edge_t {            //edges
	int firstNode;
	int secondNode;
	struct edge_t* next;
} edge_t;

typedef struct {               //vertexes of the graph
	int weight;
	int isVisited;
} node_t;

typedef struct {       //list of edges
	edge_t* head;
} list_t;


int numEdges = 0;
int numNodes = 0;

node_t* nodes;    //an array of vertexes

list_t* CreateList(void)
{
	list_t* list = (list_t*)malloc(sizeof(list_t));
	if (!list)
	{
		fprintf(stderr, "Memory allocation error");
		exit(1);
	}
	list->head = NULL;
	return list;
}

void PushBack(list_t* list, int firstNode, int secondNode)
{


	edge_t* tmp = list->head;
	edge_t* edge = (edge_t*)malloc(sizeof(edge_t));
	if (!edge)
	{
		fprintf(stderr, "Memory allocation error");
		exit(1);
	}

	edge->firstNode = firstNode;
	edge->secondNode = secondNode;
	edge->next = NULL;

	if (!list->head)      //if list is empty
	{
		list->head = edge;
		return;
	}

	while (tmp->next)
	{
		tmp = tmp->next;
	}
	
	tmp->next = edge;
}

void DFS(list_t* list, int weight)
{
	printf("%d ", weight);
	nodes[weight].isVisited = 1;

	int minWeight = numNodes;

	edge_t* tmp = list->head;

	while (1)
	{
		tmp = list->head;  //rebuilding pointer 
		minWeight = numNodes;  //rebuilding variable

		for (int i = 0; i < numEdges; i++)    // looking for the edges that is incidental to the vertex "weight"
											  // and vertexes that is not visited
		{
			if (tmp->firstNode == weight && nodes[tmp->secondNode].isVisited == 0 && minWeight > tmp->secondNode)
			{
				minWeight = tmp->secondNode;
			}

			if (tmp->secondNode == weight && nodes[tmp->firstNode].isVisited == 0 && minWeight > tmp->firstNode)
			{
				minWeight = tmp->firstNode;
			}

			tmp = tmp->next;
		}

		if (minWeight != numNodes)   //if we haven't searched every vertex yet
		{
			DFS(list, minWeight);
		}
		else
		{
			break;
		}
	}
}

void DestroyList(list_t* list)
{
	if (!list)
	{
		exit(1);
	}
	edge_t* tmp = list->head;
	edge_t* next;

	do
	{

		next = tmp->next;
		free(tmp);
		tmp = next;

	} while (tmp->next);

	list->head = NULL;
	free(tmp);
	free(list);
}

int main(void)
{
	int firstNode, secondNode;
	list_t* list = CreateList();

	scanf("%d", &numNodes);
	nodes = (node_t*)malloc(sizeof(node_t) * numNodes);
	if (!nodes)
	{
		fprintf(stderr, "Memory allocation error");
		exit(1);
	}

	for (int i = 0; i < numNodes; i++)
	{
		nodes[i].weight = i;
		nodes[i].isVisited = 0;
	}

	while (scanf("%d %d", &firstNode, &secondNode) > 0)
	{
		PushBack(list, firstNode, secondNode);
		numEdges++;
	}

	DFS(list, 0);

	DestroyList(list);
	free(nodes);

	return 0;
}