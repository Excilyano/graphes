#ifndef UIM_REP
#define UIM_REP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Edge.h"
#include "../Node.h"

typedef struct UndirectedIncidenceMatrix* pUndirectedIncidenceMatrix;

typedef struct UndirectedIncidenceMatrix {
	pEdge* edges;
} UndirectedIncidenceMatrix;

pUndirectedIncidenceMatrix uim_initEmptyMatrix(int nbNodes, int nbEdges);
int* uim_getNeighbours(pUndirectedIncidenceMatrix matrix, int node, int nbNodes, int nbEdges);
int uim_isEdge(pUndirectedIncidenceMatrix matrix, int x, int y, int nbEdges);
int uim_removeEdge(pUndirectedIncidenceMatrix matrix, int x, int y, int nbNodes, int nbEdges);
int uim_addEdge(pUndirectedIncidenceMatrix matrix, int x, int y, int nbNodes, int nbEdges);
void uim_displayMatrix(pUndirectedIncidenceMatrix matrix, int nbNodes, int nbEdges);
void uim_freeMatrix(pUndirectedIncidenceMatrix matrix, int nbNodes, int nbEdges);
pUndirectedIncidenceMatrix uim_generateGraphData(int n, int m);

#endif