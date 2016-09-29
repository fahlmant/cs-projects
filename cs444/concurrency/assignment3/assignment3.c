/****
 *Author: Taylor Fahlman
 *Assignment: Searchers, Inserters and Deleters
 *Date Due: 11/5/2015
****/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "mt19937ar.c"

void sig_catch(int sig);
int gen_number(int high, int low);
void searcher(void *num);
void inserter(void);
void deleter(void *num);

//Bufer item should have a number and a point to the next one
struct buffer_item {
    int number;
    struct buffer_item* next;
};

//Buffer struct to hold the head link, the last link and the number of links
struct buffer {
    struct buffer_item* head;
    struct buffer_item* cur;
    int items;
};

//Global variables, yay
struct buffer buff;
int number;
int deleters, searchers, inserters;

//Signal catching
void sig_catch(int sig){
    kill(0,sig);
    exit(0);
}

//Generate random numbers
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

//Searching function
void searcher(void *args) {

    int i;
    struct buffer_item *find = buff.head;

    //Waits until there is no deleters left
    while(deleters != 0)
    {
        sleep(5);
    }
    printf("Searching\n");
    searchers++;
    //The node has to exist
    if(number < buff.items)
    {
        printf("Can't find this node\n");
        return;
    }
    //Crawl through the linked list until at the node desired
    for(i = 0; i < number; i++)
    {
        find = find->next;
    }
    printf("Number: %d\n", find->number);
    searchers--;
}

void inserter(void) {

    struct buffer_item item;

    printf("Inserting\n");
    //Waits until there are no deleters
    while(deleters != 0)
    {
        sleep(5);
    }
    //Waits until it's the only inserter
    while(inserters != 0)
    {
        sleep(5);
    }
    //Makes itself known to the world
    inserters = 1;
    //Generates number for new link
    item.number = gen_number(100, 1);
    //Ensures that we are at the end of the list
    while(buff.cur->next != NULL)
    {
        buff.cur = buff.cur->next;
    }
    //Add the new node to the list
    buff.cur->next = &item;
    buff.cur = buff.cur->next;
    buff.cur->next = NULL;
    buff.items++;
    printf("Added %d to end\n", item.number);
    //No more inserters
    inserters = 0;
}

void deleter(void *arg) {

    int i;
    struct buffer_item *to_delete = buff.head;
    struct buffer_item *temp;

    //ensures it's the only deleter
    while(deleters != 0)
    {
        sleep(5);
    }
    //acquires the deleter number
    deleters = 1;
    //Makes sure there are no inserters
    while(inserters != 0)
    {
        sleep(5);
    }
    //Makes sure there are no searchers
    while(searchers != 0)
    {
        sleep(5);
    }

    printf("Delteing\n");
    //Won't remove the head
    if(number == 1)
    {
        printf("Not removing the head\n");
        return;
    }
    //Makes sure we're within the link
    else if(number < buff.items)
    {
        printf("This node doesn't exist\n");
    }
    //Removes the node, sets previous node to point to next node
    for(i = 0; i < number; i++)
    {
        if(i == (number - 2))
        {
            temp = to_delete;
        }
        to_delete = to_delete->next;          
    }
 
    //Removes the node and releases deleter
    temp->next = to_delete->next;
    free(to_delete);
    printf("Done Deleting\n");
    deleters = 0;
}


int main(int argc, char **argv) {

    struct sigaction sig;
    struct buffer_item init_item;
    pthread_t thread1, thread2, thread3, thread4;
    void *delete_func = deleter;
    void *insert_func = inserter;
    void *search_func = searcher;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);

    init_item.next = NULL;
    init_item.number = 1;
    buff.head = &init_item;

    deleters = 0;
    searchers = 0;
    inserters = 0;
    number = 2;
    
    pthread_create(&thread1, NULL, insert_func, NULL);
    pthread_create(&thread2, NULL, insert_func, NULL);
    pthread_create(&thread3, NULL, search_func, NULL);
    pthread_create(&thread4, NULL, delete_func, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);


    for(;;) {
    }
}
