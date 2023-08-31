#ifndef SETUP_H
#define SETUP_H

typedef struct Values {
	float period;
	float max_height;
	float peak_width;
	unsigned int num_of_periods;
	float min_height;
	float incre;
	float point_Distance;
	float trough_width;
	float axis;
	int row_num;
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
	float current_y;
} dFrame;

dFrame init_frame(Point *memory, int max_val);
extern Point *memory;
void reset_point(dFrame *frame);
void insert_point(dFrame *frame);
int compare_Values(float y, float comp_Value);
void printArrayToFile(Point *memory, int row, const char *filename);
void printArray(dFrame *frame, int size);





#endif // SETUP_H