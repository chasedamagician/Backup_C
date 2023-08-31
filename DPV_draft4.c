#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct DPValues
{
float rise;
float fall;
float period;
float peak;/*Width of the peak*/
float trough;
float incre;/*Increment the y-value increses each period*/
float value;/*Distance between points*/
unsigned int amount;
float starting_y;
} configDPV;
typedef struct point
{
float x;
float y;
} Point;
/*Sets the values for the array we are using to store the points*/
typedef struct Frame
{
Point *memory;/*The array*/
int loc;/*Location in the area(Row Number)*/
int max_val;
} dFrame;
/*Sets up the array and sets the row number to 0*/
dFrame init_frame(Point *memory, int max_val)
{
dFrame ret = {
.memory = memory
,   .loc = 0
,   .max_val = max_val
};
return (ret);
}
void reset_point(dFrame *frame)
{
frame->loc = 0;
}
/*Inserts a new point onto the array*/
void insert_point(Point *point2d, dFrame *frame)
{
/*
Takes the valeus from the struct and sets that portion of memory to the
specific coordinates
*/
frame->memory[frame->loc] = *point2d;
if (frame->loc < frame->max_val)
{
frame->loc++;
}
else
{
reset_point(frame);
}
}

/* Function to get user input and set the values for the Differential Pulse waveform*/
configDPV findValues(void)
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
printf("Enter the starting y value: ");
scanf("%f" , &c.starting_y);
c.trough = c.period - c.peak;
c.peak = c.peak + (c.trough);
c.fall = c.incre+c.starting_y;
c.rise=c.rise+c.starting_y;
return (c);
}

/* Function to compare floating-point values and return 1 if they are approximately equal, otherwise 0*/
int compare_Values(float y, float comp_Value)
{
int retur;
if (fabs(y - comp_Value) < 0.000001)
{
retur = 1;
}
else
{
retur = 0;
}
return (retur);
}
/*Prints the array into a text file*/
void printArrayToFile(Point *memory, int row, const char *filename)
{
/* Open the file for writing*/
FILE *file = fopen(filename, "w");

/* Check if the file was opened successfully*/
if (file == NULL)
{
printf("Error opening file.\n");
return;
}

/* Loop through the array and write each element to the file*/
for (int i = 0; i < row; i++)
{
fprintf(file, "%.2f,%.2f\n ", memory[i].x, memory[i].y);
}

/* Close the file*/
fclose(file);
}
/*Controls the logic of the graphing of the waveform*/
void graph(dFrame *my_frame, configDPV my_pulse, Point *my_point
, float comp1, float comp2)
{


if (compare_Values(my_point->y, comp2) == 1 && my_point->x < comp1)
{

while (my_point->x < comp1)
{
my_point->x = my_point->x + my_pulse.value;
insert_point(my_point, my_frame);

}
}
else if (compare_Values(my_point->x, comp1) == 1 && my_point->y < comp2)
{
while (my_point->y < comp2)
{
my_point->y = my_point->y + my_pulse.value;
insert_point(my_point, my_frame);

}
}
else if (compare_Values(my_point->x, comp1) == 1 && my_point->y > comp2)
{
while (my_point->y > comp2)
{
my_point->y = my_point->y - my_pulse.value;
insert_point(my_point, my_frame);
}
}
else if (compare_Values(my_point->y, comp2) == 1 && my_point->x > comp1)
{
while (my_point->x > comp1)
{
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
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.trough, samp_y);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.trough, my_pulse.rise);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.rise);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.fall);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);

}
/* Function to draw a segment of the descending Differential Pulse waveform*/
void DPV_graph_dec(dFrame *my_frame, configDPV my_pulse, Point *my_point)
{
/*float htro = my_pulse.trough;*/
float samp_y = my_point->y;
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.trough, samp_y);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.trough, my_pulse.fall);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.fall);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);
graph(my_frame, my_pulse, my_point, my_pulse.peak, my_pulse.rise);
printf("Fall: %f, X: %f, Y: %f\n",my_pulse.fall, my_point->x, my_point->y);

}
/* Function to print the points of the frame to the console*/
void printArray(dFrame *frame, int size)
{
printf("Coordinates:\n");
for (int i = 0; i < size; i++)
{
printf("Coordinate %d: (%.2f, %.2f)\n", i + 1, frame->memory[i].x,
frame->memory[i].y);
}
}
/*Function to cycle through and draw the Differential Pulse waveform*/
void cycle(Point *my_point, dFrame *my_frame, configDPV my_pulse)
{
unsigned int z = my_pulse.amount;
float ri = my_pulse.rise;
float peri = my_pulse.period;
while (z != 0)
{
DPV_graph(my_frame, my_pulse, my_point);
peri = peri + my_pulse.period;
my_pulse.trough = my_pulse.trough + my_pulse.period;
my_pulse.peak = my_pulse.peak + my_pulse.period;
my_pulse.rise = my_pulse.rise + my_pulse.incre;
my_pulse.fall = my_pulse.fall + my_pulse.incre;
--z;
}
z = my_pulse.amount;
my_pulse.fall = my_pulse.fall - my_pulse.incre - ri - my_pulse.starting_y;
my_pulse.rise = my_pulse.rise - ri - my_pulse.incre+my_pulse.starting_y;
while (z != 0)
{
printf("Rise: %f", my_pulse.rise);
DPV_graph_dec(my_frame, my_pulse, my_point);
peri = peri + my_pulse.period;
my_pulse.trough = my_pulse.trough + my_pulse.period;
my_pulse.peak = my_pulse.peak + my_pulse.period;
my_pulse.rise = my_pulse.rise - my_pulse.incre;
my_pulse.fall = my_pulse.fall - my_pulse.incre;
--z;
}

}
int main(void)
{
configDPV my_pulse;
dFrame my_frame;
my_pulse = findValues();
float row = (my_pulse.period * ((my_pulse.amount * 2))) +
(my_pulse.rise * (my_pulse.amount * 2)) + 
((my_pulse.rise - my_pulse.incre) * (my_pulse.amount * 2));/*array.max_my_pulse;*/
Point *memory = (Point *)malloc(row * sizeof(Point));
Point *my_point = (Point *)malloc(sizeof(Point));
my_point->x = 0;
my_point->y = my_pulse.starting_y;

my_frame = init_frame(memory, row);
cycle(my_point, &my_frame, my_pulse);

printArray(&my_frame,row);
printArrayToFile(my_frame.memory, row, "new_array_DPV.txt");
free(my_point);
free(memory);
}