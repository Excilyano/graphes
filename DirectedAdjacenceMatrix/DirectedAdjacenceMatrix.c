#include "DirectedAdjacenceMatrix.h"

/*
 * Finds the successors of a node
 * Each 1 of the line of the matrix corresponding to the node, represents the successor of this node
 * The first element of the returned array is the number of successors
 */
int* dam_getSuccessors(pDirectedAdjacenceMatrix matrix, int node, int size) {
	int i, cpt = 1;
	int* successors = malloc(sizeof(int));
	for (i = 0; i < size; i++) {
		if (matrix -> nodes[node][i] -> value > 0) {
			successors = realloc(successors, (cpt +1) * sizeof(int));
			successors[cpt++] = i;
		}
	}
	successors[0] = cpt -1;
	return successors;
}

/*
 * Finds the predecessors of a node
 * Each 1 of the column of the matrix corresponding to the node, represents the predecessor of this node
 */
int* dam_getPredecessors(pDirectedAdjacenceMatrix matrix, int node, int size) {
	int i, cpt = 1;
	int* predecessors = malloc(sizeof(int));
	for (i = 0; i < size; i++) {
		if (matrix -> nodes[i][node] -> value  > 0) {
			predecessors = realloc(predecessors, (cpt +1) * sizeof(int));
			predecessors[cpt++] = i;
		}
	}
	predecessors[0] = cpt -1;
	return predecessors;
}

/*
 * Return whether there is an edge between x and y
 */
int dam_isEdge(pDirectedAdjacenceMatrix matrix, int x, int y) {
	return matrix -> nodes[x][y] -> value != 0;
}

/*
 * Remove the edge between x and y
 */
int dam_removeEdge(pDirectedAdjacenceMatrix matrix, int x, int y) {
	if(matrix -> nodes[x][y] -> value == 1) {
		matrix -> nodes[x][y] -> value = 0;
		return 1;
	}
	return 0;
}

/*
 * Add an edge before x and y, if not already existing
 * No loop, so x must be different from y
 */
int dam_addEdge(pDirectedAdjacenceMatrix matrix, int x, int y, int value) {
	if (x != y && matrix -> nodes[x][y] -> value == 0) {
		matrix -> nodes[x][y] -> value = value;
		return 1;
	}
	return 0;
}

/*
 * Displays the given matrix
 */
void dam_displayMatrix(pDirectedAdjacenceMatrix matrix, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		printf("(");
		for(j = 0; j < size; j++) {
			printf("%d", matrix -> nodes[i][j] -> value);
			if (j != size -1) {
				printf(",");
			}
		}
		printf("),\n");
	}
}

/*
 * Free all allocations bound to the matrix given
 */
void dam_freeMatrix(pDirectedAdjacenceMatrix matrix, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			free(matrix -> nodes[i][j]);
		}
		free(matrix -> nodes[i]);
	}
	free(matrix -> nodes);
	free(matrix);
}

/*
 * Initializes and allocates memory for a square matrix of size "size".
 */
pDirectedAdjacenceMatrix dam_initEmptyMatrix(int size) {
	int i, j;
	pDirectedAdjacenceMatrix matrix = malloc(sizeof(DirectedAdjacenceMatrix));
	matrix -> nodes = malloc(size * sizeof(pNode*));
	for (i = 0; i < size; i++) {
		matrix -> nodes[i] = malloc(size * sizeof(pNode));
		for (j = 0; j < size; j++) {
			matrix -> nodes[i][j] = malloc(sizeof(Node));
			matrix -> nodes[i][j] -> value = 0;
		}
	}
	return matrix;
}

/*
 * Generates a random symectric matrix of size n, with m edges
 */
pDirectedAdjacenceMatrix dam_generateGraphData(int n, int m) {
	srand(time(NULL));
	int x, y;
	int value;
	pDirectedAdjacenceMatrix matrix = dam_initEmptyMatrix(n);
	while (m > 0) {
		x = rand() % n;
		y = rand() % n;
		value = rand() % 10;
		m -= dam_addEdge(matrix, x, y, value);
	}
	return matrix;
}

/*
 * Reverse the given matrix in a new instance
 */
pDirectedAdjacenceMatrix dam_computeInverse(pDirectedAdjacenceMatrix matrix, int size) {
	int i, j;
	pDirectedAdjacenceMatrix matrixCopy = dam_initEmptyMatrix(size);
	for (i = 1; i < size; i++) {
		for (j = 0; j < i; j++) {
			matrixCopy -> nodes[i][j] -> value = matrix -> nodes[j][i] -> value;
			matrixCopy -> nodes[j][i] -> value = matrix -> nodes[i][j] -> value;
		}		
	}
	return matrixCopy;
}