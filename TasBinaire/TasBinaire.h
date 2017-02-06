#ifndef TB_REP
#define TB_REP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TasBinaire* pTasBinaire;

typedef struct TasBinaire {
	int size;
	int* leaves;
} TasBinaire;

pTasBinaire initializeBinaryStack(int value);
void addLeaf(pTasBinaire tas, int value);
void displayStack(pTasBinaire tas);

#endif