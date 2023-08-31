#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*Structure to store values for the CV waveform*/
typedef struct CValues
{
float period;
float height;
float increx;
float increy;
float slope;
unsigned int amount;
unsigned int midp;
float starting_y;
} configTri;
/*Defines the variables used in the coordinates*/
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
float current_y;
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
frame->memory[frame->loc].y = frame->current_y;
if (frame->loc < frame->max_val)
{
frame->loc++;
}
else
{
reset_point(frame);
}
}

/*methods for defining the values*/
configTri findValues(void)
{
configTri c;
printf("Enter a length of period: ");
scanf("%f", &c.period);
printf("Enter an altitude: ");
scanf("%f", &c.height);
printf("Enter an increment: ");
scanf("%f", &c.increx);
printf("Enter the amount of periods: ");
scanf("%u", &c.amount);
printf("Enter the starting y value: ");
scanf("%f" , &c.starting_y);
c.midp = c.period / 2;
c.slope = c.height / (c.period / 2);
c.increy = c.increx * c.slope;
c.height = c.height + c.starting_y;
return (c);
}

/*Used to compare the values of floats*/
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
/*Function used to print the array into a text file*/
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
/*Sets up the logic to graph the CV plot*/
void graph(dFrame *my_frame, configTri my_tri, Point *my_point,
float comp1, float comp2)
{
if (my_point->x <= comp1 && my_frame->current_y < comp2)
{
while (my_point->x < comp1 && my_frame->current_y < comp2)
{
my_point->x = my_point->x + my_tri.increx;
my_frame->current_y = my_frame->current_y + my_tri.increy;
insert_point(my_point, my_frame);
}
}
else if (my_point->x <= comp1 && my_frame->current_y > comp2)
{
while (my_point->x < comp1 && my_frame->current_y > comp2)
{
my_point->x = my_point->x + my_tri.increx;
my_frame->current_y = my_frame->current_y - my_tri.increy;
insert_point(my_point, my_frame);
}
}
}
/*Prints the coordinates in*/
void printArray(dFrame *frame, int size)
{
printf("Coordinates:\n");
for (int i = 0; i < size; i++)
{
printf("Coordinate %d: (%.2f, %.2f)\n", i + 1, frame->memory[i].x,
frame->memory[i].y);
}
}
/*Function for producing a singular CV waveform*/
void triangle(dFrame *my_frame, configTri my_tri, Point *my_point)
{
graph(my_frame, my_tri, my_point, my_tri.midp, my_tri.height);
graph(my_frame, my_tri, my_point, my_tri.period, my_tri.starting_y);


}
/*Method to produce multiple periods*/
void cycle(Point *my_point, dFrame *my_frame, configTri my_tri/*, int row*/)
{
float z = my_tri.amount;
my_frame->current_y = my_tri.starting_y;
while (z != 0)
{
triangle(my_frame, my_tri, my_point);
my_tri.midp = my_tri.midp + my_tri.period;
my_tri.period = my_tri.period + my_tri.period;
--z;
}

}


int main(void)
{
configTri my_tri;
/*FILE *ptr_fp;*/
dFrame my_frame;

my_tri = findValues();
float row = my_tri.period * my_tri.amount;
Point *memory = (Point *)malloc( row * sizeof(Point));
Point *my_point = (Point *)malloc(sizeof(Point));
my_point->x = 0;

my_frame = init_frame(memory, row);
cycle(my_point, &my_frame, my_tri/*,row*/);
printArray(&my_frame, row);
printArrayToFile(my_frame.memory, row, "new_array_CV.txt");
free(my_point);
free(memory);
return (0);
}




