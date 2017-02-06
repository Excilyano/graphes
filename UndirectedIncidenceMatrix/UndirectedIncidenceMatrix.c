#include "UndirectedIncidenceMatrix.h"
/*
 * Finds the neighbours of a node by concatening predecessors and successors
 */
int* uim_getNeighbours(pUndirectedIncidenceMatrix matrix, int node, int nbNodes, int nbEdges) {
	int i, j, cpt = 1;
	int* neighbours = malloc(sizeof(int));
	for (i = 0; i < nbEdges; i++) {
		if (matrix -> edges[i] -> nodes[node] -> value == 1) {
			neighbours = realloc(neighbours, (++cpt) * sizeof(int));
			for (j = 0; j < nbNodes; j++) {
				if (j != node && matrix -> edges[i] -> nodes[j] -> value == 1) neighbours[cpt -1] = j;
			}
		}
	}
	neighbours[0] = cpt -1;
	return neighbours;
}

/*
 * Return whether there is an edge between x and y
 */
int uim_isEdge(pUndirectedIncidenceMatrix matrix, int x, int y, int nbEdges) {
	if(x == y) return 0;
	int i;
	int found = 0;
	for (i = 0; i < nbEdges; i++) {
		found = found || (matrix -> edges[i] -> nodes[x] -> value == 1 && matrix -> edges[i] -> nodes[y] -> value == 1 );
	}
	return found;
}

/*
 * Remove the edge between x and y
 */
int uim_removeEdge(pUndirectedIncidenceMatrix matrix, int x, int y, int nbNodes, int nbEdges) {
	if(x == y) return 0;
	int i;
	int index = 0;
	while (index < nbEdges
		&& (matrix -> edges[index] -> nodes[x] -> value != 1
		|| matrix -> edges[index] -> nodes[y] -> value != 1))
		index ++;
	if(index == nbEdges) return 0;
	for (i = 0; i < nbNodes; i++) {
		free(matrix -> edges[index] -> nodes[i]);
	}
	free(matrix -> edges[index] -> nodes);
	matrix -> edges[index] = matrix -> edges[nbEdges -1];
	free(matrix -> edges[nbEdges -1]);
	matrix -> edges = realloc(matrix -> edges, nbEdges * sizeof(pEdge));
	return 1;
}

/*
 * Add an edge before x and y, if not already existing
 * No loop, so x must be different from y
 */
int uim_addEdge(pUndirectedIncidenceMatrix matrix, int x, int y, int nbNodes, int nbEdges) {
	int i, j;
	int exists = 0;
	for (i = 0; i < nbEdges; i++) {
		exists = exists
			|| (matrix -> edges[i] -> nodes[x] -> value == 1
				&& matrix -> edges[i] -> nodes[y] -> value == 1);
	}
	if (x != y && !exists) {
		matrix -> edges = realloc(matrix -> edges, (nbEdges+1) * sizeof(pEdge));
		matrix -> edges[nbEdges] = malloc(sizeof(Edge));
		matrix -> edges[nbEdges] -> nodes = malloc(nbNodes * sizeof(pNode));
		for (j = 0; j < nbNodes; j++) {
			matrix -> edges[nbEdges] -> nodes[j] = malloc(sizeof(Node));
			matrix -> edges[nbEdges] -> nodes[j] -> value = 0;
		}
		matrix -> edges[nbEdges] -> nodes[x] -> value = 1;
		matrix -> edges[nbEdges] -> nodes[y] -> value = 1;
		return 1;
	}
	return 0;
}

/*
 * Displays the given matrix
 */
void uim_displayMatrix(pUndirectedIncidenceMatrix matrix, int nbNodes, int nbEdges) {
	int i, j;

	for (i = 0; i < nbEdges; i++) {
		printf("e%d (", i);
		for(j = 0; j < nbNodes; j++) {
			printf("%d", matrix -> edges[i] -> nodes[j] -> value);
			if (j != nbNodes -1) {
				printf(",");
			}
		}
		printf("),\n");
	}
}

/*
 * Free all allocations bound to the matrix given
 */
void uim_freeMatrix(pUndirectedIncidenceMatrix matrix, int nbNodes, int nbEdges) {
	int i, j;
	for (i = 0; i < nbEdges; i++) {
		for (j = 0; j < nbNodes; j++) {
			free(matrix -> edges[i] -> nodes[j]);
		}
		free(matrix -> edges[i] -> nodes);
		free(matrix -> edges[i]);
	}
	free(matrix -> edges);
	free(matrix);
}

/*
 * Initializes and allocates memory for a square matrix of size "size".
 */
pUndirectedIncidenceMatrix uim_initEmptyMatrix(int nbNodes, int nbEdges) {
	int i, j;
	pUndirectedIncidenceMatrix matrix = malloc(sizeof(UndirectedIncidenceMatrix));
	matrix -> edges = NULL;
	return matrix;
}

/*
 * Generates a random symectric matrix of size n, with m edges
 */
pUndirectedIncidenceMatrix uim_generateGraphData(int n, int m) {
	srand(time(NULL));
	int x, y;
	int cpt = 0;
	pUndirectedIncidenceMatrix matrix = uim_initEmptyMatrix(n, m);
	while (cpt < m) {
		x = rand() % n;
		y = rand() % n;
		cpt += uim_addEdge(matrix, x, y, n, cpt);
	}
	return matrix;
}