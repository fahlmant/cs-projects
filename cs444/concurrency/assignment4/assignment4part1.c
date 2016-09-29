/****
 *Author: Taylor Fahlman
 *Assignment: Shareable resource with 3 available slots
 *Date Due: 11/19/2015
****/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>

void sig_catch(int sig);
void process(void *);

struct buffer {
    int number;
    sem_t mutex;    
};

struct buffer buf;
int counter;

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    sem_destroy(&buf.mutex);
    kill(0,sig);
    exit(0);
}

void process (void *buffer)
{
    int zero = 0;
    if(counter > 0)
    {
        zero = 1;
    }
    while(zero == 0)
    {
        printf("Waiting\n");
        sleep(5);
        if(counter == 3)
        {   
            printf("Done waiting\n");
            zero = 1;
        }
    }
    sem_wait(&buf.mutex);
    counter = counter - 1;

    printf("Working\n");
    sleep(10);
    printf("Done working\n");

    sem_post(&buf.mutex);
    counter = counter +1;

}

int main(int argc, char **argv) {
 
    void *proc_func = process;
    struct sigaction sig;
    pthread_t p1, p2, p3, p4, p5, p6;

    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);


    //Init the semaphore to 3 
    sem_init(&buf.mutex, 0, 3);
    counter = 3;   

    pthread_create(&p1, NULL, proc_func, NULL);
    pthread_create(&p2, NULL, proc_func, NULL);
    pthread_create(&p3, NULL, proc_func, NULL);
    pthread_create(&p4, NULL, proc_func, NULL);
    pthread_create(&p5, NULL, proc_func, NULL);
    pthread_create(&p6, NULL, proc_func, NULL);

    for(;;){

    }
}
