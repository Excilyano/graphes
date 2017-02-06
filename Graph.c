#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/*
 * Implementation des fonctions de redirection des graphes.
 * Les fonctions presentes dans ce fichier sont generiques : elles acceptent toute representation d'un graphe.
 * Sont ensuite appelees les fonctions specifiques a la representation
 */
pGraphe generateGraph(int nbNodes, int nbEdges, Representation rep) {
	pGraphe graphe = malloc(sizeof(Graphe));
	graphe -> nbNodes = nbNodes;
	graphe -> nbEdges = nbEdges;
	graphe -> rep = rep;
	switch (rep) {
		case UAM :
			graphe -> representationUAM = uam_generateGraphData(nbNodes, nbEdges);
			break;
		case DAM :
			graphe -> representationDAM = dam_generateGraphData(nbNodes, nbEdges);
			break;
		case UAL :
			graphe -> representationUAL = ual_generateGraphData(nbNodes, nbEdges);
			break;
		case DAL :
			graphe -> representationDAL = dal_generateGraphData(nbNodes, nbEdges);
			break;
		case UIM :
			graphe -> representationUIM = uim_generateGraphData(nbNodes, nbEdges);
			break;
		default :
			printf("La representation demandee n'existe pas.\n");
			free(graphe);
			break;
	}
	return graphe;
}

void freeGraph(pGraphe graphe) {
	switch (graphe -> rep) {
		case UAM :
			uam_freeMatrix(graphe -> representationUAM, graphe -> nbNodes);
			break;
		case DAM :
			dam_freeMatrix(graphe -> representationDAM, graphe -> nbNodes);
			break;
		case UAL :
			ual_freeList(graphe -> representationUAL, graphe -> nbNodes);
			break;
		case DAL :
			dal_freeList(graphe -> representationDAL, graphe -> nbNodes);
			break;
		case UIM :
			uim_freeMatrix(graphe -> representationUIM, graphe -> nbNodes, graphe -> nbEdges);
			break;
		default :
			break;
	}
	free(graphe);
}

void display(pGraphe graphe) {
	printf("\n");
	switch (graphe -> rep) {
		case UAM :
			uam_displayMatrix(graphe -> representationUAM, graphe -> nbNodes);
			break;
		case DAM :
			dam_displayMatrix(graphe -> representationDAM, graphe -> nbNodes);
			break;
		case UAL :
			ual_displayList(graphe -> representationUAL, graphe -> nbNodes);
			break;
		case DAL :
			dal_displayList(graphe -> representationDAL, graphe -> nbNodes);
			break;
		case UIM :
			uim_displayMatrix(graphe -> representationUIM, graphe -> nbNodes, graphe -> nbEdges);
			break;
		default :
			break;
	}
}

int isEdge(pGraphe graphe, int x, int y) {
	int result = -1;
	switch (graphe -> rep) {
		case UAM :
			result = uam_isEdge(graphe -> representationUAM, x, y);
			break;
		case DAM :
			result = dam_isEdge(graphe -> representationDAM, x, y);
			break;
		case UAL :
			result = ual_isEdge(graphe -> representationUAL, x, y);
			break;
		case DAL :
			result = dal_isEdge(graphe -> representationDAL, x, y);
			break;
		case UIM :
			result = uim_isEdge(graphe -> representationUIM, x, y, graphe -> nbEdges);
			break;
		default :
			break;
	}
	return result;
}

int addEdge(pGraphe graphe, int x, int y) {
	int result = 0;
	srand(time(NULL));
	int value = rand() % 10;
	switch (graphe -> rep) {
		case UAM :
			result = uam_addEdge(graphe -> representationUAM, x, y, value);
			break;
		case DAM :
			result = dam_addEdge(graphe -> representationDAM, x, y, value);
			break;
		case UAL :
			result = ual_addEdge(graphe -> representationUAL, x, y);
			break;
		case DAL :
			result = dal_addEdge(graphe -> representationDAL, x, y);
			break;
		case UIM :
			result = uim_addEdge(graphe -> representationUIM, x, y, graphe -> nbNodes, graphe -> nbEdges);
			break;
		default :
			break;
	}
	graphe -> nbEdges += result;
	return result;
}

int removeEdge(pGraphe graphe, int x, int y) {
	int result = 0;
	switch (graphe -> rep) {
		case UAM :
			result = uam_removeEdge(graphe -> representationUAM, x, y);
			break;
		case DAM :
			result = dam_removeEdge(graphe -> representationDAM, x, y);
			break;
		case UAL :
			result = ual_removeEdge(graphe -> representationUAL, x, y);
			break;
		case DAL :
			result = dal_removeEdge(graphe -> representationDAL, x, y);
			break;
		case UIM :
			result = uim_removeEdge(graphe -> representationUIM, x, y, graphe -> nbNodes, graphe -> nbEdges);
			break;
		default :
			break;
	}
	graphe -> nbEdges -= result;
	return result;
}

void computeInverse(pGraphe graphe) {
	pDirectedAdjacenceMatrix inverseDAM = NULL;
	pDirectedAdjacenceList inverseDAL = NULL;
	switch (graphe -> rep) {
		case DAM :
			inverseDAM = dam_computeInverse(graphe -> representationDAM, graphe -> nbNodes);
			dam_freeMatrix(graphe -> representationDAM, graphe -> nbNodes);
			graphe -> representationDAM = inverseDAM;
			break;
		case DAL :
			inverseDAL = dal_computeInverse(graphe -> representationDAL, graphe -> nbNodes);
			dal_freeList(graphe -> representationDAL, graphe -> nbNodes);
			graphe -> representationDAL = inverseDAL;
			break;
		default :
			printf("L'inverse de cette representation est l'identite.\n");
			break;
	}
}

int* getNeighbours(pGraphe graphe, int node) {
	int* result = NULL;
	switch (graphe -> rep) {
		case UAM :
			result = uam_getNeighbours(graphe -> representationUAM, node, graphe -> nbNodes);
			break;
		case UAL :
			result = ual_getNeighbours(graphe -> representationUAL, node);
			break;
		case UIM :
			result = uim_getNeighbours(graphe -> representationUIM, node, graphe -> nbNodes, graphe -> nbEdges);
			break;
		default :
			printf("Cette representation n'admet pas de voisins.\n");
			break;
	}
	return result;
}

int* getPredecessors(pGraphe graphe, int node) {
	int* result = NULL;
	switch (graphe -> rep) {
		case DAM :
			result = dam_getPredecessors(graphe -> representationDAM, node, graphe -> nbNodes);
			break;
		case DAL :
			result = dal_getPredecessors(graphe -> representationDAL, node);
			break;
		default :
			printf("Cette representation n'admet pas de predecesseur.\n");
			break;
	}
	return result;
}

int* getSuccessors(pGraphe graphe, int node) {
	int* result = NULL;
	switch (graphe -> rep) {
		case DAM :
			result = dam_getSuccessors(graphe -> representationDAM, node, graphe -> nbNodes);
			break;
		case DAL :
			result = dal_getSuccessors(graphe -> representationDAL, node);
			break;
		default :
			printf("Cette representation n'admet pas de successeur.\n");
			break;
	}
	return result;
}

int* largePath(pGraphe graphe, int depart) {
	int index = 1, i;
	int* sommetsExplores = malloc(2 * sizeof(int));
	sommetsExplores[0] = 1;
	sommetsExplores[1] = depart;
	int* neighbours = NULL;
	int* successors = NULL;
	switch (graphe -> rep % 2) {
		case 0 :
			// Cas des representations non orientee
			while(index <= sommetsExplores[0]) {
				neighbours = getNeighbours(graphe, sommetsExplores[index]);
				index++;
				for (i = 1; i <= neighbours[0]; i++) {
					if(!contains(sommetsExplores, neighbours[i])) {
						sommetsExplores[0]++;
						sommetsExplores = realloc(sommetsExplores, (sommetsExplores[0] +1) * sizeof(int));
						sommetsExplores[sommetsExplores[0]] = neighbours[i];
					}
				}
				free(neighbours);
			}
			break;
		case 1 :
			// Cas des representations orientee
			while(index <= sommetsExplores[0]) {
				successors = getSuccessors(graphe, sommetsExplores[index]);
				index++;
				for (i = 1; i <= successors[0]; i++) {
					if(!contains(sommetsExplores, successors[i])) {
						sommetsExplores[0]++;
						sommetsExplores = realloc(sommetsExplores, (sommetsExplores[0] +1) * sizeof(int));
						sommetsExplores[sommetsExplores[0]] = successors[i];
					}
				}
				free(successors);
			}
			break;
	}
	return sommetsExplores;
}

int* depthPath(pGraphe graphe, int depart) {
	int* sommetsExplores = malloc(2 * sizeof(int));
	sommetsExplores[0] = 1;
	sommetsExplores[1] = depart;
	sommetsExplores = recursiveDepthPath(graphe, depart, sommetsExplores);
	return sommetsExplores;
}

int* recursiveDepthPath(pGraphe graphe, int noeudCourant, int* sommetsExplores) {
	int i;
	int* neighbours = NULL;
	int* successors = NULL;
	switch (graphe -> rep % 2) {
		case 0 :
			// Cas des representations non orientee
			neighbours = getNeighbours(graphe, noeudCourant);
			for (i = 1; i <= neighbours[0]; i++) {
				if(!contains(sommetsExplores, neighbours[i])) {
					sommetsExplores[0]++;
					sommetsExplores = realloc(sommetsExplores, (sommetsExplores[0] +1) * sizeof(int));
					sommetsExplores[sommetsExplores[0]] = neighbours[i];
					sommetsExplores = recursiveDepthPath(graphe, sommetsExplores[sommetsExplores[0]], sommetsExplores);
				}
			}
			free(neighbours);
			break;
		case 1 :
			successors = getSuccessors(graphe, noeudCourant);
			for (i = 1; i <= successors[0]; i++) {
				if(!contains(sommetsExplores, successors[i])) {
					sommetsExplores[0]++;
					sommetsExplores = realloc(sommetsExplores, (sommetsExplores[0] +1) * sizeof(int));
					sommetsExplores[sommetsExplores[0]] = successors[i];
					sommetsExplores = recursiveDepthPath(graphe, sommetsExplores[sommetsExplores[0]], sommetsExplores);
				}
			}
			free(successors);
			break;
	}
	return sommetsExplores;
}

int isConnex(pGraphe graphe) {
	int* path = largePath(graphe, 0);
	int result = path[0] == graphe -> nbNodes;
	free(path);
	return result;
}

int isStronglyConnex(pGraphe graphe) {
	int connex = isConnex(graphe);
	computeInverse(graphe);
	int reverseConnex = isConnex(graphe);
	computeInverse(graphe);
	return connex && reverseConnex;
}

int contains(int* sommetsExplores, int node) {
	int i;
	for (i = 1; i <= sommetsExplores[0]; i++)
		if(sommetsExplores[i] == node) return 1;
	return 0;
}