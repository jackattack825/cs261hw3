#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
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

void freeMap (struct hashMap * ht)
{  /*write this*/
	int i;
	for(i=0; i<ht->tableSize; i++){
		free(ht->table[i]);
	}
	free(ht->table);
	free(ht);
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
	int hash= stringHash1(k);
	int index= (int) (labs(hash) % ht->tableSize);
	struct hashLink* newLink= (struct hashLink*) malloc(sizeof(struct hashLink));
	assert(newLink);
	newLink->value=v;
	newLink->next= ht->table[index];
	ht->table[index]=newLink;
	ht->count++;

	float loadFac = ht->count/ht->tableSize;
	if(loadFac > Max_Load)
		_resi
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
}
