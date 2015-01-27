/* CS261- Assignment 1 - Q. 1*/
/* Name: Taylor Fahlman - Michael Papendieck
 * Date Due: 10/11/13
 * Solution description: Used loops to systematically compare the values in each part of the array of scores and ids in the struct. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct student{
    int id;
    int score;
};

struct student* allocate()
{
	/*Allocate memory for ten students*/  
    struct student * myStud = malloc(10 * sizeof(struct student));

	/*return the pointer*/
    return myStud;
}

void deallocate(struct student* students)
{
	/*Deallocate memory from stud*/
    free (students);
}

void summary(struct student* students)
{
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    double sum;
    double ave;
    int low = students[0].score;
    int high = students[0].score;

	for(int j = 0; j < 10; j++)
	{
		sum += students[j].score;

	}

    for(int i = 0; i < 10; i++)
    {
        if(low > students[i].score)
            low = students[i].score;
        if(high < students[i].score)
            high = students[i].score;
    }

    ave = sum / 10;
    printf("Average: %f \n", ave);
    printf("High: %d \n", high);
    printf("Low: %d \n", low);
}

void output(struct student* students)
{
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/	

    int score;
    int id;
    for(int i = 0; i < 10; i++)
    {
        id = students[i].id;
        score = students[i].score;
        printf("ID: %d ", id);
        printf("Score: %d \n\n", score);
    }

}

void generate(struct student* students)
{
	/*Generate random ID and scores for 10 students, ID being between 1 and 10, scores between 0 and 100*/
    int rand_id;
    int rand_score;
    int id_check = 0;
    int id_count = 0;
    int score_check = 0;
    int score_count = 0;

    for(int i = 0; i < 10; i++)
    {
        while(id_check == 0)
        {
            rand_id = rand() % 10 + 1;
            for(int j = 0; j < 10; j++)
            {
                if(rand_id != students[j].id)
                {
                    id_count++;
                }
            }
            if(id_count == 10)
            {
                id_count = 0;
                id_check = 1;
            }
            id_count = 0;
        }
        students[i].id = rand_id;
        id_check = 0;
    }

    for(int i = 0; i < 10; i++)
    {
        while(score_check == 0)
        {
            rand_score = rand() % 100;
            for(int j = 0; j < 10; j++)
            {
                if(rand_score != students[j].score)
                {
                    score_count++;
                }
            }
            if(score_count == 10)
            {
                score_count = 0;
                score_check = 1;
            }
            score_count = 0;
        }
        students[i].score = rand_score;
        score_check = 0;
    }
}

int main()
{
    struct student *stud = NULL;
	/*call allocate*/
    stud = allocate();

    srand(time(NULL));

    /*call generate*/
    generate(stud);

    /*call output*/
    output(stud);

    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);
}

