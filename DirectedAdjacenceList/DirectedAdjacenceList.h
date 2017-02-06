#ifndef DAL_REP
#define DAL_REP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Node.h"

typedef struct DirectedAdjacenceList* pDirectedAdjacenceList;

typedef struct DirectedAdjacenceList {
	pNode* nodes;
} DirectedAdjacenceList;

pDirectedAdjacenceList dal_initEmptyList(int size);
int* dal_getPredecessors(pDirectedAdjacenceList list, int node);
int* dal_getSuccessors(pDirectedAdjacenceList list, int node);
int dal_isEdge(pDirectedAdjacenceList list, int x, int y);
int dal_removeEdge(pDirectedAdjacenceList list, int x, int y);
int dal_addEdge(pDirectedAdjacenceList list, int x, int y);
void dal_displayList(pDirectedAdjacenceList list, int size);
void dal_freeList(pDirectedAdjacenceList list, int size);
pDirectedAdjacenceList dal_generateGraphData(int n, int m);
pDirectedAdjacenceList dal_computeInverse(pDirectedAdjacenceList list, int size);
int dal_contains(pNode* nodeList, int size, int node);
void dal_removeFromList(pNode* nodeList, int size, int node);

#endif