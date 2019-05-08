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
  initMap(hM, 16);

  insertMap(hM, "hello", 1);
  if(containsKey(hM, "hello")){
    printf("success\n");
    printf("entry is %d\n", *(atMap(hM, "hello")));
    removeKey(hM, "hello");
  }

  f=fopen(argv[1], "r");
  initLinkedList(l);

  pushLinkedList(l, "dog");
  if(containsLinkedList(l, "dog")){
    printf("success\n");
    printf("entry is %s\n\n\n\n\n", topLinkedList(l));
    popLinkedList(l);
  }

  while(!feof(f)){
    temp= getWord(f);
    if(!containsLinkedList(l, temp)){
      pushLinkedList(l, temp);
      printf("added %s to list\n", topLinkedList(l));
    }
    if(containsKey(hM, temp)){
      insertMap(hM, temp, *(atMap(hM, temp)) +1);
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
    printf("Word %s : times %d\n", temp, *(atMap(hM, temp)));
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
  char* c=malloc(15* sizeof(char));
  int count=0;
  int temp;
  while((temp = fgetc(file)) != EOF)
	{
		if(temp == ' ' || temp == '\n')
		  break;
		else
		{
      c[count]=temp;
			count++;
		}
	}
  c[++count]='\n';
  printf("obtained %s\n", c);
  return c;
}
