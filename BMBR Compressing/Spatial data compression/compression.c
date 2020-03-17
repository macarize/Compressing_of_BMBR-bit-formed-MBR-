#include <stdio.h>
#include <math.h>
#include "compression.h"

void CompressedInit(Compressed * compressed, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 16; j++) {
			compressed[i].x[j] = '0';
			compressed[i].y[j] = '0';
		}
	}
}

void Compress(PreCompressed * precomp, Compressed * comp, Range * range, int n, QuantizedIndex * qIndex) {
	int max_x = range->x2, max_y = range->y2, min_x = range->x1, min_y = range->y1;
	int interval_x = max_x - min_x, interval_y = max_y - min_y;
	double width = ceil((interval_x) / 15.0), height = ceil((interval_y) / 15.0);
	int i;

	int quantized_x1;
	int quantized_y1;
	int quantized_x2;
	int quantized_y2;

	for (i = 0; i < n; i++) {
		quantized_x1 = (int)floor((precomp[i].x1 / width));
		quantized_y1 = (int)floor((precomp[i].y1 / height));
		quantized_x2 = (int)ceil((precomp[i].x2 / width));
		quantized_y2 = (int)ceil((precomp[i].y2 / height));

		comp[i].x[quantized_x1] = '1';
		comp[i].x[quantized_x2] = '1';
		comp[i].y[quantized_y1] = '1';
		comp[i].y[quantized_y2] = '1';

		qIndex[i].x1 = quantized_x1;
		qIndex[i].x2 = quantized_x2;
		qIndex[i].y1 = quantized_y1;
		qIndex[i].y2 = quantized_y2;
	}
}

void findRange(PreCompressed * precomp, Range * range, int n) {

	int i = 0;

	range->x1 = precomp[i].x1;
	range->y1 = precomp[i].y1;
	range->x2 = precomp[i].x2;
	range->y2 = precomp[i].y2;

	for (i = 1; i < n; i++) {
		if (precomp[i].x1 < range->x1) range->x1 = precomp[i].x1;
		if (precomp[i].y1 < range->y1) range->y1 = precomp[i].y1;
		if (precomp[i].x2 > range->x2) range->x2 = precomp[i].x2;
		if (precomp[i].y2 > range->y2) range->y2 = precomp[i].y2;
	}
}

void RangeInit(Range * range) {
	range->x1 = 0;
	range->y1 = 0;
	range->x2 = 0;
	range->y2 = 0;
}

void printAxisSet(Compressed* comp, int n) {
	int i,j;
	for (i = 0; i < n; i++) {
		printf("Axis for set %d : ", i);
		printf("(");
		for (j = 0; j < 16; j++) {
			printf("%c", comp[i].x[j]);
		}
		printf(", ");
		for (j = 0; j < 16; j++) {
			printf("%c", comp[i].y[j]);
		}
		printf(") \n");
	}
}

void printSearchRange(Range* range) {
	printf("Search Range : (%d, %d), (%d, %d)\n\n", range->x1, range->y1, range->x2, range->y2);
}
void printMatrix(int** mat, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}
void printPrecompressed(PreCompressed* precomp, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		printf("precomp Axis for set %d : ", i);
		printf("x1 : %d ", precomp[i].x1);
		printf("x2 : %d ", precomp[i].x2);
		printf("y1 : %d ", precomp[i].y1);
		printf("y2 : %d \n", precomp[i].y2);
	}
}

