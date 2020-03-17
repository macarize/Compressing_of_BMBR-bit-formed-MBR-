#include <stdio.h>
#include "Axis_gen.h"
#include "PriorityQueue.h"

int isAxisOverlapse(Compressed * comp, QuantizedIndex * qIndex, int i, int j) {
	int bool=1;
	if (comp[j].x[qIndex[i].x1] != '0') { bool = 0; }
	if (comp[j].x[qIndex[i].x2] != '0') { bool = 0; }
	if (comp[j].y[qIndex[i].y1] != '0') { bool = 0; }
	if (comp[j].y[qIndex[i].y2] != '0') { bool = 0; }
	return bool;
}

int isMergeAbleX(Compressed* comp, QuantizedIndex* qIndex, int i, int j) {
	int bool = 0;
	int n = 0, m = 0, c = 0;

	for (n = 0, m = qIndex[i].x1; n < m; n++) {
		if (comp[j].x[n] == '1') c++;
	}
	if (c == 2) bool = 1;
	c = 0;

	if (bool == 0) {
		for (n = (qIndex[i].x2) + 1, m = 16; n < m; n++) {
			if (comp[j].x[n] == '1') c++;
		}
		if (c == 2) bool = 1;
		c = 0;
	}
	return bool;
}

int isMergeAbleY(Compressed* comp, QuantizedIndex* qIndex, int i, int j, int bool) {
	int n = 0, m = 0, c = 0;
	if (bool != 1) bool = 0;
	else {
		bool = 0;
		for (n = 0, m = qIndex[i].y1; n < m; n++) {
			if (comp[j].y[n] == '1') c++;
		}
		if (c == 2) bool = 1;
		c = 0;

		if (bool == 0) {
			for (n = (qIndex[i].y2) + 1, m = 16; n < m; n++) {
				if (comp[j].y[n] == '1') c++;
			}
			if (c == 2) bool = 1;
			c = 0;
		}
	}
	return bool;
}

int connectEdge(int **mat,int bool, int i, int j) {
	if (bool == 1) {
		mat[i][j] = 1;
		mat[j][i] = 1;
	}
}

void countEdges(int count[], int** mat, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		count[i] = 0;
		for (j = 0; j < n; j++) {
			count[i] += mat[i][j];
		}
	}
}

void printPair(int pair1, int pair2) {
	printf("pair : (%d, %d)\n", pair1, pair2);
}

void deleteEdges(int pair1, int pair2, int** mat, int n) {
	int j;
	if (pair1 != NULL) {
		for (j = 0; j < n; j++) {
			mat[pair1][j] = 0;
			mat[j][pair1] = 0;
		}
	}
	if (pair2 != NULL) {
		for (j = 0; j < n; j++) {
			mat[pair2][j] = 0;
			mat[j][pair2] = 0;
		}
	}
}

