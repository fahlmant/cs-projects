#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include "simd.p7.h"

#define SIZE   32768
float Array[2*SIZE];
float  Sums[1*SIZE];

int main() {

    FILE *fp = fopen( "signal.txt", "r" );
    if( fp == NULL )
    {
        fprintf( stderr, "Cannot open file 'signal.txt'\n" );
        exit( 1 );
    }
    int Size;
    fscanf( fp, "%d", &Size );
    Size = SIZE;

    for( int i = 0; i < Size; i++ )
    {
        fscanf( fp, "%f", &Array[i] );
        Array[i+Size] = Array[i];       // duplicate the array
    }
    fclose( fp );

    double time0 = omp_get_wtime( );

    for( int shift = 0; shift < Size; shift++ )
    {
        Sums[shift] = SimdMulSum(&Array[0], &Array[0+shift], Size);
    }
    double time1 = omp_get_wtime( );
    printf("Total time: %f\n", time1-time0);

    return 0;

}

