#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Le nombre d'arguments passes en parametre est incorrect (%d).\n", argc);
		printf("Entrez le nombre desire de noeuds, d'aretes et la representation souhaitee\n");
		printf(" %d : UndirectedAdjancencyMatrix\n", UAM);
		printf(" %d : DirectedAdjancencyMatrix\n", DAM);
		printf(" %d : UndirectedAdjancencyList\n", UAL);
		printf(" %d : DirectedAdjancencyList\n", DAL);
		printf(" %d : UndirectedIncidencyMatrix\n", UIM);
		return 1;
	}
	// Recuperation des parametres de test
	int i, j;
	int nbNodes = atoi(argv[1]);
	int nbEdges = atoi(argv[2]);
	Representation rep = atoi(argv[3]);

	pGraphe graphe = generateGraph(nbNodes, nbEdges, rep);
	display(graphe);
	computeInverse(graphe);
	display(graphe);
	computeInverse(graphe);
	display(graphe);

	if(!(graphe -> rep & 1)) {
		int* neighbours = getNeighbours(graphe, 0);
		printf ("\nNombre de voisins de 0 : %d\n", neighbours[0]);
		for (i = 1; i <= neighbours[0]; i++) {
			printf("%d, ", neighbours[i]);
		}
		free(neighbours);
	} else {
		int* predecessors = getPredecessors(graphe, 0);
		printf ("\nNombre de predecesseurs de 0 : %d\n", predecessors[0]);
		for (i = 1; i <= predecessors[0]; i++) {
			printf("%d, ", predecessors[i]);
		}
		free(predecessors);

		int* successors = getSuccessors(graphe, 0);
		printf ("\nNombre de successeurs de 0 : %d\n", successors[0]);
		for (i = 1; i <= successors[0]; i++) {
			printf("%d, ", successors[i]);
		}
		free(successors);
	}
	int* lPath = largePath(graphe, 0);
	printf("\nNoeuds accessibles depuis le noeud 0 via le parcours en largeur : \n");
	for (i = 1; i <= lPath[0]; i++) {
		printf("%d, ", lPath[i]);
	}
	free(lPath);
	int* dPath = depthPath(graphe, 0);
	printf("\nNoeuds accessibles depuis le noeud 0 via le parcours en profondeur : \n");
	for (i = 1; i <= dPath[0]; i++) {
		printf("%d, ", dPath[i]);
	}
	free(dPath);
	printf("\n");
	printf(isConnex(graphe) ? "Le graphe est connexe\n" : "Le graphe n'est pas connexe\n");
	printf(isStronglyConnex(graphe) ? "Le graphe est fortement connexe\n" : "Le graphe n'est pas fortement connexe\n");
	printf("\nNombre de noeuds : %d\n", graphe -> nbNodes);
	printf("Nombre d'aretes' : %d\n", graphe -> nbEdges);
	printf("L'arete (0,0) ne doit pas exister : %d\n", isEdge(graphe, 0, 0));
	addEdge(graphe, 1, 0);
	printf("L'arete (1,0) doit exister : %d\n", isEdge(graphe, 1, 0));
	printf("\nNombre de noeuds : %d\n", graphe -> nbNodes);
	printf("Nombre d'aretes' : %d\n", graphe -> nbEdges);
	removeEdge(graphe, 1, 0);
	printf("L'arete (1,0) ne doit plus exister : %d\n", isEdge(graphe, 1, 0));

	freeGraph(graphe);
	return 0;
}