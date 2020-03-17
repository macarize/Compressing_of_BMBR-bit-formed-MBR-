#include "Axis_gen.h"
#include "compression.h"
#include <time.h>


AxisSet Axis_generate(void) {
	AxisSet tempSet = { 0 };
	tempSet.x1 = rand() % (65535 + 1);
	tempSet.y1 = rand() % (65536 + 1);
	tempSet.x2 = rand() % (65536 + 1 - tempSet.x1) + tempSet.x1;
	tempSet.y2 = rand() % (65536 + 1 - tempSet.y1) + tempSet.y1;
	return tempSet;
}

int isOverlapping(PreCompressed r1, AxisSet r2)
{
	if (r1.x1 > r2.x2 || r2.x1 > r1.x2 || r1.y1 > r2.y2 || r2.y1 > r1.y2)
		return 0;
	return 1;
}

void makeSquare(PreCompressed * preComp, int n) {
	AxisSet tempSet;
	int i, j;

	preComp[0].x1 = 0;
	preComp[0].y1 = 0;
	preComp[0].x2 = 65536;
	preComp[0].y2 = 65536;

	for (i = 1; i < n; i++) {
		tempSet = Axis_generate();
		for (j = 1; j < i; j++) {
			if (isOverlapping(preComp[j], tempSet)) {
				tempSet = Axis_generate();
				j = 1;
			}
		}
		preComp[i].x1 = tempSet.x1;
		preComp[i].y1 = tempSet.y1;
		preComp[i].x2 = tempSet.x2;
		preComp[i].y2 = tempSet.y2;
	}
}

