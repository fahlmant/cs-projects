/****
 *Program: Linked Lists
 *Author: Taylor Fahlman
 *Date Due: 6/7/2013
 *Description: Creates a linked list that conatins the users input, then sorts them 
 *Input: Numbers until the user dosen't want to enter anymore
 *Output: Sorted list of ints in the linked list
*****/ 

#include <stdio.h>
#include <stdlib.h>

struct list {
   int num;
   struct list *next;
};

typedef struct list item;

/*****
 * Function: sort
 * Desc: Sorts the ints in the linked list by comparing the current nodes int and the next nodes int
 * Parameters: head node, and the number of nodes in the list
*****/

void sort(item *head, int count)
{
    int check = 1;
    int i = 0;
    item *buff;

    while(check != 0)
    {
        check = 0;
        int temp;
        for(i; i < count; i++)
        {

            buff = head;
            while(buff->next)
            {
                if(buff->num > buff->next->num)
                {
                    temp = buff->num;
                    buff->num = buff->next->num;
                    buff->next->num = temp;
                }
                buff = buff->next;
            }
        }
    }
}

/*****
 * Function: main
 * Desc: executes the main code, takes in user input until they dont want to, dynamically creating a linked listthen passes the head to sort, then prints out the sorted list
 * Parameters: none
******/

int main() {

    item *current, *head;
    int check;
    int number; 
    int count;

    head = NULL;
   
    printf("Press 1 to enter a number, 0 to quit\n");
    scanf("%d", &check);
    
    if(check == 1)
    {
        count = 1;
        do{
            printf("Please enter your number\n");
            scanf("%d", &number);
            current = (item*)malloc(sizeof(item));
            current->num = number;
            current->next = head;
            head = current;
            printf("Press 1 to enter a number, 0 to quit\n");
            scanf("%d", &check);
            count += 1;
        }while(check == 1);
    }


    sort(current, count);
    printf("\n");

    
    while(current){
        printf("%d\n", current->num);
        current = current->next;
    }

    return 0;
}
