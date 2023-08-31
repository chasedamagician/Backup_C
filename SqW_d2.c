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

configSq findValues(float axis, float per,float ris, float inc,float val, unsigned int amount){
    configSq c;
    printf("Enter the axis equation: ");
    scanf("%f",&axis);
    printf("Enter the length of the period: ");
    scanf("%f",&per);
    printf("Enter a height of the rise: ");
    scanf("%f",&ris);
    
    printf("Enter the size of the increment: ");
    scanf("%f",&inc);
    printf("Enter the distance between each point: ");
    scanf("%f",&val);
    printf("Enter the number of periods: ");
    scanf("%u",&amount);
    c.axis = axis;

    c.rise = ris;
    c.period = per;
    c.incre= inc;
    c.value = val;
    c.amount=amount;
    return c;
}

void SW_graph(float x, float y,float axis, float ris, float per, float pea, float inc, float fal,float val){
    printf("%0.6f, %0.6f\n", x,y);
    while (y < ris){
        y=y+val;
        printf("%0.6f, %0.6f\n", x,y);
    }
    if(y== ris && x < pea){
        while(x<pea){
            x=x+val;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }
    if (x == pea && y == ris){
        while(y>axis){
            y= y -val;
            printf("%0.6f, %0.6f\n", x,y);

        }
    }
    if(y== axis && x == pea){
        while(y> fal){
            y=y-val;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }
    if(y== fal && x == pea){
        while(x < per){
            x=x+val;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }
    if(y== fal && x == per){
        while(y< axis){
            y=y+val;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }

    /*while(x!=per){
        x=x+val;
        printf("%0.6f, %0.6f\n", x,y);
    }*/
}
void cycle(float x, float y,float axis, float ris, float per, float pea, float inc, float fal,float val,unsigned int amount){
   unsigned int z = amount;
   float peri=per;
   while(z!= 0){
        axis = axis+inc;
        while(y<axis){
            y=y+val;
            printf("%0.6f, %0.6f\n", x,y);
        }

        SW_graph(x,y,axis,ris, per, pea, inc, fal, val);
        x = x+per;
        pea = pea + peri;
        per = peri+per;
    
        
        ris = ris+inc;
        fal = fal + inc;
        --z;
        
        
   }

}
int main (){
    float x,y, axis, period, peak, trough, rise, fall, incre, value;
    unsigned int amount;

    configSq values;
    
    values = findValues(axis, period, rise, incre, value, amount); 
    axis = values.axis;
    rise = values.rise;
    period = values.period;
    peak = period/2;
    incre = values.incre;
    fall = axis - rise/2;
    value=values.value;
    amount = values.amount;
    x=0;
    y=axis;
    void* memory = malloc(10*sizeof(float)+sizeof(int));
    if (memory == NULL){
        printf("Memory allocation failed./n");
        return 1;
    }
    float *pAx = (float*)memory;
    float *pR = (float*)(pAx +1);
    float *pP = (float*)(pR +1);
    float *pPea = (float*)(pP+1);
    float *pI = (float*)(pPea + 1);
    float *pV = (float*)(pI + 1);
    float *pA = (float*)(pV +1);
    *pAx = axis;
    *pR = rise;
    *pP = period;
    *pPea = peak;
    *pI = incre;
    *pV= value;
    *pA = amount; 
    free(memory);
    cycle(x,y,axis,rise, period, peak, incre, fall, value,amount);
}