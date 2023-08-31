#include <stdio.h>
#include <math.h>
/*Structure to store values for the CV waveform*/
typedef struct CValues{
    float time;
    float height;
    float increx;
    float period;
} configTri;



/*methods for defining the values*/
configTri findValues(float t, float h, float i, float p){
    configTri c;
    printf("Enter a length of period: ");
    scanf("%f",&t);
    printf("Enter an altitude: ");
    scanf("%f",&h);
    printf("Enter an increment: ");
    scanf("%f",&i);
    printf("Enter the amount of periods: ");
    scanf("%f",&p);
    c.time = t;
    c.height = h;
    c.increx = i;
    c.period = p;
    return c;
}

/*Function for producing a singular CV waveform*/
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
/*Method to produce multiple periods*/
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
    configTri values;

    x=0;
    y=0;
    
    values = findValues(time,height,increx,period);

    time = values.time;
    height = values.height;
    increx = values.increx;
    period = values.period;
    midp=time/2;
    slope = height/(time/2);
    increy = increx*slope;
    cycle(x,y,time,height,slope,increx,increy,midp,period);
    
    
    return 0;
}




