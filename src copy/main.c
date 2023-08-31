#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SqW_setup.h"
#include "DPV_setup.h"
#include "CV_setup.h"
int main(void)
{
    dFrame my_frame; // Declare my_frame variable here
    Point *my_point = (Point *)malloc(sizeof(Point)); // Declare my_point variable here
	int ans;
	printf("What do you want to Graph? 0(CV), 1(DPV), 2(SqW))") ;
    scanf("%d", &ans);

	if (ans == 0) {
        printf("CV\n");
        Values my_tri; // Declare my_tri variable here
		CV_ex(&my_frame, my_point, my_tri);
	}
    else if (ans == 1){
        printf("DPV\n");
        Values my_pulse; // Declare my_tri variable here
        DPV_ex(&my_frame,my_point, my_pulse);
    }
    else if(ans ==2){
        printf("SW\n");
        Values my_square; // Declare my_tri variable here
        SqW_ex(&my_frame,my_point,my_square);
    }
    else{
        printf("Invalid answer");
    }
    return(0);
}