#include <stdio.h>
#include <math.h>
#include "Axis_gen.h"
#include "compression.h"
#include "PriorityQueue.h"
#include "Improved_compressing.h"
#include "DLinkedList.h"
#define MAT_LEN	1000

int DataPriorityComp(int num1, int num2)
{
	return num2 - num1;
}

int main(void)
{	
	srand(time(NULL));
	int n = 1;
	while (n<= 1000) {
		int i, j;
		int pair1, pair2;

		List pair;
		AxisSet tempSet;
		PQueue pq1, pq2, mpq;

		int** Matrix = (int**)malloc(sizeof(int*) * MAT_LEN);
		for (int i = 0; i < MAT_LEN; i++)
			* (Matrix + i) = (int*)malloc(sizeof(int) * MAT_LEN);

		printf("DataNum : ");
		scanf_s("%d", &n);
		printf("n : %d ", n);

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				Matrix[i][j] = 0;
			}
		}

		Range* range = (Range*)malloc(sizeof(Range));
		PreCompressed* preComp = (PreCompressed*)malloc(sizeof(PreCompressed) * n);
		Compressed* comp = (Compressed*)malloc(sizeof(Compressed) * n);
		QuantizedIndex* qIndex = (QuantizedIndex*)malloc(sizeof(QuantizedIndex) * n);
		int* count = (int*)malloc(sizeof(int) * n);
		int* uno = (int*)malloc(sizeof(int) * n);

		RangeInit(range);
		CompressedInit(comp, n);
		ListInit(&pair);

		for (i = 0; i < n; i++) {
			uno[i] = 0;
		}

		makeSquare(preComp, n);

		findRange(preComp, range, n);
		printPrecompressed(preComp, n);
		Compress(preComp, comp, range, n, qIndex);

		printAxisSet(comp, n);
		printSearchRange(range);

		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				int bool = 1;
				bool = isAxisOverlapse(comp, qIndex, i, j);
				if (bool == 1) {
					bool = isMergeAbleX(comp, qIndex, i, j);
					bool = isMergeAbleY(comp, qIndex, i, j, bool);
					connectEdge(Matrix, bool, i, j);
				}
			}
		}
		countEdges(count, Matrix, n);
		printMatrix(Matrix, n);

		while (1) {
			PQueueInit(&pq1, DataPriorityComp);
			PQueueInit(&pq2, DataPriorityComp);

			for (i = 0; i < n; i++) {
				if (count[i] > 0) {
					PEnqueue(&pq1, count[i], i);
				}
			}
			if (PQIsEmpty(&pq1)) break;

			pair1 = PDequeue(&pq1);

			for (j = 0; j < n; j++) {
				if (Matrix[pair1][j] == 1) PEnqueue(&pq2, count[j], j);
			}
			pair2 = PDequeue(&pq2);
			printPair(pair1, pair2);

			LInsert(&pair, pair1, pair2);
			uno[pair1] = 1;
			uno[pair2] = 1;

			deleteEdges(pair1, pair2, Matrix, n);

			countEdges(count, Matrix, n);
			printMatrix(Matrix, n);

		}

		for (i = 0; i < n; i++) {
			if (uno[i] == 0) LInsert(&pair, i, -1);
		}

		if (LFirst(&pair, &pair1, &pair2))
		{	
			i = 1;
			printf("Pair %d : %d, %d \n",i, pair1, pair2);

			while (LNext(&pair, &pair1, &pair2)) {
				i++;
				printf("Pair %d : %d, %d \n", i, pair1, pair2);
			}
		}
		printf("i : %d\n", i);
		n+=10;
	}
}