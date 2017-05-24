#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "simd.p5.h"


unsigned int seed;
float randf(unsigned int *seedp);
void ArrayMult(float *a, float *b, float *c, int k);
float ArrayMultSum(float *a, float *b, int k);


int main() {

    #ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
    #endif

    float *A = new float[NUMM];
    float *B = new float[NUMM];
    float *C = new float[NUMM];
    float *D = new float[NUMM];

    for(int i = 0; i < NUMM; i++) {
        A[i] = randf(&seed);    
    }
    for(int i = 0; i < NUMM; i++) {
        B[i] = randf(&seed);    
    }
    
    double time0 = omp_get_wtime();
    ArrayMult(A, B, C, NUMM); 
    double time1 = omp_get_wtime();
    fprintf(stdout, "Num of elements: %d, My ArrayMult Megamults/sec: %f\n", NUMM, ((double)NUMM/(time1-time0))/1000000);

    double time2 = omp_get_wtime();
    SimdMul(A, B, D, NUMM); 
    double time3 = omp_get_wtime();
    fprintf(stdout, "Num of elements: %d, SimdArrayMult Megamults/sec: %f\n", NUMM, ((double)NUMM/(time3-time2))/1000000);


    double time4 = omp_get_wtime();
    ArrayMultSum(A, B, NUMM); 
    double time5 = omp_get_wtime();
    fprintf(stdout, "Num of elements: %d, My ArrayMultSum Megamults/sec: %f\n", NUMM, ((double)NUMM/(time5-time4))/1000000);

    double time6 = omp_get_wtime();
    SimdMulSum(A, B, NUMM); 
    double time7 = omp_get_wtime();
    fprintf(stdout, "Num of elements: %d, SimdArrayMultSum Megamults/sec: %f\n", NUMM, ((double)NUMM/(time7-time6))/1000000);



    return 0;

}

float randf(unsigned int *seedp){
    
    float r = (float) rand_r(seedp);
}

void ArrayMult(float *a, float *b, float *c, int k) {

    for(int i = 0; i < k; i++) {
        
        c[i] = a[i] * b[i];
    }
}

float ArrayMultSum(float *a, float *b, int k) {

    float result = 0;
    for(int i = 0; i < k; i++) {
        
        result += a[i] * b[i];
    }
}
