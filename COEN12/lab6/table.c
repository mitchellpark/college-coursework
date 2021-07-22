/*
 * Author: Mitchell PArk
 * Assignment: Lab 6 
 */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "set.h"

int *search(SET *sp, void *elt);
static void quicksort(SET *sp, void**arr,int lo, int hi);
int partition(SET *sp,void**arr,int lo, int hi);
static void swap(void *a, void *b);

typedef struct set{
	int count;				//Current number of elements in set
	int length;				//Length of set, initialized at max length
	void**data;				//Array to store the elements
	char *flags;			//flags that have choices 'E', 'F', or 'D'
	int (*compare)();		//compare function
	unsigned (*hash)();		//hash function

}SET;

SET *sp;

/* 
 * Initializes the set with parameters for max length, compare function, and hash function.
 */
SET *createSet(int max,int (*compare)(),unsigned (*hash)()){
	assert(compare!=NULL && hash!=NULL);

	sp =malloc(sizeof(SET));
	sp->count =0;
	sp->length=max;

	//Memory allocated for the set's data and flags. Flags are set as empty.	
	sp->data = malloc(sizeof(void*)*max);
	sp->flags = malloc(sizeof(char)*max);
	sp->compare =compare;
	sp->hash =hash;

    int i;
    for(i=0; i<max; i++){
        sp->flags[i] = 'E';
    }

	assert(sp!=NULL);

	return sp;
}

/*
 * Deallocates all the memory for the set, freeing flags, data, and the set itself.
 */
void destroySet(SET *sp){
	assert(sp!=NULL);
	free(sp->data);
	free(sp->flags);
	free(sp);

}

/*
 * Returns the number of elements in the set.
 */
int numElements(SET *sp){
	return sp->count;
}

/*
 * Void function that adds the given element in the appropriate index.
 */
void addElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);

	/* 
	 * Uses search() to assure that the spot was not an 'F', and retrieve
	 * the appropriate index to add the element. The counter for the set's elements
	 * is incremeneted at the end. 
	 */
	if(sp->count<sp->length){
		int *res = search(sp, elt);
		int notFilled = res[0];
		int index = res[1];

		if(notFilled){
			sp->data[index] = elt;
			sp->flags[index] = 'F';
			sp->count++;
		}
	}
}

/*
 * Void function that removes the given element from the set.
 */
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL && elt!=NULL);

	int *res = search(sp, elt);
	int notFilled = res[0];
	int index = res[1];

	/*
	 *	Like addElement(), uses search() to assure that the spot is
	 *  marked 'F', and to retrieve the appropriate index to mark as deleted.
	 *  Lastly, the counter of the set's elements is decremented.
	 */
	if(!notFilled){
		//sp->data[index] = NULL;
		sp->flags[index] = 'D';
		sp->count--;
	}
	

}

/* 
 * Returns the element when found in the set. If not, returns NULL.
 */ 
void *findElement(SET *sp, void *elt){
	assert(sp!=NULL && elt !=NULL);
	int *res = search(sp, elt);
	int notFound = res[0];
	int index = res[1];
	/* Executes if search() says that the element's spot is an 'F' (and thus filled with the element) */
	if(!notFound){
		return sp->data[index];	
	}
	return NULL;
}

/*
 * Returns an array of elements	in the set pointed by sp.
 */ 
void *getElements(SET *sp){
	assert(sp!=NULL);
	void **arr;

	arr = malloc(sizeof(void*)*sp->count);
	assert(arr!=NULL);

	//Copies elements from spaces that are filled from the set to the array
	int i,j;
	j=0;
	for(i=0; i<sp->length; i++){
		if(sp->flags[i]=='F'){
			arr[j] = sp->data[i];
			j++;
		}
        
	}
	quicksort(sp,arr,0,sp->count-1);
	return arr;
}

/*
 * Performs a linear search to find an element in the set. Returns an array
 * of length 2, whose first element indicates that the element's spot is occupied.
 * The second element of the array is the index of the element.
 */
int *search(SET *sp, void *elt){	
	int hash = (*sp->hash)(elt)%sp->length; //hash function
	int index; 
	int res[2];
	int deletedSpot = 0;	//Holds the value of the deleted index
	int notSeenDelete = 1;		//Indicates if a 'D' has been seen

	int i;
	for(i=0; i<sp->length; i++){	
		index = (hash+i)%sp->length;
			if(sp->flags[index]=='E'){
				if(deletedSpot) break; //In the case that a 'D' has been seen

					res[0] = 1;
					res[1] = index;
					return res;
			}
			if(sp->flags[index]=='F'){
				if((*sp->compare)(sp->data[index], elt)==0){
						res[0] = 0;
						res[1] = index;
						return res;
					}	
			}
			if(sp->flags[index]=='D'){
				if(notSeenDelete){
						deletedSpot = index;
						notSeenDelete = 0;
					}
			}
	}		
	res[0] = 1;
	res[1] = deletedSpot;
	return res;
}

/*
 * Recursively calls partition() to perform Quicksort.
 * Best Case: O(nlogn). Worst Case: O(n^2) 
 */
static void quicksort(SET *sp, void**arr,int lo, int hi){
	assert(arr!=NULL);
	
	if(lo < hi){
		int p = partition(sp,arr,lo,hi);
		quicksort(sp, arr, lo, p-1);
		quicksort(sp, arr, p+1, hi);
		
	}
}

/*
 * Traverses the given array, swapping values for quicksort(). Finally, returns
 * the index of the value swapped last.
 * Runtime: O(n)
 */
int partition(SET *sp,void**arr,int lo, int hi){
	void*pivot =arr[hi];	//we pick the last element as the pivot
	int i=lo-1;
	int j;
	
	for(j=lo;j<=hi-1;j++){
		if((*sp->compare)(arr[j], pivot)<0){		//If we run into a value smaller then the pivot, we swap
			i++;			
			void* tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
					
		}

	}
	/* Final swap */
	i++;		
	void *tmp = arr[hi];
	arr[hi] = arr[i];
	arr[i] = tmp;
	return i;

}