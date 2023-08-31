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

void SW_graph(float x, float y,float axis,float ax, float ris, float per, float pea, float inc, float fal,float val){
    /*y=axis-inc;*/
    
    
    printf("%0.6f, %0.6f\n", x,y);
    while (y != ris){
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
void SW_graph_dec(float x, float y,float axis,float ax, float ris, float per, float pea, float inc, float fal,float val,float check){

    printf("%0.6f, %0.6f\n", x,y);
    while(y < ris){
        y= y+val;
        printf("%0.6f, %0.6f\n", x,y);
    }
    if (y == ris && x < pea){
        while(x<pea){
            x=x+val;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }
    while (y != axis){
        y=y-val;
        printf("%0.6f, %0.6f\n", x,y);
    }
    while (y != fal){
        y=y-val;
        printf("%0.6f, %0.6f\n", x,y);
    }
    if(y== fal && x < per){
        while(x<per){
            x=x+val;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }
    if (x == per && y == fal){
        while(y<axis){
            y= y +val;
            printf("%0.6f, %0.6f\n", x,y);

        }
    }
    
    /*if(y== axis && x == per){
        while(y<ris){
            y=y+val;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }
    if(y== fal && x == pea){
        while(x < per){
            x=x+val;
            printf("hello\n");
            printf("%0.6f, %0.6f\n", x,y);

        }

    }
    if(y== ris && x == per){

        while(y>axis){
            y=y-val;
            printf("%0.6f, %0.6f\n", x,y);

        }

    }

    while(x!=per){
        x=x+val;
        printf("%0.6f, %0.6f\n", x,y);
    }*/
}
void cycle(float x, float y,float axis,float ax, float ris, float per, float peri, float pea, float inc, float fal,float val,unsigned int amount){
   unsigned int z = amount;
   float axi = axis;
   
   while(z!= 0){
        
        SW_graph(x,y,axis,ax,ris, per, pea, inc, fal, val);/*Something is causing this function to not run.*/
        /*printf("%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f, %0.6f,%0.6f\n", x,y,axis,ax,ris,per,pea,ris,fal);*/
        axis = axis+ax;
        while(x == per && y<axis){
            y=y+val;
            printf("%0.6f, %0.6f\n", x,y);
        }
        x = x + peri;
        
        pea = pea + peri;
        per = peri+per;
        ris = ris+inc;
        fal = fal + inc;
        /*printf("%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f, %0.6f,%0.6f\n", x,y,axis,ax,ris,per,pea,ris,fal);*/
        --z;
        if(z==1){
            fal = fal-inc;
        }
        
        
   }
   z=amount-1;
   ris = axis;
   axis = axis-2*ax;
   
   fal = fal - 2*inc;
    float check;
    while(z!= 0){
        
        SW_graph_dec(x,y,axis,ax,ris, per, pea, inc, fal, val,check);/*Something is causing this function to not run.*/
        /*printf("%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f, %0.6f,%0.6f\n", x,y,axis,ax,ris,per,pea,ris,fal);*/
       
        axis = axis-ax;
        
         if (z==1 && y== axi){
            break;
        }
        
        /*while(x == per && y>axis){
            printf("fuck\n");
            y=y+val;
            printf("%0.6f, %0.6f\n", x,y);
        }
        
        printf("%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f,%0.6f, %0.6f,%0.6f\n", x,y,axis,ax,ris,per,pea,ris,fal); x!=peri * (amount+(amount-1)) && */
        x = x + peri;
            
        pea = pea + peri;
        per = peri+per;
        ris = ris- inc;
        fal = fal - inc;
        --z;
        printf("%d",z);
        --check;
        
        
        
   }

}
int main (){
    float x,y, axis,ax, period,peri, peak, trough, rise, fall, incre, value;
    unsigned int amount;

    configSq values;



    
    values = findValues(axis, period, rise, incre, value, amount); 
    axis = values.axis;
    ax = axis;
    float riseh = values.rise;
    rise = values.rise + axis;
    period = values.period;
    peri = period;
    peak = period/2;
    incre = values.incre;
    fall = axis - riseh;
    value=values.value;
    amount = values.amount;
    x=0;
    y=axis;
    cycle(x,y,axis,ax,rise, period, peri, peak, incre, fall, value,amount);

}