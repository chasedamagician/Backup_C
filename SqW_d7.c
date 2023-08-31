#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct SqValues{
    float axis;
    float period;
    float rise;
    float incre;
    float value;/*Distance between points*/
    unsigned int amount;
} configSq;

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
    
    return c;
}
void SW_mem(float** memory, int i, float x, float y) {
    memory[i][0] = x;
    memory[i][1] = y;
}

int compare_Values(float num, float comp_Value){
    int retur;
    if(fabs(num - comp_Value)<0.000001){
        retur = 1;
    }
    else{
        retur = 0;
    }
    return retur;
}
void graph(float** memory , float i, float v1,float comp1,float v2,float comp2,float val){
    if(compare_Values(v2,comp2) == 1 && v1 < comp1){
        while(v1<comp1){
            v1 = v1 +val;
            printf("%0.6f, %0.6f\n", v1,v2);
            SW_mem(memory, i, v1, v2);
            ++i;
            
        }
    }
    else if(compare_Values(v1,comp1) == 1 && v2 < comp2){
        while(v2<comp2){
            v2 = v2+val;
            printf("%0.6f, %0.6f\n", v1,v2);
            SW_mem(memory, i, v1, v2);
            ++i;
        }
    }
    else if(compare_Values(v1,comp1) == 1 && v2 > comp2){
        while(v2>comp2){
            v2 = v2 -val;
            printf("%0.6f, %0.6f\n", v1,v2);
            SW_mem(memory, i, v1, v2);
            ++i;
        }
        

    }
    else if(compare_Values(v2,comp2) == 1 && v1 > comp1){
        while(v1>comp1){
            v1 = v1 -val;
            printf("%0.6f, %0.6f\n", v1,v2);
            SW_mem(memory, i, v1, v2);
            ++i;
        }
        

    }
    
}

void SW_graph(float** memory,int i,float x, float axis, float ris, float per, float pea, float inc, float fal,float val){
    /*y=axis-inc;*/
    float y = axis;
    float place_holder = 0;
    printf("%0.6f, %0.6f\n", x,y);
    graph(memory,i,x,0,y,ris,val);
    graph(memory,i,x,pea, y, ris,val);
    graph(memory,i,x,pea,y,axis,val);
    graph(memory,i,x,pea,y,fal,val);
    graph(memory,i,x,per,y,fal,val);
    graph(memory,i,x,per,y,axis,val);
    /*while (y != ris){
        y=y+val;
        SW_mem(memory, i, x, y);
        i++;

        printf("%0.6f, %0.6f\n", x,y);
    }*/
    /*
    if(compare_Values(y,ris) == 1 && x < pea){
        while(x<pea){
            x=x+val;
            SW_mem(memory, i, x, y);
            i++;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }*/
    /*
    if (compare_Values(x,pea) == 1 && y == ris){
        while(y>axis){
            y= y - val;
            SW_mem(memory, i, x, y);
            i++;
            
            printf("%0.6f, %0.6f\n", x,y);

        }
    }*/
    /*
    if(compare_Values(y,axis) == 1 && compare_Values(x,pea) == 1){
        while(y> fal){
            y=y-val;
            SW_mem(memory, i, x, y);
            i++;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }*/
    /*
    if(compare_Values(y,fal) == 1 && x == pea){
        while(x < per){
            x=x+val;
            SW_mem(memory, i, x, y);
            i++;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }*/
    /*if(y== fal &&compare_Values(x,per) == 1){
        while(y< axis){
            y=y+val;
            SW_mem(memory, i, x, y);
            i++;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }*/

}
void SW_graph_dec(float** memory, int i, float x, float axis, float ris, float per, float pea, float inc, float fal,float val,float check){
    float y = axis;
    printf("%0.6f, %0.6f\n", x,y);
    graph(memory,i,x,0,y,ris, val);
    graph(memory,i,x,pea,y,ris,val);
    graph(memory,i,x,pea,y,axis,val);
    graph(memory,i,x,pea,y,fal,val);
    graph(memory,i,x,per,y,fal,val);
    graph(memory,i,x,per,y,axis,val);
    /*
    while(y < ris){
        y= y+val;
        SW_mem(memory, i, x, y);
        i++;
        printf("%0.6f, %0.6f\n", x,y);
    }
    if (compare_Values(y,ris) == 1 && x < pea){
        while(x<pea){
            x=x+val;
            SW_mem(memory, i, x, y);
            i++;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }
    while (y != axis){
        y=y-val;
        SW_mem(memory, i, x, y);
        i++;
        printf("%0.6f, %0.6f\n", x,y);
    }
    while (y != fal){
        y=y-val;
        SW_mem(memory, i, x, y);
        i++;
        printf("%0.6f, %0.6f\n", x,y);
    }
    if(compare_Values(y,fal) == 1 && x < per){
        while(x<per){
            x=x+val;
            SW_mem(memory, i, x, y);
            i++;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }
    if (x == per && y == fal){
        while(y<axis){
            y= y +val;
            SW_mem(memory, i, x, y);
            i++;
            printf("%0.6f, %0.6f\n", x,y);

        }
    }*/
    
}
void printArray(float** array, int size) {
    printf("Coordinates:\n");
    for (int i = 0; i < size; i++) {
        printf("Coordinate %d: (%.2f, %.2f)\n", i + 1, array[i][0], array[i][1]);
    }
}
void cycle(float** memory,int i,float row, float x, float axis, float ris, float per,  float pea, float inc, float fal,float val,unsigned int amount){
   unsigned int z = amount;
   float y = axis;
   float axi = axis;
   float peri = per;
   while(z != 0){
        
        SW_graph(memory,i,x,axis,ris, per, pea, inc, fal, val);
        //printArray(memory,row);
        axis = axis+axi;
        while(x == per && y<axis){
            y=y+val;
            //printf("%0.6f, %0.6f\n", x,y);
        }
        x = x + peri;
        
        pea = pea + peri;
        per = peri+per;
        ris = ris+inc;
        fal = fal + inc;
        --z;
        if(z==1){
            fal = fal-inc;
        }
        
        
   }
   z=amount-1;
   ris = axis;
   axis = axis-2*axi;
   
   fal = fal - 2*inc;
    float check;
    while(z!= 0){
        
        SW_graph_dec(memory,i,x,axis,ris, per, pea, inc, fal, val,check);
        //printArray(memory,row);
        /*printf("%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f, %0.6f,%0.6f\n", x,y,axis,ax,ris,per,pea,ris,fal);*/
       
        axis = axis-axi;
        
         if (z==1 && y== axi){
            break;
        }
        
       
        x = x + peri;
            
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
    FILE *ptr_fp;
    configSq values;
   
    int col = 2;
    

    
    

    
    
    values = findValues(); 
    
    rise = values.rise + values.axis;
    
    peak = values.period/2;
    /*incre = values.incre;*/
    fall = values.axis - values.rise;
    //value=values.value;*/
    float row = (values.period * ((values.amount*2)-1)) + ((rise * ((values.amount*2)-1))*2 + (values.incre*((values.amount*2)-1)));
    float** memory = (float**)malloc(row * sizeof(float*));
    for (int i = 0; i < row; i++) {
        memory[i] = (float*)malloc(2 * sizeof(float)); // Each coordinate has x and y
    }
    x=0;
   
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
    printf("# of rows: %f\n",row);
    cycle(memory,i, row,x,values.axis, rise, values.period,  peak, values.incre, fall, values.value,values.amount);
    
    for (int i = 0; i < row; i++) {
        free(memory[i]);
    }
    free(memory);
}