#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DPV_setup.h"
typedef struct Values configDPV;
Values my_pulse;
dFrame my_frame;
Point *my_point;

configDPV DPV_findValues(void)
{
	configDPV c;
	printf("Enter a height of the rise: ");
	scanf("%f", &c.rise);
	printf("Enter the length of the period: ");
	scanf("%f", &c.period);
	printf("Enter the width of the peak: ");
	scanf("%f", &c.peak);
	printf("Enter the size of the increment: ");
	scanf("%f", &c.incre);
	printf("Enter the distance between each point: ");
	scanf("%f", &c.value);
	printf("Enter the number of periods: ");
	scanf("%u", &c.amount);
	c.trough = c.period - c.peak;
	c.peak = c.peak + (c.trough);
	c.fall = c.incre;
	return (c);
}

void DP_graph(dFrame *my_frame, configDPV my_pulse, Point *my_point, float comp1,
	   float comp2)
{
	if (compare_Values(my_point->y, comp2) == 1 && my_point->x < comp1) {
		while (my_point->x < comp1) {
			my_point->x = my_point->x + my_pulse.value;
			insert_point(my_point, my_frame);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_point->y < comp2) {
		while (my_point->y < comp2) {
			my_point->y = my_point->y + my_pulse.value;
			insert_point(my_point, my_frame);
		}
	} else if (compare_Values(my_point->x, comp1) == 1 &&
		   my_point->y > comp2) {
		while (my_point->y > comp2) {
			my_point->y = my_point->y - my_pulse.value;
			insert_point(my_point, my_frame);
		}
	} else if (compare_Values(my_point->y, comp2) == 1 &&
		   my_point->x > comp1) {
		while (my_point->x > comp1) {
			my_point->x = my_point->x - my_pulse.value;
			insert_point(my_point, my_frame);
		}
	}
}
/* Function to draw a segment of the ascending Differential Pulse waveform*/
void DPV_graph(dFrame *my_frame, configDPV my_pulse, Point *my_point)
{
	/*float htro = my_pulse.trough;*/
	float samp_y = my_point->y;
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough, samp_y);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough, my_pulse.rise);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.rise);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.fall);
}
/* Function to draw a segment of the descending Differential Pulse waveform*/
void DPV_graph_dec(dFrame *my_frame, configDPV my_pulse, Point *my_point)
{
	/*float htro = my_pulse.trough;*/
	float samp_y = my_point->y;
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough, samp_y);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.trough, my_pulse.fall);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.fall);
	DP_graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.rise);
}

void cycle(Point *my_point, dFrame *my_frame, configDPV my_pulse)
{
	unsigned int z = my_pulse.amount;
	float ri = my_pulse.rise;
	float peri = my_pulse.period;
	while (z != 0) {
		DPV_graph(my_frame, my_pulse, my_point);
		peri = peri + my_pulse.period;
		my_pulse.trough = my_pulse.trough + my_pulse.period;
		my_pulse.peak = my_pulse.peak + my_pulse.period;
		my_pulse.rise = my_pulse.rise + my_pulse.incre;
		my_pulse.fall = my_pulse.fall + my_pulse.incre;
		--z;
	}
	z = my_pulse.amount;
	my_pulse.fall = my_pulse.fall - my_pulse.incre - ri;
	my_pulse.rise = my_pulse.rise - ri - my_pulse.incre;
	while (z != 0) {
		DPV_graph_dec(my_frame, my_pulse, my_point);
		peri = peri + my_pulse.period;
		my_pulse.trough = my_pulse.trough + my_pulse.period;
		my_pulse.peak = my_pulse.peak + my_pulse.period;
		my_pulse.rise = my_pulse.rise - my_pulse.incre;
		my_pulse.fall = my_pulse.fall - my_pulse.incre;
		--z;
	}
}
void DPV_ex(dFrame *my_frame, Point *my_point, Values my_pulse)
{
	my_pulse = DPV_findValues();
	float row = (my_pulse.period * ((my_pulse.amount * 2))) +
		    (my_pulse.rise * (my_pulse.amount * 2)) +
		    ((my_pulse.rise - my_pulse.incre) *
		     (my_pulse.amount * 2)); /*array.max_my_pulse;*/
	Point *memory = (Point *)malloc(row * sizeof(Point));
	//Point *my_point = (Point *)malloc(sizeof(Point));
	my_point->x = 0;
	my_point->y = 0;

	*my_frame = init_frame(memory, row);
	cycle(my_point, my_frame, my_pulse);
	printArrayToFile(my_frame->memory, row, "new_array_DPV.txt");
	free(my_point);
	free(memory);
}