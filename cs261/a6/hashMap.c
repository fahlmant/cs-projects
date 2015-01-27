#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

struct hashLink {
   KeyType key; /*the key is what you use to look up a hashLink*/
   ValueType value; /*the value stored with the hashLink, a pointer to int in the case of concordance*/
   struct hashLink * next; /*notice how these are like linked list nodes*/
};
typedef struct hashLink hashLink;

struct hashMap {
    hashLink ** table; /*array of pointers to hashLinks*/
    int tableSize; /*number of buckets in the table*/
    int count; /*number of hashLinks in the table*/
};
typedef struct hashMap hashMap;

/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	struct hashLink *cur;
	struct hashLink *temp;
	ValueType *v;
	KeyType k;

	for(int i = 0; i < ht->tableSize; i++)
	{
		cur = ht->table[i];
		while(cur != NULL)
		{

			v = cur->value;
			cur->key = NULL;
			k = cur->key;
			free(v);
			free(k);
			temp = cur;
			cur = cur->next;
			free(temp);
			
		}
		
		
	}		
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	hashLink ** newTable;
	newTable = (hashLink**)malloc(sizeof(hashLink*) * newTableSize);

	for(int i = 0; i < ht->tableSize; i++)
	{
		newTable[i] = ht->table[i];
	}	

	free(ht->table);
	ht->table = newTable;
	ht->tableSize = newTableSize;		
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	int hash;
	int check = 0;
	struct hashLink *cur;

	if(HASHING_FUNCTION == 1)
	{
		hash = stringHash1(k);
	}
	else if(HASHING_FUNCTION == 2)
	{
		hash = stringHash2(k);
	}

	int idx = hash % ht->tableSize;
	
	cur = ht->table[idx];
	if(cur == NULL)
	{
		check = 2;
	}
	while(cur != NULL && check == 0) 
	{

		{
			if(strcmp(cur->key, k) == 0)
			{
				check = 1;
			}
			else
			{
				cur = cur->next;
				check = 2;
			}
		}
	}

	if(check == 1)
	{
		cur->value = v;
	}
	else if(check == 2)
	{
		struct hashLink *new = malloc(sizeof(struct hashLink));
		new->key = k;
		new->value = v;
		cur = ht->table[idx];
		new->next = cur;
		ht->table[idx] = new;
		ht->count++;
		//create a hashLink and put it in the bucket.
	}

	float load = tableLoad(ht);
	if(load > LOAD_FACTOR_THRESHOLD)
	{
		_setTableSize(ht, (2*ht->tableSize));
			for(int i = 0; i < ht->tableSize; i++)
			{
				cur = ht->table[i];
				while(cur != NULL)
				{
					insertMap(ht, cur->key, cur->value);
					cur = cur->next;
				}

			}
	}	



	
	
	
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType atMap (struct hashMap * ht, KeyType k)
{ 
	int hash;
	struct hashLink *cur;
	
	if(HASHING_FUNCTION == 1)
	{
		hash = stringHash1(k);
	}
	else if(HASHING_FUNCTION == 2)
	{
		hash = stringHash2(k);
	}

	int idx = hash % ht->tableSize;

	cur = ht->table[idx];
	while(cur != 0)
	{
		if(strcmp(cur->key, k) == 0)
		{

			return cur->value;
		}
		else
		{
			cur = cur->next;
		}
	}

	return NULL;

}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	struct hashLink *cur;
	int hash;
	if(HASHING_FUNCTION == 1)
	{
		hash = stringHash1(k);
	}
	else if(HASHING_FUNCTION == 2)
	{
		hash = stringHash2(k);
	}
	int idx = hash % ht->tableSize;
	cur = ht->table[idx];
	while(cur != 0)
	{
		if(strcmp(cur->key, k) == 0)
			return 1;
		else
			cur = cur->next;
	}
	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	struct hashLink *cur;
	struct hashLink *temp;
	int hash;
	if(HASHING_FUNCTION == 1)
	{
		hash = stringHash1(k);
	}
	else if(HASHING_FUNCTION == 2)
	{

		hash = stringHash2(k);
	}
	int idx = hash % ht->tableSize;
	cur = ht->table[idx];
	while(cur != 0)
	{
		if(strcmp(cur->key, k) == 0)
		{
			temp = cur;
			cur = cur->next;
			free(temp);
			ht->table[idx] = cur;
		}
		else
			cur = cur->next;
	}
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	return ht->count;	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	int count;
	for(int i = 0; i < ht->tableSize; i++)
	{
		if(ht->table[i] == NULL)
			count++;
		
	}
	return count;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	int hlCount = ht->count;
	int bCount = ht->tableSize;
	double ratio = hlCount / (double) bCount;
	return ratio; 
}

/* print the hashMap */
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d ->", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}