#include <stdio.h>
#include <stdlib.h>

int main() {
    // Pre-existing variables
    int a = 10;
    float b = 3.14;
    char c = 'X';

    // Allocate memory for the variables
    void* memory = malloc(sizeof(int) + sizeof(float) + sizeof(char));

    if (memory == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Copy the variables into the allocated memory
    int* pA = (int*)memory;
    float* pB = (float*)(pA + 1);
    char* pC = (char*)(pB + 1);

    *pA = a;
    *pB = b;
    *pC = c;

    // Access and print the values
    printf("a: %d\n", *pA);
    printf("b: %.2f\n", *pB);
    printf("c: %c\n", *pC);

    // Free the allocated memory
    free(memory);

    return 0;
}