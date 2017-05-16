#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void GrainDeer();
void Grain();
void Watcher();
void MyAgent();
void tempandprecip();
void incrementMonth();
float grainGrowth();
int deerPop(float height);
float co2(float height);
void printCurrentState();
float Ranf(unsigned int *, float, float);
int Ranf(unsigned int *, int, int);
float SQR(float x);

const float GRAIN_GROWS_PER_MONTH =     8.0;
const float ONE_DEER_EATS_PER_MONTH =   0.5;

const float AVG_PRECIP_PER_MONTH =      6.0;    // average
const float AMP_PRECIP_PER_MONTH =      6.0;    // plus or minus
const float RANDOM_PRECIP =             2.0;    // plus or minus noise

const float AVG_TEMP =                  50.0;   // average
const float AMP_TEMP =                  20.0;   // plus or minus
const float RANDOM_TEMP =               10.0;   // plus or minus noise

const float MIDTEMP =                   40.0;
const float MIDPRECIP =                 10.0;

float   NowPrecip;      // inches of rain per month
float   NowTemp;
unsigned int seed;
// starting date and time:
int NowMonth =    0;
int NowYear  = 2017;
float NowC02 = 0.;

// starting state (feel free to change this if you want):
int NowNumDeer = 1;
float NowHeight =  1.;

int main() {




    #ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
    #endif

    tempandprecip();
        
    double time0 = omp_get_wtime();
    omp_set_num_threads( 4 );   // same as # of sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {

            GrainDeer();
        }

        #pragma omp section
        {
            Grain();
        }

        #pragma omp section
        {
            Watcher();
        }

        #pragma omp section
        {
            MyAgent(); // your own
        }
    }       // implied barrier -- all functions must return in order
            // to allow any of them to get past here    
    double time1 = omp_get_wtime();

    fprintf(stdout, "Time: %f\n", (double)time1 - time0);
    return 0;
}



void GrainDeer() {

    while( NowYear < 2023) {
        //Compute tmp next-value
        //Based on simulation
        float newGrain = grainGrowth();
        int nextDeer = deerPop(newGrain);
        #pragma omp barrier

        NowNumDeer = nextDeer;
        #pragma omp barrier
        #pragma omp barrier
    }
}

void Grain() {
    
    while( NowYear < 2023) {
        //Compute tmp next-value
        //Based on simulation

        float newGrain = grainGrowth();
        #pragma omp barrier
        NowHeight = newGrain;
        #pragma omp barrier
        #pragma omp barrier
    }
}

void Watcher() {
    
    while( NowYear < 2023) {
        //Compute tmp next-value
        //Based on simulation

        #pragma omp barrier
        #pragma omp barrier
        printCurrentState();
        incrementMonth();
        tempandprecip();
       #pragma omp barrier
    }
}

void MyAgent() {

    while( NowYear < 2023) {
        //Compute tmp next-value
        //Based on simulation

        float newGrain = grainGrowth();
        float C02 = co2(newGrain);
        #pragma omp barrier
        NowC02 = C02;
        #pragma omp barrier
        #pragma omp barrier
    }
}

void incrementMonth() {

    if (NowMonth == 11) {
        NowMonth = 0;
        NowYear++;
    }
    else {
        NowMonth++;
    }
}

void tempandprecip() {
    
    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );
    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
    if( NowPrecip < 0.0 ) NowPrecip = 0.0;
}

int deerPop(float height) {
    
    int newNumDeer = NowNumDeer;

    float cap = newNumDeer * ONE_DEER_EATS_PER_MONTH;
    if(height > cap) {
        newNumDeer++;
    }
    else if (height < cap) {
        newNumDeer--;
    }

    return newNumDeer;

}

float co2(float height) {
    
    float newC02 = 0;
    int randNum = Ranf( &seed, 1, 100);
    if(randNum % 3 == 0)
    {
         newC02 = height*(0.2);    
    }

    return newC02;
}

float grainGrowth() {

    float nextGrain = NowHeight;

    float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );

    float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );

    nextGrain += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
    nextGrain -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
    nextGrain += NowC02;

    if(nextGrain < 0.0) nextGrain = 0.0;

    return nextGrain;


}

void printCurrentState() {

    int step = NowMonth + ((NowYear - 2017) * 12);

    printf("\n\n\n");
    printf("Step: %d\n", step);
    printf("Current year: %d\n", NowYear);
    printf("Current month: %d\n", NowMonth);
    printf("Temp: %f\n", (NowTemp-32)*(5.0/9.0));
    printf("Precipitation: %f\n", NowPrecip*2.54);
    printf("Grain Height: %f\n", ((NowHeight)*2.54));
    printf("Deer: %d\n", NowNumDeer);
    printf("Grain due to C02: %f\n", NowC02*2.54);


}

float Ranf( unsigned int *seedp,  float low, float high )
{
    float r = (float) rand_r( seedp );              // 0 - RAND_MAX

    return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int Ranf( unsigned int *seedp, int ilow, int ihigh )
{
    float low = (float)ilow;
    float high = (float)ihigh + 0.9999f;

    return (int)(  Ranf(seedp, low,high) );
}

float SQR(float x) {
    
    return x*x;
}
