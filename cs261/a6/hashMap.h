# ifndef HashMap
# define HashMap

# define KeyType char *
# define ValueType void*

/*
 this is useful for you in answering the questions. if your write your code such
 that you call stringHash1 when HASHING_FUNCTION==1 and stringHash2 when
 HASHING_FUNCTION==2 then you only need to change this value in order to switch
 hashing functions that your code uses. you are not required to use this value
 though.
 */
# define HASHING_FUNCTION 2

/* load factor threshold for resizing the hash table */
# define LOAD_FACTOR_THRESHOLD 0.75

int stringHash1(char * str);

int stringHash2(char * str);

struct hashMap *createMap(int tableSize);

void deleteMap(struct hashMap *ht);

void insertMap (struct hashMap * ht, KeyType k, ValueType v);

ValueType atMap (struct hashMap * ht, KeyType k);

int containsKey (struct hashMap * ht, KeyType k);

void removeKey (struct hashMap * ht, KeyType k);

int size (struct hashMap *ht);

int capacity(struct hashMap *ht);

int emptyBuckets(struct hashMap *ht);

float tableLoad(struct hashMap *ht);

void printMap (struct hashMap * ht);
void printValue(ValueType v);

# endif
