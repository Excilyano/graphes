#include "UndirectedAdjacenceList.h"
/*
 * Finds the neighbours of a node by concatening predecessors and successors
 */
int* ual_getNeighbours(pUndirectedAdjacenceList list, int node) {
	int i;
	int* neighbours = malloc((list -> nodes[node] -> nbNeighbours +1) * sizeof(int));
	neighbours[0] = list -> nodes[node] -> nbNeighbours;
	for (i = 0; i < list -> nodes[node] -> nbNeighbours; i++) {
		neighbours[i+1] = list -> nodes[node] -> neighbours[i] -> value;
	}
	return neighbours;
}

/*
 * Return whether there is an edge between x and y
 */
int ual_isEdge(pUndirectedAdjacenceList list, int x, int y) {
	return ual_contains(list -> nodes[x] -> neighbours, list -> nodes[x] -> nbNeighbours, y);
}

/*
 * Remove the edge between x and y
 */
int ual_removeEdge(pUndirectedAdjacenceList list, int x, int y) {
	if (ual_contains(list -> nodes[x] -> neighbours, list -> nodes[x] -> nbNeighbours, y)) {
		list -> nodes[x] -> nbNeighbours--;
		list -> nodes[y] -> nbNeighbours--;
		ual_removeFromList(list -> nodes[x] -> neighbours, list -> nodes[x] -> nbNeighbours, y);
		ual_removeFromList(list -> nodes[y] -> neighbours, list -> nodes[y] -> nbNeighbours, x);
		list -> nodes[x] -> neighbours = realloc(list -> nodes[x] -> neighbours, list -> nodes[x] -> nbNeighbours * sizeof(pNode));
		list -> nodes[y] -> neighbours = realloc(list -> nodes[y] -> neighbours, list -> nodes[y] -> nbNeighbours * sizeof(pNode));
		return 1;
	}
	return 0;
}

/*
 * Add an edge before x and y, if not already existing
 * No loop, so x must be different from y
 */
int ual_addEdge(pUndirectedAdjacenceList list, int x, int y) {
	if (!ual_contains(list -> nodes[x] -> neighbours, list -> nodes[x] -> nbNeighbours, y) && x != y) {
		list -> nodes[x] -> nbNeighbours++;
		list -> nodes[y] -> nbNeighbours++;
		list -> nodes[x] -> neighbours = realloc(list -> nodes[x] -> neighbours, list -> nodes[x] -> nbNeighbours * sizeof(pNode));
		list -> nodes[y] -> neighbours = realloc(list -> nodes[y] -> neighbours, list -> nodes[y] -> nbNeighbours * sizeof(pNode));
		list -> nodes[x] -> neighbours[list -> nodes[x] -> nbNeighbours -1] = list -> nodes[y];
		list -> nodes[y] -> neighbours[list -> nodes[y] -> nbNeighbours -1] = list -> nodes[x];
		return 1;
	}
	return 0;
}

/*
 * Displays the given list
 */
void ual_displayList(pUndirectedAdjacenceList list, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		printf("[%d] : (", i);
		for(j = 0; j < list -> nodes[i] -> nbNeighbours; j++) {
			printf("%d", list -> nodes[i] -> neighbours[j] -> value);
			if (j < list -> nodes[i] -> nbNeighbours -1) {
				printf(",");
			}
		}
		printf("),\n");
	}
}

/*
 * Free all allocations bound to the list given
 */
void ual_freeList(pUndirectedAdjacenceList list, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		free(list -> nodes[i] -> neighbours);
		free(list -> nodes[i]);
	}
	free(list -> nodes);
	free(list);
}

/*
 * Initializes and allocates memory for a list of size "size".
 */
pUndirectedAdjacenceList ual_initEmptylist(int size) {
	int i;
	pUndirectedAdjacenceList list = malloc(sizeof(UndirectedAdjacenceList));
	list -> nodes = malloc(size * sizeof(pNode*));
	for (i = 0; i < size; i++) {
		list -> nodes[i] = malloc(sizeof(Node));
		list -> nodes[i] -> value = i;
		list -> nodes[i] -> nbNeighbours = 0;
		list -> nodes[i] -> neighbours = malloc(sizeof(void));
	}
	return list;
}

/*
 * Generates a random list of size n, with m edges
 */
pUndirectedAdjacenceList ual_generateGraphData(int n, int m) {
	srand(time(NULL));
	int x, y;
	pUndirectedAdjacenceList list = ual_initEmptylist(n);
	while (m > 0) {
		x = rand() % n;
		y = rand() % n;
		m -= ual_addEdge(list, x, y);
	}
	return list;
}

int ual_contains(pNode* nodeList, int size, int node) {
	int i;
	for (i = 0; i < size; i++)
		if(nodeList[i] -> value == node) return 1;
	return 0;
}

void ual_removeFromList(pNode* nodeList, int size, int node) {
	int i = 0;
	while (i < size && nodeList[i] -> value != node) i++;
	while (i < size) {
		nodeList[i] = nodeList[i+1];
		i++;
	}
}