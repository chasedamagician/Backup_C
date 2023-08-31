#include <stdio.h>
#include <math.h>


float length(float time){
    printf("Enter a length of period: ");
    scanf("%f/n",&time);
    return time;
}
float altitude(float height){
    printf("Enter an altitude: ");
    scanf("%f/n",&height);
    return height;
}
float change(float increx){
    printf("Enter an increment: ");
    scanf("%f/n",&increx);
    return increx;
}
float repeat(float period){
    printf("Enter the amount of periods: ");
    scanf("%f/n",&period);
    return period;
}


void triangle(float x, float y, float time, float height, float slope, float increx, float increy,float midp){
    
     while ((x<=midp) && (y<=height)){
        x = x + increx;
        y =y + increy;
        printf("%0.6f, %0.6f\n", x,y);

    }
    if ((x = midp) && (y = height)){
        while (x<=time && y>=0){
            x = x +increx;
            y = y - increy;
            printf("%0.6f,%0.6f\n", x,y);
        }

    }

}
void cycle(float x, float y, float time, float height, float slope, float increx, float increy,float midp, float period){
   float z = period;
   float teme = time;
   while(z!= 0){
        triangle(x,y,teme,height,slope,increx,increy,midp);
        x=x+time;
        midp=midp+time;
        teme=teme+time;
        --z;
   }

}


int main() {

    float x,y,time, height, slope, increx,increy,period,midp;

    x=0;
    y=0;
    
    
    
    

    /*insert(time,height,increx,period);*/
    time = length(time);
    midp=time/2;
    height = altitude(height);
    increx = change(increx);
    period = repeat(period);
    slope = height/(time/2);
    increy = increx*slope;
    cycle(x,y,time,height,slope,increx,increy,midp,period);
    
   
    

    

    
    return 0;
}




