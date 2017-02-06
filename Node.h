#ifndef NODE
#define NODE

typedef struct Node* pNode;

typedef struct Node {
	int value;
	int nbNeighbours;
	pNode* neighbours;
	int nbSuccessors;
	pNode* successors;
	int nbPredecessors;
	pNode* predecessors;
} Node;

#endif