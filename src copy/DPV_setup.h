#ifndef DPV_SETUP_H
#define DPV_SETUP_H
#include "setup.h"

Values DPV_findValues(void);
void DP_graph(dFrame *frame, Values my_graph, Point *my_point, float comp1,
	   float comp2);
void DPV_graph(dFrame *my_frame, Values my_graph, Point *my_point);
void DPV_graph_dec(dFrame *my_frame, Values my_graph, Point *my_point);
void cycle(Point *my_point, dFrame *my_frame, Values my_graph);
void DPV_ex(dFrame *frame, Point *point, Values my_tri);


#endif