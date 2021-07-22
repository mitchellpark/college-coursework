#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

/*
 * Author: Mitchell Park
 * This file implements the functions for the "set" interface.
 * In those functions, it uses many of the functions in list.c.
 */
typedef struct set{
	int count;		//number of elements
	int length; 	//length of array
	LIST **lists; 		//array of lists
	int (*compare)(); 		//function for comparing elemnts
	unsigned(*hash)(); 		//hash function
} SET;

/*
 * Creates a set, initializing and allocating memory for all of its variables.
 * The runtime is O(n), where n is the number of the set, because for each index in "lists,"
 * a list is initialized. 
 * Runtime: O(n)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)() ){
	SET *sp;

	sp = malloc(sizeof(SET));									
	assert(sp!=NULL);

	sp->count = 0;											//The current number of items in the set
	sp->length = maxElts;							//the length of the array
	sp->lists = malloc(sizeof(void*)*sp->length);			
	sp->compare = compare;
	sp->hash = hash;

	int i;
	for(i=0; i<sp->length; i++) {							//"lists" will store an arroy of lists.
		sp->lists[i] = createList(compare);
	}

	assert(sp->lists!=NULL);
	
	return sp;
}

/*
 * Frees memory of lists, and then the set.
 * Runtime: O(1)
 */
void destroySet(SET *sp){
	free(sp->lists);						
	free(sp);							
}

/*
 * Returns the number of elements in the set
 * Runtime: O(1)
 */
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
}

/*
 * Uses findItem and addFirst in "list.c" to add items, making sure to not add duplicate values.
 * The index of "lists" is determnined by the provided hash function.
 * Runtime: O(n)
 */
void addElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);

	int index = (*sp->hash)(elt)%sp->length;
	LIST *item = sp->lists[index];

	if(findItem(item,elt)==NULL) {			
		addFirst(item,elt);
		sp->count++;
	}
	
}

/*
 * Uses findItem and removeItem of "list.c" to remove an element. If the element is found, then it is removed.
 * Finally, the number of elements in the list is decremented.
 * Runtime: O(n)
 */
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);

	int index = (*sp->hash)(elt)%sp->length;
	LIST *item = sp->lists[index];

	if (findItem(item,elt)!=NULL) {			//When the value is found, remove it.
		removeItem(item,elt);
		sp->count--;
	}
}

/*
 * Basically the findElement function; returns the item if found, and NULL if not.
 * Runtime: O(n)
 */
void *findElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);

	int index = (*sp->hash)(elt)%sp->length;
	LIST *item = sp->lists[index];
	return findItem(item,elt);
}
/*
 * Returns an array of the elements in the set for the user. Because "arr" is a 2d array, we have 2 for loops, retrieving
 * an array of elements with getItems,  and copying the values over to an index of "arr."
 * Runtime: O(n^2)
 */
void *getElements(SET *sp){
	assert(sp!=NULL);
	void **arr;
	arr = malloc(sizeof(void*)*sp->count);		// declare array and allocate memory to be size of the number of elements

	int i, j, copyCount = 0;
	for(i=0; i<sp->length; i++){
		void **copiedArr = getItems(sp->lists[i]);

		for (j=0; j<numItems(sp->lists[i]); j++) {
			arr[copyCount] = copiedArr[j];
			copyCount++;
		}
	}
	return arr;
}