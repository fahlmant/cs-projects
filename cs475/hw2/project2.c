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

    double time0 = omp_get_wtime();
    
    #pragma omp parallel for schedule(CHUNKTYPE, CHUNKSIZE), default(none), private(prod), shared(array)
    for(int i = 0; i < ARRAYSIZE; i++) {
        prod = 1.;
        for(int j = 0; j < i; j++) {
            prod *= array[j];
        }
    }
    
    double time1 = omp_get_wtime();
    long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE+1) / 2;
    fprintf( stderr, "Threads = %2d; ChunkSize = %5d; Scheduling=static ; MegaMults/sec = %10.2lf\n", NUMT, CHUNKSIZE, (double)numMuled/(time1-time0)/1000000. );
        

    return 0;
}
