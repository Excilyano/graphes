#ifndef UAL_REP
#define UAL_REP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Node.h"

typedef struct UndirectedAdjacenceList* pUndirectedAdjacenceList;

typedef struct UndirectedAdjacenceList {
	pNode* nodes;
} UndirectedAdjacenceList;

pUndirectedAdjacenceList ual_initEmptyList(int size);
int* ual_getNeighbours(pUndirectedAdjacenceList matrix, int node);
int ual_isEdge(pUndirectedAdjacenceList matrix, int x, int y);
int ual_removeEdge(pUndirectedAdjacenceList matrix, int x, int y);
int ual_addEdge(pUndirectedAdjacenceList matrix, int x, int y);
void ual_displayList(pUndirectedAdjacenceList matrix, int size);
void ual_freeList(pUndirectedAdjacenceList matrix, int size);
pUndirectedAdjacenceList ual_generateGraphData(int n, int m);
int ual_contains(pNode* nodeList, int size, int node);
void ual_removeFromList(pNode* nodeList, int size, int node);

#endif