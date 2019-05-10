#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"
#include "linkedList.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.

 when there are no more words in the input file this function will return NULL.

 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/
  int* i;
  char* temp;
  LinkedList* l;
  FILE* f;
  hashMap* hM;

  hM= malloc(sizeof(struct hashMap*));
  temp = malloc(sizeof(char*));
  l= malloc(sizeof(struct LinkedList*));
  f = malloc(sizeof(FILE*));

  if(argc <1){
    printf("not enough args");
    exit(0);
  }
  initMap(hM, 50);

  f=fopen(argv[1], "r");
  initLinkedList(l);

  while(!feof(f)){
    temp= getWord(f);
    if(!containsLinkedList(l, temp) && temp[0]!='\r\n'){
      pushLinkedList(l, temp);
      printf("added %s to list\n", topLinkedList(l));
    }
    if(containsKey(hM, temp)){
      i= atMap(hM, temp);
      /*insertMap(hM, temp, (*i) + 1); */
      (*i)++;
      printf("added %d to map\n", *(atMap(hM, temp)));
    }
    else{
      insertMap(hM, temp, 1);
      printf("added %d to map\n", *(atMap(hM, temp)));
    }
    /*free(temp);*/
  }
  while(!isEmptyLinkedList(l)){
    temp=topLinkedList(l);
    if(*temp!=0)
      printf("Word %s : times %d\n", temp, *(atMap(hM, temp)));
    /*printf("ascii of first char is %d\n", temp[0]); */
    popLinkedList(l);
    free(temp);
  }

  freeMap(hM);
  free(hM);
  free(temp);
  freeLinkedList(l);
  free(l);
  return 0;
}

char* getWord(FILE *file){
  int length = 0;
	int maxLength = 16;
	char character;

	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);

	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}

	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}
