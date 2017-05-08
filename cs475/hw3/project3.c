#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


struct s
{
        float value;
        int pad[NUMPAD];
} Array[4];

int main( ) {

    #ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
    #endif

    omp_set_num_threads( NUMT );
    fprintf( stderr, "Using %d threads\n", NUMT );

    double time0 = omp_get_wtime();
    const int SomeBigNumber = 100000000;    // keep < 2B


    #pragma omp parallel for
    for( int i = 0; i < 4; i++ )
    {
        unsigned int seed = 0;      // automatically private
        for( unsigned int j = 0; j < SomeBigNumber; j++ )
        {
            Array[ i ].value = Array[ i ].value + (float)rand_r( &seed );
        }
    }
    
    double time1 = omp_get_wtime();
    //long int numMuled =  / 2;
    fprintf( stderr, "Threads = %2d; NumPads = %5d; Scheduling=static ; MegaMults/sec = %10.2lf\n", NUMT, NUMPAD, (time1-time0));//(double)numMuled/(time1-time0)/1000000. )     

    return 0;
}
