/*
 * Author: Mitchell Park
 * This file provides the interface for a struct called set to represent a 
 * sorted set. It implements functionalities such as creation and deletion, 
 * addition and removal, accessing, and searching.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct set SET;

static int search(SET *set, char *elem, bool *found);	

struct set {
	int count;	//number of elements set holds
	int len;    //length of array
	char **arr; //array of strings
};

/*
 * This function allocates memory to create a set, initializing variables to
 * represent of the array, its length, and the counter of how many elements 
 * are in the set.
 * Runtime: O(1)
 */
SET *createSet(int maxLen){

	SET *set;
	set=malloc(sizeof(SET));					
	assert(set!=NULL);

    //set variables are initilizaed, the assert() ensures that the array exists
	set->count = 0;								
	set->len=maxLen;							
	set->arr = malloc(sizeof(char*)*maxLen);
	assert(set->arr!=NULL);

	return set;
}

/*
 * This function destroys the set, freeing the memory of the elements of the array,
 * the array itself, and lastly, the set. 
 * Runtime: O(n)
 */
void destroySet(SET *set){
	int i;

	//array elements are freed
	for(i=0; i<set->count; i++){	
		free(set->arr[i]);
	}

    //The array and set are freed
	free(set->arr);						
	free(set);							
}

/*
 * This function returns the number of elements in the set.
 * Runtime: O(1)
 */
int numElements(SET *set){
	assert(set!=NULL);
	return set->count;
}

/*
 * This function, as opposed to search() in unsorted.c, performs a binary search. It uses bounds
 * called lo, mid, and hi as indexes. Variable diff represents the difference between the observed
 * array element and the parameter elem, so diff>0 would mean that the element exists later in the array, 
 * while diff>0 means that the current index is to high. Bounds are updated accordingly, cutting the
 * logarithmically.
 * Runtime: O(logn)
 */
int search (SET *set, char *elem, bool *found) {
    assert(set!=NULL && elem!=NULL);
	int lo, hi, mid, diff;	
	lo = 0;
	hi=set->count-1;		//lo and hi are the min and max indexes of the array, respectively.

	while (lo<=hi) {
		mid = (lo + hi)/2;
		diff = strcmp(elem,set->arr[mid]); //the difference between the element and the array element's value

		if(diff > 0) {	    //The element is located at a higher index
            lo = mid + 1;
		} else if(diff <0){     //The element is located at a lower index
			hi = mid -1;
		}else {
			*found = true;  //The element is found, so index is returned
			return mid;
		}
	}
	*found = false;				//The element was not found after traversing the whole set
	return lo;					//Returns the appropriate index for the element to go 
}

/*
 * This function performs a binary search to provide an index for the element 
 * (-1, if not found). If the given element is a new one, it is placed where 
 * it should go lexicographically, and the elements after it are shifted one
 * place to the right.
 * Runtime: O(n)
 */
void addElement(SET *set, char *elem){
	assert(set!=NULL && elem!=NULL);
	bool found;
	int index = search(set, elem, &found);	    //Index of the element

	if(!found) {
		//Starting ffrom the end, every element with a greater index is shifted right.
		for(int i=set->count; i>index; i--) {
			set->arr[i] = set->arr[i-1];
		}

        //The element is duplicated and placed at the appropriate index.
		set->arr[index]=strdup(elem); 
		set->count++;
	}
}

/*
 * This function performs a binary search for the element. If element exists, 
 * the memory is freed, and the elements to its right are shifted one place 
 * to the left. 
 * Runtime: O(n)
 */
void removeElement(SET *set, char *elem){
	assert(set!=NULL && elem!=NULL);
	bool found;
	int index = search(set, elem, &found);			//index of the element

    /* If the element is found, the space is freed, and the for loop shifts the 
      other elements. Lastly, the size of the set is decremeneted. */
	if(found) {
		free(set->arr[index]);	

		for(int i=index+1; i<set->count; i++){
			set->arr[i-1] = set->arr[i];
		}

		set->count--;
	}
}

/*
 * This function performs a binary search to find the given element. If found,
 * the element is returned. Else, it returns NULL.
 * Runtime: O(logn)
 */
char *findElement(SET *set, char *elem){
	assert(set!=NULL && elem!=NULL);
	bool found;
	int index = search(set, elem, &found); //index of the element

	if (found) return elem;

	return NULL;
}
/*
 * This function returns a duplicate of the set's array to the user.
 * Runtime: O(n)
 */
char **getElements(SET *set){
	assert(set!=NULL);
	char **array;
	array = malloc(sizeof(char*)*set->count);	//An array with same length as the set's array is initialized

	for(int i=0; i<set->count; i++){
		array[i]=strdup(set->arr[i]);				//Duplicates of the original array's elements are copied to the new array
	}
	return array;
}