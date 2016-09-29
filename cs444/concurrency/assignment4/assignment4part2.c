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

void sig_catch(int sig);
void barber(void *);
void customer(void *);
void get_hair_cut(void);
void cut_hair(void);
void line_pop(void);
void line_push(void);

struct chair {

    struct chair *next;
};

struct line {

    int number_of_customers;
    int chairs;
    struct chair *current;
    struct chair *next;
};

pthread_mutex_t barber_lock;
pthread_mutex_t add_lock;
struct line global_queue;

void sig_catch(int sig){
    
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

void line_push(void)
{
    struct chair new;
    struct chair *ref = global_queue.current;

    //Double check that the queue isn't full
    if(global_queue.number_of_customers >= global_queue.chairs)
    {
        return;
    }
    new.next = NULL;
    while(global_queue.next != NULL)
    {
        ref = ref->next;  
    }
    ref->next = &new;
    global_queue.number_of_customers++;

}

void line_pop(void)
{
    struct chair *ref = global_queue.current;

    global_queue.number_of_customers--;
    global_queue.current = global_queue.next;
    if(global_queue.next != NULL)
    {
        global_queue.next = global_queue.current->next;
    }

    ref = NULL;

}

void barber(void *queue)
{
    int i;
    int copy_of_customer_number;

    for(;;)
    {
        i = 0;
        copy_of_customer_number = global_queue.number_of_customers;
        while(global_queue.number_of_customers == 0)
        {
            printf("The Barber is sleeping\n");
            sleep(5);
        }
    
        for(i = 0; i < copy_of_customer_number; i++)
        {
            //Cut hair
            cut_hair();
        }
    }
}

void customer(void *queue)
{
    //Sees if there is room in the queue
    if(global_queue.number_of_customers >= global_queue.chairs)
    {
        printf("Line is full. Leaving\n");
        return;
    }

    pthread_mutex_lock(&add_lock);
    line_push();
    pthread_mutex_unlock(&add_lock);

    printf("In chair waiting\n");
    //get mutex
    pthread_mutex_lock(&barber_lock);
    get_hair_cut();
    //release mutex
    line_pop();
    pthread_mutex_unlock(&barber_lock);
}


void cut_hair(void)
{
    
    printf("Cutting hair\n");
    sleep(10);
    printf("Done cutting hair\n");
}

void get_hair_cut(void)
{
    printf("Getting hair cut\n");
    sleep(10);
    printf("Done getting hair cut\n");
    
}

int main(int argc, char **argv) {

    pthread_t barber_thread;
    pthread_t c1, c2, c3, c4;
    void *barber_func = barber;
    void *customer_func = customer;
    struct chair one;

    struct sigaction sig;
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);

    one.next = NULL;
    global_queue.current = &one;
    
    pthread_mutex_init(&barber_lock, NULL);
    pthread_mutex_init(&add_lock, NULL);

    global_queue.chairs = 3;
    global_queue.number_of_customers = 0;

    pthread_create(&barber_thread, NULL, barber_func, NULL);
    sleep(5);

    pthread_create(&c1, NULL, customer_func, NULL);
    pthread_create(&c2, NULL, customer_func, NULL);
    pthread_create(&c3, NULL, customer_func, NULL);
    pthread_create(&c4, NULL, customer_func, NULL);

    for(;;)
    {

        
    }
}
