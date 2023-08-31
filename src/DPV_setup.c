#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DPV_setup.h"
typedef struct Values configDPV;
/*
Values my_tri;
dFrame my_frame;
Point *my_point;
*/

configDPV DPV_findValues(void)
{
	configDPV c;
	printf("Enter a height of the max_height: ");
	scanf("%f", &c.max_height);
	printf("Enter the length of the period: ");
	scanf("%f", &c.period);
	printf("Enter the width of the peak_width: ");
	scanf("%f", &c.peak_width);
	printf("Enter the size of the increment: ");
	scanf("%f", &c.incre);
	printf("Enter the distance between each point: ");
	scanf("%f", &c.point_Distance);
	printf("Enter the number of periods: ");
	scanf("%u", &c.num_of_periods);
	c.trough_width = c.period - c.peak_width;
	c.peak_width = c.peak_width + (c.trough_width);
	c.min_height = c.incre;
	return (c);
}

void DP_graph(dFrame *my_frame, configDPV my_pulse, Point *my_point,
		float comp1, float comp2)
{
	if (compare_Values(my_frame->current_y, comp2) == 1 && my_point->x < comp1)
	{
		while (my_point->x < comp1)
		{
			my_point->x = my_point->x + my_pulse.point_Distance;
			insert_point(my_frame);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_frame->current_y < comp2)
		{
	while (my_frame->current_y < comp2)
		{
			my_frame->current_y = my_frame->current_y + my_pulse.point_Distance;
			insert_point(my_frame);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_frame->current_y > comp2)
		   {
	while (my_frame->current_y > comp2)
		{
			my_frame->current_y = my_frame->current_y - my_pulse.point_Distance;
			insert_point(my_frame);
		}
	} else if (compare_Values(my_frame->current_y, comp2) == 1 &&
		   my_point->x > comp1)
		   {
	while (my_point->x > comp1)
		{
			my_point->x = my_point->x - my_pulse.point_Distance;
			insert_point(my_frame);
		}
	}
}
/* Function to draw a segment of the ascending Differential Pulse waveform*/
void DPV_graph(dFrame *my_frame, configDPV my_pulse, Point *my_point)
{
	/*float htro = my_pulse.trough_width;*/
	float samp_y = my_frame->current_y;
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough_width, samp_y);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough_width, my_pulse.max_height);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak_width, my_pulse.max_height);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak_width, my_pulse.min_height);
}
/* Function to draw a segment of the descending Differential Pulse waveform*/
void DPV_graph_dec(dFrame *my_frame, configDPV my_pulse, Point *my_point)
{
	/*float htro = my_pulse.trough_width;*/
	float samp_y = my_frame->current_y;
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough_width, samp_y);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough_width, my_pulse.min_height);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak_width, my_pulse.min_height);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak_width, my_pulse.max_height);
}

void cycle(Point *my_point, dFrame *my_frame, configDPV my_pulse)
{
	unsigned int z = my_pulse.num_of_periods;
	float ri = my_pulse.max_height;
	float peri = my_pulse.period;
	my_frame -> current_y = 0;
	while (z != 0)
	{
		DPV_graph(my_frame, my_pulse, my_point);
		peri = peri + my_pulse.period;
		my_pulse.trough_width = my_pulse.trough_width + my_pulse.period;
		my_pulse.peak_width = my_pulse.peak_width + my_pulse.period;
		my_pulse.max_height = my_pulse.max_height + my_pulse.incre;
		my_pulse.min_height = my_pulse.min_height + my_pulse.incre;
		--z;
	}
	z = my_pulse.num_of_periods;
	my_pulse.min_height = my_pulse.min_height - my_pulse.incre - ri;
	my_pulse.max_height = my_pulse.max_height - ri - my_pulse.incre;
	while (z != 0)
	{
		DPV_graph_dec(my_frame, my_pulse, my_point);
		peri = peri + my_pulse.period;
		my_pulse.trough_width = my_pulse.trough_width + my_pulse.period;
		my_pulse.peak_width = my_pulse.peak_width + my_pulse.period;
		my_pulse.max_height = my_pulse.max_height - my_pulse.incre;
		my_pulse.min_height = my_pulse.min_height - my_pulse.incre;
		--z;
	}
}
void DPV_ex(dFrame *my_frame, Point *my_point, Values my_pulse)
{
	//my_pulse = DPV_findValues();
	float row = (my_pulse.period * ((my_pulse.num_of_periods * 2))) +
		    (my_pulse.max_height * (my_pulse.num_of_periods * 2)) +
		    ((my_pulse.max_height - my_pulse.incre) *
		     (my_pulse.num_of_periods * 2)); /*array.max_my_pulse;*/
	Point *memory = (Point *)malloc(row * sizeof(Point));
	Point *my_point = (Point *)malloc(1);
	my_point->y = 0;

	*my_frame = init_frame(memory, row);
	cycle(my_point, my_frame, my_pulse);
	printArrayToFile(my_frame->memory, row, "new_array_DPV.txt");
	free(my_point);
	free(memory);
}