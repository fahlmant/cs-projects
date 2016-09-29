/****
 *Author: Taylor Fahlman
 *Assignment: The Dining Philosophers Problem
 *Date Due: 10/12/2015
****/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "mt19937ar.c"

void sig_catch(int sig);
pthread_mutex_t fork1, fork2, fork3, fork4, fork5;
int fork12 = 0, fork23 = 0, fork34 = 0, fork45 = 0, fork51 = 0;
void plato(void);
void locke(void);
void pythagoras(void);
void socrates(void);
void marx(void);
void eat(void);
void think(void);
int gen_number(int high, int low);

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    printf("fork12: %d\n", fork12);
    printf("fork23: %d\n", fork23);
    printf("fork34: %d\n", fork34);
    printf("fork45: %d\n", fork45);
    printf("fork51: %d\n", fork51);
    pthread_mutex_destroy(&fork1);
    pthread_mutex_destroy(&fork2);
    pthread_mutex_destroy(&fork3);
    pthread_mutex_destroy(&fork4);
    pthread_mutex_destroy(&fork5);
    kill(0,sig);
    exit(0);
}

int gen_number(int high, int low) {

    int num = 0;

    num = (int)genrand_int32();
    num = abs(num);
    num %= (high - low);
    if (num < low)
    {
        num = low;
    }

    return num;
}

void eat(void){
    
    int num = 0;
    
    num = gen_number(9, 2);
    sleep(num);
}

void think(void){
    int num = 0;

    num = gen_number(20, 1);
    sleep(num);
}

void plato(void){

    for(;;)
    {
        //Think
        printf("Plato is thinking\n");
        think();
        printf("Plato is done thinking\n");
        //Check that the adjacent philos dont have forks
        //If they do, wait on signal 
        //Philosopher 1, gets forks 1,2
        while(fork51 == 1)
        {
            printf("Plato is waiting for fork 1\n");
            sleep(5);
        }
        while(fork23 == 1)
        {
            printf("Plato is waiting for fork 2\n");
            sleep(5);
        }
        pthread_mutex_lock(&fork1);
        pthread_mutex_lock(&fork2);
        fork12 = 1;
        printf("Plato has forks 1 and 2\n");

        //Do eat
        printf("Plato is eating\n");
        eat();
        printf("Plato is done eating\n");

        //Puts forks
        pthread_mutex_unlock(&fork1);
        pthread_mutex_unlock(&fork2);
        fork12 = 0;
        printf("Plato has put forks 1 and 2 down\n");
    }
}

void locke(void){

    for(;;)
    {
        //Think
        printf("Locke is thinking\n");
        think();
        printf("Locke is done thinking\n");

       //Philosopher 2, gets forks 2,3
        while(fork12 == 1)
        {
            printf("Locke is waiting for fork 2\n");
            sleep(5);
        }
        while(fork34 == 1)
        {
            printf("Locke is waiting for fork 3\n");
            sleep(5);
        }
        pthread_mutex_lock(&fork2);
        pthread_mutex_lock(&fork3);
        fork23 = 1;
        printf("Locke has forks 2 and 3\n");

        //Eat
        printf("Locke is eating\n");
        eat();
        printf("Locke is done eating\n");

       //Puts forks
        pthread_mutex_unlock(&fork2);
        pthread_mutex_unlock(&fork3);
        fork23 = 0;
        printf("Locke has put down forks 2 and 3\n");
    }
}

void pythagoras(void){

    for(;;)
    {
        //Think
        printf("Pythagoras is thinking\n");
        think();
        printf("Pythagoras is done thinking\n");
        
        //Philosopher 3, gets forks 3,4
        while(fork23 == 1)
        {
            printf("Pythagoras is waiting for fork 3\n");
            sleep(5);
        }
        while(fork45 == 1)
        {
            printf("Pythagoras is waiting for fork 4\n");
            sleep(5);
        }
        pthread_mutex_lock(&fork3);
        pthread_mutex_lock(&fork4);
        fork34 = 1;
        printf("Pythagoras has forks 3 and 4\n");

        //Eat
        printf("Pythagoras is eating\n");
        eat();
        printf("pythagoras is done eating\n");

        //Puts forks
        pthread_mutex_unlock(&fork3);
        pthread_mutex_unlock(&fork4);
        fork34 = 0;
        printf("Pyhtagoras has put down forks 3 and 4\n");
    }
}

void socrates(void) {

    for(;;)
    {
        //Think
        printf("Socrates is thinking\n");
        think();
        printf("Socrates is done thinking\n");

        //Philosopher 4, gets forks 4,5
        while(fork34 == 1)
        {
            printf("Socrates is waiting for fork 4\n");
            sleep(5);
        }
        while(fork51 == 1)
        {   
            printf("Socrates is waiting for fork 5\n");
            sleep(5);
        }
        pthread_mutex_lock(&fork4);
        pthread_mutex_lock(&fork5);
        fork45 = 1;
        printf("Socrates has forks 4 and 5\n");

        //Eat
        printf("Socrates is eating\n");
        eat();
        printf("Socrates is done eating\n");

        //Puts forks
        pthread_mutex_unlock(&fork4);
        pthread_mutex_unlock(&fork5);
        fork45 = 0;
        printf("Socrates has put down forks 4 and 5\n");
    }
}

void marx(void) {

    for(;;)
    {
        //Think
        printf("Marx is thinking\n");
        think();
        printf("Marx is done thinking\n");

        //Philosopher 5, gets forks 5,1
        while(fork45 == 1)
        {
            printf("Marx is waiting for fork 5\n");
            sleep(5);
        }
        while(fork12 == 1)
        {
            printf("Marx is waiting for fork 5\n");
            sleep(5);
        }
        pthread_mutex_lock(&fork5);
        pthread_mutex_lock(&fork1);
        fork51 = 1;
        printf("Marx has forks 5 and 1\n");

        //Eat
        printf("Marx is eating\n");
        eat();
        printf("Marx is done eating\n");
        
        //Put forks
        pthread_mutex_unlock(&fork5);
        pthread_mutex_unlock(&fork1);
        fork51 = 0;
        printf("Marx has put down forks 5 and 1\n");
    }
}

int main(int argc, char **argv) {

    struct sigaction sig;
    pthread_t plato_thread;
    pthread_t locke_thread;
    pthread_t pythag_thread;
    pthread_t socrates_thread;
    pthread_t marx_thread;
    void* plato_func = plato;
    void* locke_func = locke;
    void* pthag_func = pythagoras;
    void* socrates_func = socrates;
    void* marx_func = marx;

    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);
    
    pthread_mutex_init(&fork1, NULL);
    pthread_mutex_init(&fork2, NULL); 
    pthread_mutex_init(&fork3, NULL); 
    pthread_mutex_init(&fork4, NULL); 
    pthread_mutex_init(&fork5, NULL); 

    pthread_create(&plato_thread, NULL, plato_func, NULL);
    pthread_create(&locke_thread, NULL, locke_func, NULL);
    pthread_create(&pythag_thread, NULL, pthag_func, NULL);
    pthread_create(&socrates_thread, NULL, socrates_func, NULL);
    pthread_create(&marx_thread, NULL, marx_func, NULL);

    for(;;){

    }
}
