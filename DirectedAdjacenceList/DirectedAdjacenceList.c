#include "DirectedAdjacenceList.h"
/*
 * Finds the predecessors of a node
 */
int* dal_getPredecessors(pDirectedAdjacenceList list, int node) {
	int i;
	int* predecessors = malloc((list -> nodes[node] -> nbPredecessors +1) * sizeof(int));
	predecessors[0] = list -> nodes[node] -> nbPredecessors;
	for (i = 0; i < list -> nodes[node] -> nbPredecessors; i++) {
		predecessors[i+1] = list -> nodes[node] -> predecessors[i] -> value;
	}
	return predecessors;
}

/*
 * Finds the successors of a node
 */
int* dal_getSuccessors(pDirectedAdjacenceList list, int node) {
	int i;
	int* successors = malloc((list -> nodes[node] -> nbSuccessors +1) * sizeof(int));
	successors[0] = list -> nodes[node] -> nbSuccessors;
	for (i = 0; i < list -> nodes[node] -> nbSuccessors; i++) {
		successors[i+1] = list -> nodes[node] -> successors[i] -> value;
	}
	return successors;
}

/*
 * Return whether there is an edge between x and y
 */
int dal_isEdge(pDirectedAdjacenceList list, int x, int y) {
	return dal_contains(list -> nodes[x] -> successors, list -> nodes[x] -> nbSuccessors, y);
}

/*
 * Remove the edge between x and y
 */
int dal_removeEdge(pDirectedAdjacenceList list, int x, int y) {
	if (dal_contains(list -> nodes[x] -> successors, list -> nodes[x] -> nbSuccessors, y)) {
		list -> nodes[x] -> nbSuccessors--;
		list -> nodes[y] -> nbPredecessors--;
		dal_removeFromList(list -> nodes[x] -> successors, list -> nodes[x] -> nbSuccessors, y);
		dal_removeFromList(list -> nodes[y] -> predecessors, list -> nodes[y] -> nbPredecessors, x);
		list -> nodes[x] -> successors = realloc(list -> nodes[x] -> successors, list -> nodes[x] -> nbSuccessors * sizeof(pNode));
		list -> nodes[x] -> predecessors = realloc(list -> nodes[x] -> predecessors, list -> nodes[x] -> nbPredecessors * sizeof(pNode));
		return 1;
	}
	return 0;
}

/*
 * Add an edge before x and y, if not already existing
 * No loop, so x must be different from y
 */
int dal_addEdge(pDirectedAdjacenceList list, int x, int y) {
	if (!dal_contains(list -> nodes[x] -> successors, list -> nodes[x] -> nbSuccessors, y) && x != y) {
		list -> nodes[x] -> nbSuccessors++;
		list -> nodes[y] -> nbPredecessors++;
		list -> nodes[x] -> successors = realloc(list -> nodes[x] -> successors, list -> nodes[x] -> nbSuccessors * sizeof(pNode));
		list -> nodes[y] -> predecessors = realloc(list -> nodes[y] -> predecessors, list -> nodes[y] -> nbPredecessors * sizeof(pNode));
		list -> nodes[x] -> successors[list -> nodes[x] -> nbSuccessors -1] = list -> nodes[y];
		list -> nodes[y] -> predecessors[list -> nodes[y] -> nbPredecessors -1] = list -> nodes[x];
		return 1;
	}
	return 0;
}

/*
 * Displays the given list
 */
void dal_displayList(pDirectedAdjacenceList list, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		printf("[%d] : (", i);
		for(j = 0; j < list -> nodes[i] -> nbSuccessors; j++) {
			printf("%d", list -> nodes[i] -> successors[j] -> value);
			if (j < list -> nodes[i] -> nbSuccessors -1) {
				printf(",");
			}
		}
		printf("),\n");
	}
}

/*
 * Free all allocations bound to the list given
 */
void dal_freeList(pDirectedAdjacenceList list, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		free(list -> nodes[i] -> successors);
		free(list -> nodes[i] -> predecessors);
		free(list -> nodes[i]);
	}
	free(list -> nodes);
	free(list);
}

/*
 * Initializes and allocates memory for a list of size "size".
 */
pDirectedAdjacenceList dal_initEmptyList(int size) {
	int i;
	pDirectedAdjacenceList list = malloc(sizeof(DirectedAdjacenceList));
	list -> nodes = malloc(size * sizeof(pNode*));
	for (i = 0; i < size; i++) {
		list -> nodes[i] = malloc(sizeof(Node));
		list -> nodes[i] -> value = i;
		list -> nodes[i] -> nbSuccessors = 0;
		list -> nodes[i] -> nbPredecessors = 0;
		list -> nodes[i] -> successors = NULL;
		list -> nodes[i] -> predecessors = NULL;
	}
	return list;
}

/*
 * Generates a random list of size n, with m edges
 */
pDirectedAdjacenceList dal_generateGraphData(int n, int m) {
	srand(time(NULL));
	int x, y;
	int value;
	pDirectedAdjacenceList list = dal_initEmptyList(n);
	while (m > 0) {
		x = rand() % n;
		y = rand() % n;
		value = rand() % 10;
		m -= dal_addEdge(list, x, y);
	}
	return list;
}

int dal_contains(pNode* nodeList, int size, int node) {
	int i;
	for (i = 0; i < size; i++)
		if(nodeList[i] -> value == node) return 1;
	return 0;
}

void dal_removeFromList(pNode* nodeList, int size, int node) {
	int i = 0;
	while (i < size && nodeList[i] -> value != node) i++;
	while (i < size) {
		nodeList[i] = nodeList[i+1];
		i++;
	}
}

/*
 * Reverse the given list in a new instance
 */
pDirectedAdjacenceList dal_computeInverse(pDirectedAdjacenceList list, int size) {
	int i, j;
	pDirectedAdjacenceList listCopy = dal_initEmptyList(size);
	for (i = 0; i < size; i++) {
		for(j = 0; j < list -> nodes[i] -> nbSuccessors; j++) {
			dal_addEdge(listCopy, list -> nodes[i] -> successors[j] -> value, i);
		}
	}
	return listCopy;
}