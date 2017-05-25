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
    double result1 = ((double)NUMM/(time1-time0));
    double time_result1 = time1-time0;

    double time2 = omp_get_wtime();
    SimdMul(A, B, D, NUMM); 
    double time3 = omp_get_wtime(); 
    double result2 = ((double)NUMM/(time3-time2));
    
    fprintf(stdout, "Speedup Mult P: %f\n", result2/result1);

    double time4 = omp_get_wtime();
    ArrayMultSum(A, B, NUMM); 
    double time5 = omp_get_wtime();
    double result3 = ((double)NUMM/(time5-time4));
    

    double time6 = omp_get_wtime();
    SimdMulSum(A, B, NUMM); 
    double time7 = omp_get_wtime();
    double result4 = ((double)NUMM/(time7-time6));

    fprintf(stdout, "Speedup Reduction P: %f\n", result2/result1);


    return 0;

}

float randf(unsigned int *seedp){
    
    float r = (float) rand_r(seedp);
    return r;
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
