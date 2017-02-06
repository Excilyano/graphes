#ifndef UAM_REP
#define UAM_REP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Node.h"

typedef struct UndirectedAdjacenceMatrix* pUndirectedAdjacenceMatrix;

typedef struct UndirectedAdjacenceMatrix {
	pNode** nodes;
} UndirectedAdjacenceMatrix;

pUndirectedAdjacenceMatrix uam_initEmptyMatrix(int size);
int* uam_getNeighbours(pUndirectedAdjacenceMatrix matrix, int node, int size);
int uam_isEdge(pUndirectedAdjacenceMatrix matrix, int x, int y);
int uam_removeEdge(pUndirectedAdjacenceMatrix matrix, int x, int y);
int uam_addEdge(pUndirectedAdjacenceMatrix matrix, int x, int y, int value);
void uam_displayMatrix(pUndirectedAdjacenceMatrix matrix, int size);
void uam_freeMatrix(pUndirectedAdjacenceMatrix matrix, int size);
pUndirectedAdjacenceMatrix uam_generateGraphData(int n, int m);

void uam_deepPath(pUndirectedAdjacenceMatrix matrix, int v);
void uam_largePath(pUndirectedAdjacenceMatrix matrix, int v);
void uam_isConnex(pUndirectedAdjacenceMatrix matrix);
void uam_isStronglyConnex(pUndirectedAdjacenceMatrix);

#endif