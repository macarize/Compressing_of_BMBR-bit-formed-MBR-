#ifndef __Improved_compressing__
#define __Improved_compressing__
#include "compression.h"

int isAxisOverlapse(Compressed * comp, QuantizedIndex * qIndex, int i, int j);
int isMergeAbleX(Compressed* comp, QuantizedIndex* qIndex, int i, int j);
int isMergeAbleY(Compressed* comp, QuantizedIndex* qIndex, int i, int j, int bool);
int connectEdge(int **mat,int bool, int i, int j);
void countEdges(int count[], int **mat, int n);
void printPair(int pair1, int pair2);
void deleteEdges(int pair1, int pair2, int **mat, int n);
#endif