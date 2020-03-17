#ifndef __SPATIAL_DATA_COMPRESSION__
#define __SPATIAL_DATA_COMPRESSION__
typedef struct _QuantizedIndex {
	int x1;
	int y1;
	int x2;
	int y2;
} QuantizedIndex;

typedef struct _PreCompressed {
	int x1;
	int y1;
	int x2;
	int y2;
} PreCompressed;

typedef struct _Compressed {
	char x[16];
	char y[16];
} Compressed;

typedef struct _Range {
	int x1;
	int y1;
	int x2;
	int y2;
} Range;

void CompressedInit(Compressed * compressed, int n);
void RangeInit(Range * range);

void findRange(PreCompressed * precomp, Range * range, int n);
void Compress(PreCompressed * precomp, Compressed * comp, Range * range, int n, QuantizedIndex * qIndex);

void printPrecompressed(PreCompressed* precomp, int n);
void printAxisSet(Compressed* comp, int n);
void printSearchRange(Range* range);
void printMatrix(int** mat, int n);
#endif