#include <stdio.h>

#define NUM_POINTS 100
#define PERIOD 10

int main() {
    int i;
    float x, y;

    for (i = 0; i < NUM_POINTS; i++) {
        x = (float)i / NUM_POINTS * PERIOD;
        y = (i % (NUM_POINTS / PERIOD)) / ((float)(NUM_POINTS / PERIOD) - 1);

        printf("%.2f, %.2f\n", x, y);
    }

    return 0;
}