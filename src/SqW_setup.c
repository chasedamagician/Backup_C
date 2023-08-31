#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SqW_setup.h"

//Values my_square;
//dFrame my_frame;
//Point *my_point;

Values SqW_findValues(void)
{
	Values c;
	printf("Enter the axis equation: ");
	scanf(" %f", &c.axis);
	printf("Enter the length of the period: ");
	scanf(" %f", &c.period);
	printf("Enter a height of the max_height: ");
	scanf(" %f", &c.max_height);
	printf("Enter the size of the increment: ");
	scanf(" %f", &c.incre);
	printf("Enter the distance between each point: ");
	scanf(" %f", &c.point_Distance);
	printf("Enter the number of periods: ");
	scanf(" %u", &c.num_of_periods);
	c.min_height = c.axis - c.max_height;
	c.max_height = c.max_height + c.axis;
	c.peak_width = c.period / 2;

	c.row_num = 0;
	return (c);
}
void SqW_graph(dFrame *my_frame, Values my_square, Point *my_point, float comp1,
	   float comp2)
{
	if (compare_Values(my_frame->current_y, comp2) == 1 && my_point->x < comp1) {
		while (my_point->x < comp1) {
			my_point->x = my_point->x + my_square.point_Distance;
			insert_point(my_point);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_frame->current_y < comp2) {
		while (my_frame->current_y < comp2) {
			my_frame->current_y = my_frame->current_y + my_square.point_Distance;
			insert_point(my_point);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_frame->current_y > comp2) {
		while (my_frame->current_y > comp2) {
			my_frame->current_y = my_frame->current_y - my_square.point_Distance;
			insert_point(my_point);
		}
	} else if (compare_Values(my_frame->current_y, comp2) == 1 &&
		   my_point->x > comp1) {
		while (my_point->x > comp1) {
			my_point->x = my_point->x - my_square.point_Distance;
			insert_point(my_point);
		}
	}
}
/*The function SqW_graphs a single period of the plot*/
void SW_graph(dFrame *my_frame, Values my_square, Point *my_point)
{
	float p_h = my_point->x; /*Place holder variable*/
	SqW_graph(my_frame, my_square, my_point, p_h, my_square.max_height);
	SqW_graph(my_frame, my_square, my_point, my_square.peak_width, my_square.max_height);
	SqW_graph(my_frame, my_square, my_point, my_square.peak_width, my_square.axis);
	SqW_graph(my_frame, my_square, my_point, my_square.peak_width, my_square.min_height);
	SqW_graph(my_frame, my_square, my_point, my_square.period, my_square.min_height);
	SqW_graph(my_frame, my_square, my_point, my_square.period, my_square.axis);
}

void SW_cycle(Point *my_point, dFrame *my_frame, Values my_square)
{
	unsigned int z = my_square.num_of_periods;
	/*int num_points = (int)row/((my_square.num_of_periods/2)-1);*/
	float axi = my_square.axis;
	float peri = my_square.period;
	my_frame->current_y= axi;
	while (z != 0) {
		SW_graph(my_frame, my_square, my_point);
		my_square.axis = my_square.axis + axi;
		SqW_graph(my_frame, my_square, my_point, my_square.period,
		      my_square.axis);

		my_square.peak_width = my_square.peak_width + peri;
		my_square.period = peri + my_square.period;
		my_square.max_height = my_square.max_height + my_square.incre;
		my_square.min_height = my_square.min_height + my_square.incre;
		--z;
	}
	z = my_square.num_of_periods - 1;
	my_square.max_height = my_square.axis;
	my_square.axis = my_square.axis - 2 * my_square.incre;
	my_square.min_height = my_square.min_height - 2 * my_square.incre;

	while (z != 0) {
		SW_graph(my_frame, my_square, my_point);

		my_square.axis = my_square.axis - axi;

		if (z == 1 && my_frame->current_y == axi) {
			break;
		}

		my_square.peak_width = my_square.peak_width + peri;
		my_square.period = peri + my_square.period;
		my_square.max_height = my_square.max_height - my_square.incre;
		my_square.min_height = my_square.min_height - my_square.incre;
		--z;
	}
}
void SqW_ex(dFrame *my_frame, Point *my_point, Values my_square)
{
	//my_square = SqW_findValues();
	float row = (my_square.period * ((my_square.num_of_periods * 2) - 1)) +
		    ((my_square.max_height * ((my_square.num_of_periods * 2))) * 2);
	Point *memory = (Point *)malloc(row * sizeof(Point));
	Point *my_point = (Point *)malloc(1);
	my_frame->current_y = my_square.axis;
	*my_frame = init_frame(memory, row);
	SW_cycle(my_point, my_frame, my_square);
	printArray(my_frame, row);
	printArrayToFile(my_frame->memory, row, "new_array.txt");
	free(my_point);
	free(memory);
}