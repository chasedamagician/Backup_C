#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "setup.h"

dFrame init_frame(Point *memory, int max_val)
{
	dFrame ret = { .memory = memory, .loc = 0, .max_val = max_val };
	return (ret);
}

void reset_point(dFrame *frame)
{
	frame->loc = 0;
}
/*Inserts a new point onto the array*/
void insert_point(dFrame *frame)
{
/*Takes the valeus from the struct and sets that portion of memory to the
specific coordinates*/

	frame->memory[frame->loc].y = frame->current_y;
	if (frame->loc < frame->max_val) {
		frame->loc++;
	} else {
		reset_point(frame);
	}
}
void printArrayToFile(Point *memory, int row, const char *filename)
{
	/* Open the file for writing*/
	FILE *file = fopen(filename, "w");

	/* Check if the file was opened successfully*/
	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}

	/* Loop through the array and write each element to the file*/
	for (int i = 0; i < row; i++) {
		fprintf(file, "%.2f\n ",memory[i].y);
	}

	/* Close the file*/
	fclose(file);
}
int compare_Values(float y, float comp_Value)
{
	int retur;
	if (fabs(y - comp_Value) < 0.000001) {
		retur = 1;
	} else {
		retur = 0;
	}
	return (retur);
}
void printArray(dFrame *frame, int size)
{
	printf("Coordinates:\n");
	for (int i = 0; i < size; i++) {
		printf("Coordinate %d: (%.2f)\n", i + 1,
		       frame->memory[i].y);
	}
}