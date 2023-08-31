#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct SqValues{
    float axis;
    float period;
    float rise;
    float peak;
    float fall;
    float incre;
    float value;/*Distance between points*/
    int i; 

    unsigned int amount;
} configSq;
typedef struct point{
    float x;
    float y;
}Point;
typedef struct Frame{
    Point* memory;
    int loc;
    int max_val;
}dFrame;
dFrame init_frame(Point *memory, unsigned int max_val){
    dFrame ret = 
        {
        .memory = memory
        ,   .loc = 0
        ,   .max_val = max_val
        };
    return ret;
}
void insert_point( Point point2d, dFrame *frame){
    frame -> memory[frame->loc] = point2d; //Takes the valeus from the struct and sets that portion of memory tot he specific coordinates
    if (frame -> loc < frame -> max_val){
        frame -> loc++;
    }
    
}

//void reset_point -> Work on this later

configSq findValues(void){
    configSq c;
    printf("Enter the axis equation: ");
    scanf(" %f",&c.axis);
    printf("Enter the length of the period: ");
    scanf(" %f",&c.period);
    printf("Enter a height of the rise: ");
    scanf(" %f",&c.rise);
    printf("Enter the size of the increment: ");
    scanf(" %f",&c.incre);
    printf("Enter the distance between each point: ");
    scanf(" %f",&c.value);
    printf("Enter the number of periods: ");
    scanf(" %u",&c.amount);
    c.rise = c.rise+c.axis;
    c.peak = c.period/2;
    c.fall = c.axis - c.rise;
    c.i = 0;
    return c;
}


void SW_mem(float** memory, int i, float x, float y) {
    memory[i][0] = x;
    memory[i][1] = y;
}

int compare_Values(float y, float comp_Value){
    int retur;
    if(fabs(y - comp_Value)<0.000001){
        retur = 1;
    }
    else{
        retur = 0;
    }
    return retur;
}
int compare_Valuesx(float x, float comp_Value){
    int retur;
    if(fabs(x - comp_Value)<0.000001){
        retur = 1;
    }
    else{
        retur = 0;
    }
    return retur;
}
void graph(dFrame *my_frame, configSq my_square, Point my_point, float comp1, float comp2) {
    
    //printf("First Coordinates: %f, %f", x,y);
    if (compare_Values(my_point.y, comp2) == 1 && my_point.x < comp1) {
        //printf("New Logic\n");
        while (my_point.x < comp1) {
            my_point.x = my_point.x + my_square.value;
            //printf("%0.6f, %0.6f\n", x, y);
            insert_point(my_point, my_frame);
            //SW_mem(memory, i, x , y);
            //printf("Row#1: %d\n", i);
        }
    } else if (compare_Valuesx(my_point.x , comp1) == 1 && my_point.y < comp2) {
        //printf("New Logic\n");
        //printf("Rise Actual Height: %f\n",comp2);
        while (my_point.y < comp2) {
            my_point.y = my_point.y + my_square.value;
            insert_point(my_point,my_frame);
            //printf("%0.6f, %0.6f\n", x, y);
            //SW_mem(memory, i, x , y);
            //printf("Row#2: %d\n", i);
            //++(i);
        }
    } else if (compare_Valuesx(my_point.x , comp1) == 1 && my_point.y > comp2) {
        //printf("New Logic\n");
        while (my_point.y > comp2) {
            my_point.y = my_point.y - my_square.value;
            insert_point(my_point, my_frame);
            //printf("%0.6f, %0.6f\n", x, y);
            //SW_mem(memory, i, x , y);
            //printf("Row#3: %d\n", i);
            //++(i);
        }
    } else if (compare_Values(my_point.y, comp2) == 1 && my_point.x > comp1) {
        //printf("New Logic\n");
        while (my_point.x > comp1) {
            my_point.x = my_point.x - my_square.value;
            insert_point(my_point, my_frame);
            //printf("%0.6f, %0.6f\n", x, y);
            //SW_mem(memory, i, x , y);
            //printf("Row#4: %d\n", i);
            //++(i);
        }
    }
}

void SW_graph(dFrame *my_frame, configSq my_square, Point my_point){

    dFrame array;
    
    float p_h = my_point.x;//Place holder variable
    graph(my_frame, my_square, my_point,p_h,my_square.rise);
    graph(my_frame, my_square, my_point,my_square.peak,my_square.rise);
    graph(my_frame, my_square, my_point,my_square.peak,my_square.axis);
    graph(my_frame, my_square, my_point,my_square.peak,my_square.fall);
    graph(my_frame, my_square, my_point,my_square.period,my_square.fall);
    graph(my_frame, my_square, my_point,my_square.period,my_square.axis);


}

void printArray(dFrame *frame, int size) {
    printf("Coordinates:\n");
    for (int i = 0; i < size; i++) {
        printf("Coordinate %d: (%.2f, %.2f)\n", i + 1, frame->memory[i].x, frame->memory[i].y);
    }
}
void cycle(Point my_point, dFrame *my_frame, configSq my_square,int row){
   unsigned int z = my_square.amount;
   int num_points = (int)row/((my_square.amount/2)-1);
   float axi = my_square.axis;
   float peri = my_square.period;
   while(z != 0){
        
        SW_graph(my_frame,my_square,my_point);
        //printArray(memory,row);
        my_square.axis = my_square.axis+axi;
        graph(my_frame,my_square, my_point,my_square.period,my_square.axis);

        my_square.peak = my_square.peak + peri;
        my_square.period = peri+my_square.period;
        my_square.rise = my_square.rise+my_square.incre;
        my_square.fall = my_square.fall + my_square.incre;
        --z;
        /*if(z==1){
            my_square.fall = my_square.fall-my_square.incre;
        }*/
        
        
   }
   z=my_square.amount-1;
   my_square.rise = my_square.axis;
   my_square.axis = my_square.axis-2*my_square.incre;
   //printf("New my_square.axis my_square.valueue: %f\n", my_square.axis);
   my_square.fall = my_square.fall - 2*my_square.incre;
    float check;
    while(z!= 0){
        
        SW_graph(my_frame,my_square,my_point);
        //printArray(memory,row);
        /*printf("%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f, %0.6f,%0.6f\n", x,y,my_square.axis,ax,my_square.rise,my_square.period,my_square.peak,my_square.rise,my_square.fall);*/
       
        my_square.axis = my_square.axis-axi;
        
         if (z==1 && my_point.y== axi){
            break;
        }
        
        
        my_square.peak = my_square.peak + peri;
        my_square.period = peri+my_square.period;
        my_square.rise = my_square.rise- my_square.incre;
        my_square.fall = my_square.fall - my_square.incre;
        --z;
        //printf("%d",z);
        --check;
        
        
        
   }

}

int main (){
    //float x,y, period, peak, rise, fall;
    //unsigned int amount;
    
    FILE *ptr_fp;
    configSq my_square;
    dFrame my_frame;
    

    
    

    
    
    my_square = findValues(); 
    //array = setValues(&values);
    
    float row = (my_square.period * ((my_square.amount*2)-1)) + ((my_square.rise * ((my_square.amount*2)))*2);//array.max_my_square;
    int rows = (int)row;
    Point* memory = (Point*)malloc( row * sizeof(Point));
    Point my_point = 
        {
            .x = 0,
            .y = my_square.axis
        };

    my_frame = init_frame(memory,row);
    //float** memory = (float**)malloc(row * sizeof(float*));

    //for (int i = 0; i < row; i++) {
      //  memory[i] = (float*)malloc(2 * sizeof(float)); // Each coordinate has x and y
    //}
    
    
    cycle(my_point, &my_frame,my_square,row);
    printArray(&my_frame,row);
    //free(my_frame);
    free(memory);
}