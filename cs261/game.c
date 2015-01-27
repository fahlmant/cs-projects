#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



struct Q {
	struct Q *left;
	struct Q *right;
	char* value;
};

void initQ(struct Q *new)
{
	new->value = " ";
	new->left = NULL;
	new->right = NULL;
}

struct Q* newQ()
{	
	struct Q *new = (struct Q*)malloc(sizeof(struct Q));
	assert(new != 0);

	initQ(new);
	return new;	

}

int main()
{
	struct Q *q = newQ();
	q->value = "Are you thinking of a dog?";
	printf("%s \n", q->value);

	return 0;
}