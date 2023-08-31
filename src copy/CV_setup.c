#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CV_setup.h"
Values my_tri;
dFrame my_frame;
Point *my_point;

Values CV_findValues(void)
{
	Values c;
	printf("Enter a length of period: ");
	scanf("%f", &c.period);
	printf("Enter an altitude: ");
	scanf("%f", &c.rise);
	printf("Enter an increment: ");
	scanf("%f", &c.increx);
	printf("Enter the amount of periods: ");
	scanf("%u", &c.amount);
	c.peak = c.period / 2;
	c.slope = c.rise / (c.period / 2);
	c.increy = c.increx * c.slope;
	return (c);
}

void CV_graph(dFrame *my_frame, Values my_tri, Point *my_point, float comp1,
	   float comp2)
{
	if (my_point->x <= comp1 && my_point->y < comp2) {
		while (my_point->x < comp1 && my_point->y < comp2) {
			my_point->x = my_point->x + my_tri.increx;
			my_point->y = my_point->y + my_tri.increy;
			insert_point(my_point, my_frame);
		}
	} else if (my_point->x <= comp1 && my_point->y > comp2) {
		while (my_point->x < comp1 && my_point->y > comp2) {
			my_point->x = my_point->x + my_tri.increx;
			my_point->y = my_point->y - my_tri.increy;
			insert_point(my_point, my_frame);
		}
	}
}

void triangle(dFrame *my_frame, Values my_tri, Point *my_point)
{
	CV_graph(my_frame, my_tri, my_point, my_tri.peak, my_tri.rise);
	CV_graph(my_frame, my_tri, my_point, my_tri.period, 0);
}
/*Method to produce multiple periods*/
void CV_cycle(Point *my_point, dFrame *my_frame, Values my_tri /*, int row*/)
{
	float z = my_tri.amount;

	while (z != 0) {
		triangle(my_frame, my_tri, my_point);
		my_tri.peak = my_tri.peak + my_tri.period;
		my_tri.period = my_tri.period + my_tri.period;
		--z;
	}
}
void CV_ex(dFrame *my_frame, Point *my_point, Values my_tri)
{
	
	/*FILE *ptr_fp;*/
	my_tri = CV_findValues();
	float row = my_tri.period * my_tri.amount;
	Point *memory = (Point *)malloc(row * sizeof(Point));
	//Point *my_point = (Point *)malloc(sizeof(Point));
	my_point->x = 0;
	my_point->y = 0;
	*my_frame = init_frame(memory, row);
	CV_cycle(my_point, my_frame, my_tri /*,row*/);
	printArray(my_frame, row);
	printArrayToFile(my_frame->memory, row, "new_array_CV.txt");
	free(my_point);
	free(memory);
}