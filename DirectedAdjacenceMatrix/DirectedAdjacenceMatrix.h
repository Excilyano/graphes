#ifndef DAM_REP
#define DAM_REP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Node.h"

typedef struct DirectedAdjacenceMatrix* pDirectedAdjacenceMatrix;

typedef struct DirectedAdjacenceMatrix {
	pNode** nodes;
} DirectedAdjacenceMatrix;

pDirectedAdjacenceMatrix dam_initEmptyMatrix(int size);
int* dam_getSuccessors(pDirectedAdjacenceMatrix matrix, int node, int size);
int* dam_getPredecessors(pDirectedAdjacenceMatrix matrix, int node, int size);
int dam_isEdge(pDirectedAdjacenceMatrix matrix, int x, int y);
int dam_removeEdge(pDirectedAdjacenceMatrix matrix, int x, int y);
int dam_addEdge(pDirectedAdjacenceMatrix matrix, int x, int y, int value);
void dam_displayMatrix(pDirectedAdjacenceMatrix matrix, int size);
void dam_freeMatrix(pDirectedAdjacenceMatrix matrix, int size);
pDirectedAdjacenceMatrix dam_generateGraphData(int n, int m);
pDirectedAdjacenceMatrix dam_computeInverse(pDirectedAdjacenceMatrix, int size);

#endif