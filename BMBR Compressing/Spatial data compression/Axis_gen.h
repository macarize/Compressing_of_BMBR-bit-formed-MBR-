#ifndef __Axis_gen__
#define __Axis_gen__
#include "compression.h"

struct Axis_set {
	int x1;
	int x2;
	int y1;
	int y2;
} typedef AxisSet;

AxisSet Axis_generate(void);
int isOverlapping(PreCompressed r1, AxisSet r2);
void makeSquare(PreCompressed * preComp, int n);
#endif