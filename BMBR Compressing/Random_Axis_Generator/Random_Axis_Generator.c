#include <stdio.h>
#include <stdlib.h>

struct Axis_set {
	int x1;
	int x2;
	int y1;
	int y2;
} typedef AxisSet;

struct Axis_set Axis_generate(void) {
	AxisSet tempSet;
	tempSet.x1 = rand() % (254 + 1);
	tempSet.y1 = rand() % (254 + 1);
	tempSet.x2 = rand() % (255 + 1 - tempSet.x2) + tempSet.x2;
	tempSet.y2 = rand() % (255 + 1 - tempSet.y2) + tempSet.y2;
	return tempSet;
}
