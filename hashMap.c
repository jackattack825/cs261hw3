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
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
	float loadFac;
	int hash, index;
	struct hashLink* newLink;
	if(!containsKey(ht, k)){
		hash= stringHash1(k);
		index= (int) (labs(hash) % ht->tableSize);
		newLink= (struct hashLink*) malloc(sizeof(struct hashLink));
		assert(newLink);
		newLink->value=v;
		newLink->next= ht->table[index];
		ht->table[index]=newLink;
		ht->count++;
	}
	else{
		hash= stringHash1(k);
		index= (int) (labs(hash) % ht->tableSize);
		ht->table[index]->value=v;
	}

	loadFac = ht->count/ht->tableSize;

	if(loadFac > 0.75){
		int oldsize = ht->tableSize;
		struct hashMap *oldht = ht;
		struct hashLink *cur, *last;
		int i;
		initMap(ht, oldsize*2);
		free(oldht);
		for(i=0; i<oldsize; i++){
			cur = oldht->table[i];
			while(cur!=NULL){
				insertMap(ht, cur->key, cur->value);
				last=cur;
				cur=cur->next;
				free(last);
			}
		}
		free(oldht);
	}
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
	int hash, index;
	hash= stringHash1(k);
	index= (int) (labs(hash) % ht->tableSize);
	return &(ht->table[index]->value);
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
	int hash, index;
	hash= stringHash1(k);
	index= (int) (labs(hash) % ht->tableSize);
	if(ht->table[index]==NULL)
		return 0;
	return 1;
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
	int hash, index;
	struct hashLink* curr;
	struct hashLink* prev;
	hash= stringHash1(k);
	index= (int) (labs(hash) % ht->tableSize);
	if(ht->table[index]==NULL)
		return;
	prev=ht->table[index];
	curr=prev->next;
	do{
		free(prev);
		prev=curr;
		if(curr!=NULL)
			curr=curr->next;
	}	while(curr!=NULL);
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
	int i;
	hashLink* link;
	int count=0;
	for(i=0; i<ht->tableSize; i++){
		link=ht->table[i];
		if(link!=NULL){
			count++;
			while(link->next!=NULL){
				count++;
				link=link->next;
			}
		}
	}

	return count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int i, count;
	for(i=0; i<ht->tableSize; i++){
		if(ht->table[i]==NULL)
			count++;
	}
	return count;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
	return ht->count/ht->tableSize;
}
