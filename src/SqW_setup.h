#ifndef SqW_SETUP_H
#define SqW_SETUP_H
#include "setup.h"

Values SqW_findValues(void);
void SqW_graph(dFrame *frame, Values my_graph, Point *my_point, float comp1,
	   float comp2);
void SW_graph(dFrame *my_frame, Values my_graph, Point *my_point);
void SW_cycle(Point *my_point, dFrame *my_frame, Values my_graph);
void SqW_ex(dFrame *frame, Point *point, Values my_tri);




#endif