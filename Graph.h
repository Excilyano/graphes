#ifndef GRAPH
#define GRAPH

#include "Node.h"
#include "DirectedAdjacenceList/DirectedAdjacenceList.h"
#include "DirectedAdjacenceMatrix/DirectedAdjacenceMatrix.h"
#include "UndirectedAdjacenceList/UndirectedAdjacenceList.h"
#include "UndirectedAdjacenceMatrix/UndirectedAdjacenceMatrix.h"
#include "UndirectedIncidenceMatrix/UndirectedIncidenceMatrix.h"
/*
 * Representation generique d'un graphe
 * Toute representation d'un graphe peut etre stocke dans cette structure
 * L'enumeration "Representation" permet de determiner quelle representation est utilisee pour l'instance en cours :
 	> UndirectedAdjancencyMatrix
 	> DirectedAdjancencyMatrix
 	> UndirectedAdjancencyList
 	> DirectedAdjancencyList
 	> UndirectedIncidencyMatrix
 */
typedef enum Representation Representation;
enum Representation {
	UAM,
	DAM,
	UAL,
	DAL,
	UIM
};
typedef struct Graphe* pGraphe;

typedef struct Graphe {
	// Definition des attributs communs a toutes les representations
	int nbNodes;
	int nbEdges;
	Representation rep;

	// Definitions des differentes structures / representation
	pDirectedAdjacenceList representationDAL;
	pDirectedAdjacenceMatrix representationDAM;
	pUndirectedAdjacenceList representationUAL;
	pUndirectedAdjacenceMatrix representationUAM;
	pUndirectedIncidenceMatrix representationUIM;
} Graphe;

pGraphe generateGraph(int nbNodes, int nbEdges, Representation rep);
void freeGraph(pGraphe graphe);
void display(pGraphe graphe);
int isEdge(pGraphe graphe, int x, int y);
int addEdge(pGraphe graphe, int x, int y);
int removeEdge(pGraphe graphe, int x, int y);
void computeInverse(pGraphe graphe);
int* getNeighbours(pGraphe graphe, int node);
int* getPredecessors(pGraphe graphe, int node);
int* getSuccessors(pGraphe graphe, int node);
int* largePath(pGraphe graphe, int depart);
int* depthPath(pGraphe graphe, int depart);
int* recursiveDepthPath(pGraphe graphe, int noeudCourant, int* sommetsExplores);
int contains(int* array, int node);
int isConnex(pGraphe graphe);
int isStronglyConnex(pGraphe graphe);

#endif