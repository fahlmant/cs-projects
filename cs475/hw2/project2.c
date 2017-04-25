#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define ARRAYSIZE 32768 //32K

float Ranf(float low, float high) {

    float r = (float)rand();
    return(low + r * (high - low) / (float)RAND_MAX);
}

int main( ) {

    #ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
    #endif
    int array[ARRAYSIZE];
    float prod = 0;
    for(int i = 0; i < ARRAYSIZE; i++) {
       array[i] = Ranf(-1.f, 1.f); 
    }

    omp_set_num_threads( NUMT );
    fprintf( stderr, "Using %d threads\n", NUMT );

    #pragma omp parallel for schedule(dynamic, 4096), default(none), private(prod), shared(array)
    for(int i = 0; i < ARRAYSIZE; i++) {
        prod = 1.;
        for(int j = 0; j < i; j++) {
            prod *= array[j];
            printf("J: %d\n", i);
        }
    }
        

    return 0;
}
