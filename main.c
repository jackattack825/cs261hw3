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
  int ch;
  char* temp;
  LinkedList* l;
  FILE* f;
  hashMap* hM;
  if(argc <1){
    printf("not enough args");
    exit(0);
  }
  initMap(hM, 16);
  f=fopen(argv[1], 'r');
  ch= getc(f);
  initLinkedList(l);

  while(ch!= EOF){
    temp= getWord(f);
    pushLinkedList(l, temp);
    if(containsKey(hM, temp))
      insertMap(hM, temp, atMap(hM, temp) +1);
    else
      insertMap(hM, temp, 1);
    ch=getc(f);
  }
  while(!isEmptyLinkedList(l)){
    temp= topLinkedList(l);
    popLinkedList(l);
    printf("%s : %d\n", temp, atMap(hM, temp));
  }
  return 0;
}

char* getWord(FILE *file){
  char* c;
  fgets(c, 20, file);
  return c;
}
