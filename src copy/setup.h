#ifndef SETUP_H
#define SETUP_H

typedef struct Values {
	float period;
	float rise;
	float peak;
	unsigned int amount;
	float fall;
	float incre;
	float value;
	float trough;
	float axis;
	int i;
	float increx;
	float increy;
	float slope;
} Values;
typedef struct point {
	float x;
	float y;
} Point;
typedef struct Frame {
	Point *memory; /*The array*/
	int loc; /*Location in the area(Row Number)*/
	int max_val;
} dFrame;

dFrame init_frame(Point *memory, int max_val);
void reset_point(dFrame *frame);
void insert_point(Point *point, dFrame *frame);
int compare_Values(float y, float comp_Value);
void printArrayToFile(Point *memory, int row, const char *filename);
void printArray(dFrame *frame, int size);





#endif // SETUP_H