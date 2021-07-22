/*
 * Author: Mitchell Park
 * Title: Project 2, unsorted.c
 * What this file does: This interface implements adding, removing,
 * accessing, searching, creating, and deleting functions for the unsorted SET.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct set SET;

static int search(SET *set, char *elem);	

struct set {
	int count;      //number of elements set holds	
	int len;        //length of array
	char **arr;     //array of strings
};

/*
 * This function allocates memory to create a set that creates an array, keeps track of its length, 
 * and keeps terack of the number of elements in the set. 
 * Runtime: O(1)
 */
SET *createSet(int maxLen){

	SET *set;
	set=malloc(sizeof(SET));			
	assert(set!=NULL);

	set->count = 0;							
	set->len=maxLen;							
	set->arr = malloc(sizeof(char*)*maxLen);	//the set is given an array with the maximum length.
	assert(set->arr!=NULL);
	return set;
}

/*
 * This function destroys the set by freeing the memory of the elements of the array arr,
 * the array itself, and lastly, the set.
 * Runtime: O(n)
 */
void destroySet(SET *set){
    assert(set!=NULL);
	int i;

	// elements are freed
    for(i=0; i<set->count; i++){
        free(set->arr[i]);
    }

    //array and set are freed
	free(set->arr);				
	free(set);					
}

/*
 * Returns the number of elements in the set
 * Runtime: O(1)
 */
int numElements(SET *set){
	assert(set!=NULL);
	return set->count;
}

/*
 * This function performs a linear search to find the provided element in the set. If the element is 
 * not found, it is added to the end of the set. The size of the set is incremented after the addition.
 * Runtime: O(n)
 */
void addElement(SET *set, char *elem){
	assert(set!=NULL && elem!=NULL);

    //If the element is not found, it is added to the end of the array.
	if(search(set,elem)==-1){
		set->arr[set->count] = strdup(elem);	
		set->count++;
	}
}

/*
 * This function does a linear search to find the given element. When found, its memory is freed, and the last
 * element replaces the emptied space.
 * Runtime: O(n)
 */
void removeElement(SET *set, char *elem){
	assert(set!=NULL && elem!=NULL);

	int index = search(set,elem);	//index of the element

    if(index!=-1){
		free(set->arr[index]);	//memory is freed	

        //Last element takes the freed place. Then, the size of the set is decremented.
		set->arr[index] = set->arr[set->count-1];	    
		set->arr[set->count-1] = NULL;
		set->count--;
	}
}

/*
 * This function does a linear search through the set and returns the given element. If the element is
 * not found, it returns NULL.
 * Runtime: O(n)
 */
char *findElement(SET *set, char *elem){
	assert(set!=NULL && elem!=NULL);
	int i;

	//Iterates through the array, using strcmp() to determine if value is seen
	for(i=0; i<set->count; i++){
		if( strcmp(set->arr[i],elem)==0 ){
			return elem;
		}
	}
	return NULL;
}

/*
 * This function returns a copy of the set's array for the user.
 * Runtime: O(n)
 */
char **getElements(SET *set){
	assert(set!=NULL);
	char **array;

	array = malloc(sizeof(char*)*set->count);	 //assigns the size of the set to the newly created array
	for (int i=0; i<set->count; i++){
		array[i]=strdup(set->arr[i]);			//Duplicates of the set elements are copied into the array
	}
	return array;
}

/*
 * Performs a linear search in the set. If the given element is found, its index is returned. Else,
 * it returns -1. 
 * Runtime: O(n)
 */
static int search(SET *set, char *elem){
	assert(set!=NULL && elem!=NULL);
	int i;

	//Iterates through the array linearly, using strcmp() to determine if element is seen
	for(i=0;i<set->count;i++){
		if(strcmp(set->arr[i],elem)==0){
			return i;
		}
	}
	return -1;	
}