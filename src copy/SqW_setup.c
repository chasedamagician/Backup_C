#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SqW_setup.h"

Values my_square;
dFrame my_frame;
Point *my_point;

Values SqW_findValues(void)
{
	Values c;
	printf("Enter the axis equation: ");
	scanf(" %f", &c.axis);
	printf("Enter the length of the period: ");
	scanf(" %f", &c.period);
	printf("Enter a height of the rise: ");
	scanf(" %f", &c.rise);
	printf("Enter the size of the increment: ");
	scanf(" %f", &c.incre);
	printf("Enter the distance between each point: ");
	scanf(" %f", &c.value);
	printf("Enter the number of periods: ");
	scanf(" %u", &c.amount);
	c.fall = c.axis - c.rise;
	c.rise = c.rise + c.axis;
	c.peak = c.period / 2;

	c.i = 0;
	return (c);
}
void SqW_graph(dFrame *my_frame, Values my_square, Point *my_point, float comp1,
	   float comp2)
{
	if (compare_Values(my_point->y, comp2) == 1 && my_point->x < comp1) {
		while (my_point->x < comp1) {
			my_point->x = my_point->x + my_square.value;
			insert_point(my_point, my_frame);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_point->y < comp2) {
		while (my_point->y < comp2) {
			my_point->y = my_point->y + my_square.value;
			insert_point(my_point, my_frame);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_point->y > comp2) {
		while (my_point->y > comp2) {
			my_point->y = my_point->y - my_square.value;
			insert_point(my_point, my_frame);
		}
	} else if (compare_Values(my_point->y, comp2) == 1 &&
		   my_point->x > comp1) {
		while (my_point->x > comp1) {
			my_point->x = my_point->x - my_square.value;
			insert_point(my_point, my_frame);
		}
	}
}
/*The function SqW_graphs a single period of the plot*/
void SW_graph(dFrame *my_frame, Values my_square, Point *my_point)
{
	float p_h = my_point->x; /*Place holder variable*/
	SqW_graph(my_frame, my_square, my_point, p_h, my_square.rise);
	SqW_graph(my_frame, my_square, my_point, my_square.peak, my_square.rise);
	SqW_graph(my_frame, my_square, my_point, my_square.peak, my_square.axis);
	SqW_graph(my_frame, my_square, my_point, my_square.peak, my_square.fall);
	SqW_graph(my_frame, my_square, my_point, my_square.period, my_square.fall);
	SqW_graph(my_frame, my_square, my_point, my_square.period, my_square.axis);
}

void SW_cycle(Point *my_point, dFrame *my_frame, Values my_square)
{
	unsigned int z = my_square.amount;
	/*int num_points = (int)row/((my_square.amount/2)-1);*/
	float axi = my_square.axis;
	float peri = my_square.period;
	while (z != 0) {
		SW_graph(my_frame, my_square, my_point);
		my_square.axis = my_square.axis + axi;
		SqW_graph(my_frame, my_square, my_point, my_square.period,
		      my_square.axis);

		my_square.peak = my_square.peak + peri;
		my_square.period = peri + my_square.period;
		my_square.rise = my_square.rise + my_square.incre;
		my_square.fall = my_square.fall + my_square.incre;
		--z;
	}
	z = my_square.amount - 1;
	my_square.rise = my_square.axis;
	my_square.axis = my_square.axis - 2 * my_square.incre;
	my_square.fall = my_square.fall - 2 * my_square.incre;

	while (z != 0) {
		SW_graph(my_frame, my_square, my_point);

		my_square.axis = my_square.axis - axi;

		if (z == 1 && my_point->y == axi) {
			break;
		}

		my_square.peak = my_square.peak + peri;
		my_square.period = peri + my_square.period;
		my_square.rise = my_square.rise - my_square.incre;
		my_square.fall = my_square.fall - my_square.incre;
		--z;
	}
}
void SqW_ex(dFrame *my_frame, Point *my_point, Values my_square)
{
	my_square = SqW_findValues();
	float row = (my_square.period * ((my_square.amount * 2) - 1)) +
		    ((my_square.rise * ((my_square.amount * 2))) * 2);
	Point *memory = (Point *)malloc(row * sizeof(Point));
	//Point *my_point = (Point *)malloc(sizeof(Point));
	my_point->x = 0;
	my_point->y = my_square.axis;
	*my_frame = init_frame(memory, row);
	SW_cycle(my_point, my_frame, my_square);
	printArray(my_frame, row);
	printArrayToFile(my_frame->memory, row, "new_array.txt");
	free(my_point);
	free(memory);
}