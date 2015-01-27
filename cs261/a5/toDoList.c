#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"






/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TaskP createTask (int priority, char *desc)
{
	TaskP t = malloc(sizeof(struct Task));							/* FIXME */
	t->priority = priority;
	strcpy(t->description, desc);
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the
			task priority, followed by a tab character (\t), and
			the task description.

			The tasks are not necessarily stored in the file in
			priority order.

*/
void saveList(DynArr *heap, FILE *filePtr)
{
  int i;
	TaskP task;
	assert(sizeDynArr(heap) > 0);
	for(i = 0; i < sizeDynArr(heap); i++)
	{
	  task = getDynArr(heap, i);
	  fprintf(filePtr, "%d\t%s\n", task->priority, task->description);
	}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file
*/
void loadList(DynArr *heap, FILE *filePtr)
{
  TaskP task;
  char line[100];  /* Assume lines < 100 */
  char desc[TASK_DESC_SIZE], *nlptr;
  int priority;

  /* Read the priority first, then the description.
   * fgets() is used to read string with spaces
   */
#ifdef NOTDEF
  while (fscanf(filePtr, "%d\t", &priority) != EOF)
    {
      /* fgets() stops reading at \n character */
      fgets(desc, sizeof(desc), filePtr);
      /* remove trailing newline character */
      nlptr = strchr(desc, '\n');
      if (nlptr)
        *nlptr = '\0';

      task = createTask(priority, desc);
      addHeap(heap, task);
    }
#endif

  while(fgets(line, sizeof(line), filePtr) != 0)
    {
      sscanf(line, "%d\t%[^\n]", &priority, desc);
      task = createTask(priority, desc);
      addHeap(heap, task);
    } /* should use feof to make sure it found eof and not error*/

}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  DynArr *temp;
  TaskP task;
  assert(sizeDynArr(heap) > 0);

  temp = createDynArr(sizeDynArr(heap));
  /* copy the main list to a temp list
   * so that tasks can be printed out and removed.
   */
  copyDynArr(heap, temp);
  while(sizeDynArr(temp) > 0)
    {
      /* get the task */
      task = getMinHeap(temp);
      /* print the task */
      printf("%d:  %s\n\n", task->priority, task->description);
      /* remove the task */
      removeMinHeap(temp);
    }
  /* free the temp list */
  deleteDynArr(temp);
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
  TaskP l,r;
  l = (TaskP)left;
  r = (TaskP)right;

 if (l->priority < r->priority)
    return -1;
  else if (l->priority > r->priority)
    return 1;
  else
    return 0;
}
