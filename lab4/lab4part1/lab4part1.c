#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

double randDouble() {
return (double)rand() / ((double)RAND_MAX);
}

bool inBounds(double x, double y) {
    if (y < sqrt(1- x*x)) 
    {
        return true;
    }
    else {
        return false;
    }
}


int main(void)
{
    double numIteration, pi;
    int i;
    int inCircle = 0;
    srand(42);
    printf("Number of monte carlo iterations: ");
    scanf("%lfnumInteration", &numIteration);

    for (i=0; i<numIteration;i++) {
        if (inBounds(randDouble(), randDouble())) {
            // printf("true\n");
            inCircle += 1;
        }
        // else{
        //     printf("false\n");
        // }
    }
    pi = inCircle/numIteration*4;


    printf("Pi: %0.4lf", pi);

    return 0;
}
