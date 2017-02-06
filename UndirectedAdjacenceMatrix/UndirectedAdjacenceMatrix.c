#include "UndirectedAdjacenceMatrix.h"
/*
 * Finds the neighbours of a node by concatening predecessors and successors
 */
int* uam_getNeighbours(pUndirectedAdjacenceMatrix matrix, int node, int size) {
	int i, cpt = 1;
	int* neighbours = malloc(sizeof(int));
	for (i = 0; i < size; i++) {
		if (matrix -> nodes[i][node] -> value == 1 || matrix -> nodes[node][i] -> value == 1) {
			neighbours = realloc(neighbours, (cpt +1) * sizeof(int));
			neighbours[cpt++] = i;
		}
	}
	neighbours[0] = cpt -1;
	return neighbours;
}

/*
 * Return whether there is an edge between x and y
 */
int uam_isEdge(pUndirectedAdjacenceMatrix matrix, int x, int y) {
	return matrix -> nodes[x][y] -> value != 0;
}

/*
 * Remove the edge between x and y
 */
int uam_removeEdge(pUndirectedAdjacenceMatrix matrix, int x, int y) {
	if(matrix -> nodes[x][y] -> value == 1) {
		matrix -> nodes[x][y] -> value = 0;
		matrix -> nodes[y][x] -> value = 0;
		return 1;
	}
	return 0;
}

/*
 * Add an edge before x and y, if not already existing
 * No loop, so x must be different from y
 */
int uam_addEdge(pUndirectedAdjacenceMatrix matrix, int x, int y, int value) {
	if (x != y && matrix -> nodes[x][y] -> value == 0) {
		matrix -> nodes[x][y] -> value = value;
		matrix -> nodes[y][x] -> value = value;
		return 1;
	}
	return 0;
}

/*
 * Displays the given matrix
 */
void uam_displayMatrix(pUndirectedAdjacenceMatrix matrix, int size) {
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
void uam_freeMatrix(pUndirectedAdjacenceMatrix matrix, int size) {
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
pUndirectedAdjacenceMatrix uam_initEmptyMatrix(int size) {
	int i, j;
	pUndirectedAdjacenceMatrix matrix = malloc(sizeof(UndirectedAdjacenceMatrix));
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
pUndirectedAdjacenceMatrix uam_generateGraphData(int n, int m) {
	srand(time(NULL));
	int x, y;
	int value;
	pUndirectedAdjacenceMatrix matrix = uam_initEmptyMatrix(n);
	while (m > 0) {
		x = rand() % n;
		y = rand() % n;
		value = rand() % 10;
		m -= uam_addEdge(matrix, x, y, value);
	}
	return matrix;
}

/*
 * Check the connexity of a graph
 */
void uam_isConnex(pUndirectedAdjacenceMatrix matrix);

/*
 * Check the strong connexity of a graph
 */
void uam_isStronglyConnex(pUndirectedAdjacenceMatrix);