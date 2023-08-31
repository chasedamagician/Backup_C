#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct SqValues{
    float axis;
    float period;
    float rise;
    float incre;
    float value;/*Distance between points*/
    int i;

    unsigned int amount;
} configSq;
typedef struct rowValues{
    float* memory;
    int current;
    int max_values;
}configRow;

configSq findValues(void){
    configSq c;
    printf("Enter the axis equation: ");
    scanf("%f",&c.axis);
    printf("Enter the length of the period: ");
    scanf("%f",&c.period);
    printf("Enter a height of the rise: ");
    scanf("%f",&c.rise);
    printf("Enter the size of the increment: ");
    scanf("%f",&c.incre);
    printf("Enter the distance between each point: ");
    scanf("%f",&c.value);
    printf("Enter the number of periods: ");
    scanf("%u",&c.amount);
    c.i = 0;
    return c;
}
configRow setValues(void){
    configRow x;
    configSq values = findValues();
    x.memory = 0;
    float rise = values.rise + values.axis;
    x.current = 0;
    x.max_values = (values.period * ((values.amount*2)-1)) + ((rise * ((values.amount*2)))*2);


}
void SW_mem(float** memory, int *i, float *x_ptr, float *y_ptr) {
    memory[*i][0] = *x_ptr;
    memory[*i][1] = *y_ptr;
}

int compare_Values(float *y_ptr, float comp_Value){
    int retur;
    if(fabs(*y_ptr - comp_Value)<0.000001){
        retur = 1;
    }
    else{
        retur = 0;
    }
    return retur;
}
int compare_Valuesx(float *x_ptr, float comp_Value){
    int retur;
    if(fabs(*x_ptr - comp_Value)<0.000001){
        retur = 1;
    }
    else{
        retur = 0;
    }
    return retur;
}
void graph(float** memory, int* i_ptr, float *x_ptr, float comp1, float *y_ptr, float comp2, float val) {
    if (compare_Values(y_ptr, comp2) == 1 && *x_ptr < comp1) {
        //printf("New Logic\n");
        while (*x_ptr < comp1) {
            *x_ptr = *x_ptr + val;
            //printf("%0.6f, %0.6f\n", *x_ptr, *y_ptr);
            SW_mem(memory, i_ptr, x_ptr, y_ptr);
            //printf("Row#1: %d\n", *i_ptr);
            ++(*i_ptr);
        }
    } else if (compare_Valuesx(x_ptr, comp1) == 1 && *y_ptr < comp2) {
        printf("New Logic\n");
        printf("Rise Actual Height: %f\n",comp2);
        while (*y_ptr < comp2) {
            *y_ptr = *y_ptr + val;
            //printf("%0.6f, %0.6f\n", *x_ptr, *y_ptr);
            SW_mem(memory, i_ptr, x_ptr, y_ptr);
            //printf("Row#2: %d\n", *i_ptr);
            ++(*i_ptr);
        }
    } else if (compare_Valuesx(x_ptr, comp1) == 1 && *y_ptr > comp2) {
        //printf("New Logic\n");
        while (*y_ptr > comp2) {
            *y_ptr = *y_ptr - val;
            //printf("%0.6f, %0.6f\n", *x_ptr, *y_ptr);
            SW_mem(memory, i_ptr, x_ptr, y_ptr);
            //printf("Row#3: %d\n", *i_ptr);
            ++(*i_ptr);
        }
    } else if (compare_Values(y_ptr, comp2) == 1 && *x_ptr > comp1) {
        //printf("New Logic\n");
        while (*x_ptr > comp1) {
            *x_ptr = *x_ptr - val;
            //printf("%0.6f, %0.6f\n", *x_ptr, *y_ptr);
            SW_mem(memory, i_ptr, x_ptr, y_ptr);
            //printf("Row#4: %d\n", *i_ptr);
            ++(*i_ptr);
        }
    }
}

void SW_graph(float** memory,int *i_ptr,float *x_ptr,float *y_ptr, float axis, float axi, float ris, float per, float pea, float inc, float fal,float val){
    /*y=axis-inc;*/
    //float *y_ptr = &axis;

    
    float p_h = *x_ptr;//Place holder variable
    //printf("%0.6f, %0.6f\n", *x_ptr,*y_ptr);
    //printf("Rise Height: %f\n",ris);
    //printf("Axis Height: %f\n",axis);
    graph(memory,i_ptr,x_ptr,p_h,y_ptr,ris,val);
    graph(memory,i_ptr,x_ptr,pea, y_ptr, ris,val);
    graph(memory,i_ptr,x_ptr,pea,y_ptr,axis,val);
    graph(memory,i_ptr,x_ptr,pea,y_ptr,fal,val);
    graph(memory,i_ptr,x_ptr,per,y_ptr,fal,val);
    graph(memory,i_ptr,x_ptr,per,y_ptr,axis,val);


}
void SW_graph_dec(float** memory, int *i_ptr, float *x_ptr, float *y_ptr, float axis,float axi, float ris, float per, float pea, float inc, float fal,float val,float check){
    //float *y_ptr = &axis;
    float p_h = *x_ptr;
    //printf("%0.6f, %0.6f\n", *x_ptr,*y_ptr);
    //printf("Rise Height: %f\n",ris);
    //printf("Axis Height: %f\n",axis);
    graph(memory,i_ptr,x_ptr,p_h,y_ptr,ris, val);
    graph(memory,i_ptr,x_ptr,pea,y_ptr,ris,val);
    graph(memory,i_ptr,x_ptr,pea,y_ptr,axis,val);
    graph(memory,i_ptr,x_ptr,pea,y_ptr,fal,val);
    graph(memory,i_ptr,x_ptr,per,y_ptr,fal,val);
    graph(memory,i_ptr,x_ptr,per,y_ptr,axis,val);
    
}
void printArray(float** array, int size) {
    printf("Coordinates:\n");
    for (int i = 0; i < size; i++) {
        printf("Coordinate %d: (%.2f, %.2f)\n", i + 1, array[i][0], array[i][1]);
    }
}
void cycle(float** memory,int *i_ptr,float row, float *x_ptr, float *y_ptr,float axis, float ris, float per,  float pea, float inc, float fal,float val,unsigned int amount){
   unsigned int z = amount;
   int num_points = (int)row/((amount/2)-1);
   float axi = axis;
   float peri = per;
   while(z != 0){
        
        SW_graph(memory,i_ptr,x_ptr,y_ptr,axis,axi,ris, per, pea, inc, fal, val);
        //printArray(memory,row);
        axis = axis+axi;
        graph(memory,i_ptr,x_ptr,per,y_ptr,axis,val);

        pea = pea + peri;
        per = peri+per;
        ris = ris+inc;
        fal = fal + inc;
        --z;
        /*if(z==1){
            fal = fal-inc;
        }*/
        
        
   }
   z=amount-1;
   ris = axis;
   axis = axis-2*inc;
   //printf("New Axis Value: %f\n", axis);
   fal = fal - 2*inc;
    float check;
    while(z!= 0){
        
        SW_graph_dec(memory,i_ptr,x_ptr,y_ptr,axis,axi,ris, per, pea, inc, fal, val,check);
        //printArray(memory,row);
        /*printf("%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f, %0.6f,%0.6f\n", x,y,axis,ax,ris,per,pea,ris,fal);*/
       
        axis = axis-axi;
        
         if (z==1 && *y_ptr== axi){
            break;
        }
        
        
        pea = pea + peri;
        per = peri+per;
        ris = ris- inc;
        fal = fal - inc;
        --z;
        //printf("%d",z);
        --check;
        
        
        
   }

}

int main (){
    float x,y, period, peak, rise, fall;
    unsigned int amount;
    int i =0;
    int* i_ptr = &i;
    FILE *ptr_fp;
    configSq values;
    configRow array;
    int col = 2;
    

    
    

    
    
    values = findValues(); 
    array = setValues();
    float axi = values.axis;
    rise = values.rise + values.axis;
    
    peak = values.period/2;
    /*incre = values.incre;*/
    fall = values.axis - values.rise;
    //value=values.value;*/
    float row = (values.period * ((values.amount*2)-1)) + ((rise * ((values.amount*2)))*2);//+ (values.incre*((values.amount))));
    float** memory = (float**)malloc(row * sizeof(float*));
    for (int i = 0; i < row; i++) {
        memory[i] = (float*)malloc(2 * sizeof(float)); // Each coordinate has x and y
    }
    array.memory = memory;
    x=0;
    y=values.axis;
    float *x_ptr =&x;
    float *y_ptr = &y;

    //float* p = (float*)memory;/*This is wrong, find what to do with it later*/
    
    /*
    if((ptr_fp = fopen("text2.txt", "wb")) == NULL)
		{
			perror("Unable to open file!\n");
			exit(1);
		}else printf("Opened file successfully for writing.\n");

		 Part D 
		if( fwrite(p, 10*sizeof(float)+sizeof(int), 1, ptr_fp) != 1)
		{
			printf("Write error!\n");
			exit(1);
		}else printf("Write was successful.\n");
		fclose(ptr_fp);
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%.2f ", memory[i][j]);
        }
        printf("\n");
    }*/
    //printf("# of rows: %f\n",row);
    cycle(memory,i_ptr, row,x_ptr,y_ptr,values.axis, rise, values.period,  peak, values.incre, fall, values.value,values.amount);
    printArray(memory,row);
    for (int i = 0; i < row; i++) {
        free(memory[i]);
    }
    free(memory);
}