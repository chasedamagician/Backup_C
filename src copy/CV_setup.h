#ifndef CV_SETUP_H
#define CV_SETUP_H
#include "setup.h"

Values CV_findValues(void);
void CV_graph(dFrame *frame, Values my_graph, Point *my_point, float comp1,
	   float comp2);
void triangle(dFrame *my_frame, Values my_graph, Point *my_point);
void CV_cycle(Point *my_point, dFrame *my_frame, Values my_graph);
void CV_ex(dFrame *frame, Point *point, Values my_tri);

#endif 