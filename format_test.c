#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*Sets the main values for the square wave*/
typedef struct SqValues
{
  float axis;          /*The point of the axis on the graph*/
  float period;        /*The length of a single instance of the plot*/
  float rise;          /*The max height of the plot*/
  float peak;          /*The width of the peak*/
  float fall;          /*The lowest height of the plot*/
  float incre;         /*The value that the points increase or decrease by*/
  float value;         /*Distance between points*/
  int i;               /*Starting row number*/
  unsigned int amount; /*Number of periods*/
} configSq;
/*Sets the values for the x and y coordinates*/
typedef struct point
{
  float x;
  float y;
} Point;
/*Sets the values for the array we are using to store the points*/
typedef struct Frame
{
  Point *memory; /*The array*/
  int loc;       /*Location in the area(Row Number)*/
  int max_val;
} dFrame;
/*Sets up the array and sets the row number to 0*/
dFrame
init_frame (Point *memory, int max_val)
{
  dFrame ret = { .memory = memory, .loc = 0, .max_val = max_val };
  return (ret);
}
void
reset_point (dFrame *frame)
{
  frame->loc = 0;
}
/*Inserts a new point onto the array*/
void
insert_point (Point *point2d, dFrame *frame)
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
      reset_point (frame);
    }
}

/*Gets the values for the variables*/
configSq
findValues (void)
{
  configSq c;
  printf ("Enter the axis equation: ");
  scanf (" %f", &c.axis);
  printf ("Enter the length of the period: ");
  scanf (" %f", &c.period);
  printf ("Enter a height of the rise: ");
  scanf (" %f", &c.rise);
  printf ("Enter the size of the increment: ");
  scanf (" %f", &c.incre);
  printf ("Enter the distance between each point: ");
  scanf (" %f", &c.value);
  printf ("Enter the number of periods: ");
  scanf (" %u", &c.amount);
  c.fall = c.axis - c.rise;
  c.rise = c.rise + c.axis;
  c.peak = c.period / 2;

  c.i = 0;
  return (c);
}
/*Allows the program to compare float variables*/
int
compare_Values (float y, float comp_Value)
{
  int retur;
  if (fabs (y - comp_Value) < 0.000001)
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
void
printArrayToFile (Point *memory, int row, const char *filename)
{
  /* Open the file for writing*/
  FILE *file = fopen (filename, "w");

  /* Check if the file was opened successfully*/
  if (file == NULL)
    {
      printf ("Error opening file.\n");
      return;
    }

  /* Loop through the array and write each element to the file*/
  for (int i = 0; i < row; i++)
    {
      fprintf (file, "%.2f,%.2f\n ", memory[i].x, memory[i].y);
    }

  /* Close the file*/
  fclose (file);
}
/*Holds the logic for graphign the voltammogram*/
void
graph (dFrame *my_frame, configSq my_square, Point *my_point, float comp1,
       float comp2)
{

  if (compare_Values (my_point->y, comp2) == 1 && my_point->x < comp1)
    {

      while (my_point->x < comp1)
        {
          my_point->x = my_point->x + my_square.value;
          insert_point (my_point, my_frame);
        }
    }
  else if (compare_Values (my_point->x, comp1) == 1 && my_point->y < comp2)
    {
      while (my_point->y < comp2)
        {
          my_point->y = my_point->y + my_square.value;
          insert_point (my_point, my_frame);
        }
    }
  else if (compare_Values (my_point->x, comp1) == 1 && my_point->y > comp2)
    {
      while (my_point->y > comp2)
        {
          my_point->y = my_point->y - my_square.value;
          insert_point (my_point, my_frame);
        }
    }
  else if (compare_Values (my_point->y, comp2) == 1 && my_point->x > comp1)
    {
      while (my_point->x > comp1)
        {
          my_point->x = my_point->x - my_square.value;
          insert_point (my_point, my_frame);
        }
    }
}
/*The function graphs a single period of the plot*/
void
SW_graph (dFrame *my_frame, configSq my_square, Point *my_point)
{
  float p_h = my_point->x; /*Place holder variable*/
  graph (my_frame, my_square, my_point, p_h, my_square.rise);
  graph (my_frame, my_square, my_point, my_square.peak, my_square.rise);
  graph (my_frame, my_square, my_point, my_square.peak, my_square.axis);
  graph (my_frame, my_square, my_point, my_square.peak, my_square.fall);
  graph (my_frame, my_square, my_point, my_square.period, my_square.fall);
  graph (my_frame, my_square, my_point, my_square.period, my_square.axis);
}
/*Prints the array*/
void
printArray (dFrame *frame, int size)
{
  printf ("Coordinates:\n");
  for (int i = 0; i < size; i++)
    {
      printf ("Coordinate %d: (%.2f, %.2f)\n", i + 1, frame->memory[i].x,
              frame->memory[i].y);
    }
}
/*this function plots the voltammogram, ascending and descending*/
void
cycle (Point *my_point, dFrame *my_frame, configSq my_square)
{
  unsigned int z = my_square.amount;
  /*int num_points = (int)row/((my_square.amount/2)-1);*/
  float axi = my_square.axis;
  float peri = my_square.period;
  while (z != 0)
    {

      SW_graph (my_frame, my_square, my_point);
      my_square.axis = my_square.axis + axi;
      graph (my_frame, my_square, my_point, my_square.period, my_square.axis);

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

  while (z != 0)
    {

      SW_graph (my_frame, my_square, my_point);

      my_square.axis = my_square.axis - axi;

      if (z == 1 && my_point->y == axi)
        {
          break;
        }

      my_square.peak = my_square.peak + peri;
      my_square.period = peri + my_square.period;
      my_square.rise = my_square.rise - my_square.incre;
      my_square.fall = my_square.fall - my_square.incre;
      --z;
    }
}

int
main (void)
{
  configSq my_square;
  dFrame my_frame;
  my_square = findValues ();
  float row = (my_square.period * ((my_square.amount * 2) - 1))
              + ((my_square.rise * ((my_square.amount * 2))) * 2);
  Point *memory = (Point *)malloc (row * sizeof (Point));
  Point *my_point = (Point *)malloc (sizeof (Point));
  my_point->x = 0;
  my_point->y = my_square.axis;
  my_frame = init_frame (memory, row);
  cycle (my_point, &my_frame, my_square);
  printArray (&my_frame, row);
  printArrayToFile (my_frame.memory, row, "new_array.txt");
  free (my_point);
  free (memory);
  return (0);
}