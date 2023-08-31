#include <stdio.h>
#include <math.h>
typedef struct DPValues{
    float rise;
    float period;
    float peak;/*Width of the peak*/
    float incre;/*Increment the y-value increses each period*/
    float value;/*Distance between points*/
    unsigned int amount;
} configDPV;

configDPV findValues(float ris, float per, float pea, float inc,float val, unsigned int amount){
    configDPV c;
    printf("Enter a height of the rise: ");
    scanf("%f",&ris);
    printf("Enter the length of the period: ");
    scanf("%f",&per);
    printf("Enter the width of the peak: ");
    scanf("%f",&pea);
    printf("Enter the size of the increment: ");
    scanf("%f",&inc);
    printf("Enter the distance between each point: ");
    scanf("%f",&val);
    printf("Enter the number of periods: ");
    scanf("%u",&amount);

    c.rise = ris;
    c.period = per;
    c.peak = pea;
    c.incre= inc;
    c.value = val;
    c.amount=amount;
    return c;
}
void DPV_graph(float x, float y, float ris, float per, float pea, float tro, float inc, float fal,float val){
    float htro = tro;
    
    while (x < htro){
        x= x+val;
        printf("%0.6f, %0.6f\n", x,y);
    }
    if (x>=htro && y < ris){
        while(y!=ris){
            y=y+val;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }
    if(x==htro && y == ris){
        while(x!=(pea)){
            x=x+val;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }
    if(x==(pea) && y==ris){
        while(y>(fal)){
            y=y-val;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }
    /*while(x!=per){
        x=x+val;
        printf("%0.6f, %0.6f\n", x,y);
    }*/
}
void DPV_graph_dec(float x, float y, float ris, float per, float pea, float tro, float inc, float fal,float val){
    float htro = tro;
    
    while (x < htro){
        x= x+val;
        printf("%0.6f, %0.6f\n", x,y);
    }
    if (x>=htro && y > fal){
        while(y!=fal){
            y=y-val;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }
    if(x==htro && y == fal){
        while(x!=(pea)){
            x=x+val;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }
    if(x==(pea) && y==fal){
        while(y!=(ris)){
            y=y+val;
            printf("%0.6f, %0.6f\n", x,y);
        }
    }

    /*while(x!=per){
        x=x+val;
        printf("%0.6f, %0.6f\n", x,y);
    }*/
}
void cycle(float x, float y, float rise, float period, float peakc, float trough, float incre, float fall, float value,unsigned int amount){
   unsigned int z = amount;
    float ri = rise;
   float peri=period;
   while(z!= 0){
        DPV_graph(x,y,rise,peri,peakc,trough,incre,fall,value);
        x = x+period;
        y= y+incre;
        peri = peri+period;
        trough = trough+ period;
        peakc = peakc + period;
        rise = rise+incre;
        fall = fall + incre;
        --z;
   }
   z = amount;
   float nfall = fall - incre - ri;
   float nrise = rise - ri - incre;
   while(z!= 0){
        DPV_graph_dec(x,y,nrise,peri,peakc,trough,incre,nfall,value);
        x = x+period;
        y= y-incre;
        peri = peri+period;
        trough = trough+ period;
        peakc = peakc + period;
        nrise = nrise-incre;
        nfall = nfall -incre;
        --z;
   }

}
int main (){
    float x,y, rise, period,peakw,peakc, trough, incre, fall,value;
    unsigned int amount;

    configDPV values;
    x=0;
    y=0;
    values = findValues(rise,period,peakw, incre, value,amount); 

    rise = values.rise;
    period = values.period;
    peakw = values.peak;
    trough = period - peakw;
    peakc = peakw+(trough);
    incre = values.incre;
    fall = incre;
    value=values.value;
    amount = values.amount;
    cycle(x,y,rise,period,peakc,trough, incre,fall,value,amount);
}