#ifndef EDGE
#define EDGE

#include "Node.h"

typedef struct Edge* pEdge;

typedef struct Edge {
	int value;
	pNode* nodes;
} Edge;

#endif