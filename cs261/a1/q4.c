/* CS261- Assignment 1 - Q.4*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/ 
	int id_swap;
	int score_swap;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if (students[j].score > students[j+1].score)
			{
				id_swap = students[j].id;
				score_swap = students[j].score;
				students[j].id = students[j+1].id;
				students[j].score = students[j+1].score;
				students[j+1].id = id_swap;
				students[j+1].score = score_swap;				
			}
		}
	}
    
     /* Remember, each student must be matched with their original score after sorting */
}

int main(){
	
	srand(time(NULL));
	
    /*Declare an integer n and assign it a value.*/
	int n = 10;    

    /*Allocate memory for n students using malloc.*/
	struct student *students = malloc(n*sizeof(struct student));    

    /*Generate random IDs and scores for the n students, using rand().*/
	int rand_id;
    int rand_score;
    int id_check = 0;
    int id_count = 0;
    int score_check = 0;
    int score_count = 0;

    for(int i = 0; i < n; i++)
    {
        while(id_check == 0)
        {
            rand_id = rand() % 10 + 1;
            for(int j = 0; j < n; j++)
            {
                if(rand_id != students[j].id)
                {
                    id_count++;
                }
            }
            if(id_count == n)
            {
                id_count = 0;
                id_check = 1;
            }
            id_count = 0;
        }
        students[i].id = rand_id;
        id_check = 0;
    }

    for(int i = 0; i < n; i++)
    {
        while(score_check == 0)
        {
            rand_score = rand() % 100;
            for(int j = 0; j < n; j++)
            {
                if(rand_score != students[j].score)
                {
                    score_count++;
                }
            }
            if(score_count == n)
            {
                score_count = 0;
                score_check = 1;
            }
            score_count = 0;
        }
        students[i].score = rand_score;
        score_check = 0;
    }

    
    /*Print the contents of the array of n students.*/
	for(int k = 0; k < n; k++)
	{
		printf("ID:%d \n", students[k].id);
		printf("Score:%d \n\n", students[k].score);
	}	

    /*Pass this array along with n to the sort() function*/
    sort(students, n);

    /*Print the contents of the array of n students.*/
	for(int l = 0; l < n; l++)
	{
		printf("Sorted\n");
		printf("ID:%d \n", students[l].id);
		printf("Score:%d \n\n", students[l].score);
	}

	free(students);
    
    return 0;
}