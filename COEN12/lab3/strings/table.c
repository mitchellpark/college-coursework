#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

unsigned strhash(char *s);

int *search(SET *sp, char *elt);

typedef struct set{
	int count;		//Current number of elements in set
	int length;		//Length of set, initialized at max length
	char**data;		//Array to store the elements
	char *flags;	//flgas with choices 'E', 'F', or 'D'

}SET;
/*
 * Initializes the set with a parameter for max length.
 */
SET *createSet(int max){

	SET *sp;
	sp = malloc(sizeof(SET));
	sp->count = 0;
	sp->length = max;
	sp->data = malloc(sizeof(char*)*max);
	sp->flags = malloc(sizeof(char)*max);
	memset(sp->flags, 'E' ,sizeof(char)*max); //flags are all set as empty

	assert(sp!=NULL);

	return sp;
}

/*
 * Deallocates all the memory for the set, freeing the individual elements of the data array,
 * the array itself, and lastly, the set itself.
 */
void destroySet(SET *sp){
	assert(sp!=NULL);
	
	int i;
	for(i =0; i<sp->count; i++){
		free(sp->data[i]);
	} 
	free(sp->data);
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
void addElement(SET *sp, char *elt){
	assert(sp!=NULL && elt!=NULL);

	/* 
	 * Uses search() to assure that the spot was not an 'F', and retrieve
	 * the appropriate index to add the element. The counter for the set's elements
	 * is incremeneted at the end. 
	 */
	if(sp->count != sp->length){
		int *res = search(sp, elt);
		int notFilled = res[0];
		int index = res[1];

		if(notFilled){
			sp->data[index] = strdup(elt);
			sp->flags[index] = 'F';
			sp->count++;
				
		}
	}
}

/*
 * Void function that removes the given element from the set.
 */
void removeElement(SET *sp, char *elt){
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
		free(sp->data[index]);
		sp->flags[index]='D';
		sp->count--;
	}
	

}

/*
 * Returns the element when found in the set. If not, returns NULL.
 */
char *findElement(SET *sp, char *elt){
	assert(sp!=NULL && elt !=NULL);

	/* Executes if search() says that the element's spot is an 'F' (and thus filled with the element) */
	if(!search(sp,elt)[0]){
		return elt;	
	}
	return NULL;


}

/*
 * Returns an array of elements in the set pointed by sp.
 */
char **getElements(SET *sp){
	assert(sp!=NULL);

	char **elts;
	elts = malloc(sizeof(char*)*sp->count);
	assert(elts!=NULL);

	//Copies elements from spaces that are filled from the set to the array
	int i,j;
	j=0;
	for(i=0; i<sp->length; i++){
		if(sp->flags[i]=='F'){
			elts[j] = sp->data[i];
			j++;
		}
	}

	return elts;
}

/*
 * Performs a linear search to find an element in the set. Returns an array
 * of length 2, whose first element indicates that the element's spot is occupied.
 * The second element of the array is the index of the element.
 */
int *search(SET *sp, char *elt){
	assert(sp!=NULL && elt!=NULL);

	int res[2];
	int hash = strhash(elt)%sp->length; //hash function
	
	int deletedSpot = 0; 	//Holds the value of the deleted index
	int notSeenDelete = 1;	//0 if a 'D' has been seen

	int i;
	for(i=hash; i<sp->length; i++){
		switch(sp->flags[i]){
			case 'E':
				if(deletedSpot) break; //In the case that a 'D' has been seen

				res[0] = 1;
				res[1] = i;
				return res;
			case 'F':
				if(!strcmp(sp->data[i], elt)){
					res[0] = 0;
					res[1] = i;
					return res;
				}	
				break;
			case 'D':
				if(notSeenDelete){
					deletedSpot = i;
					notSeenDelete = 0;
				}
		}
	}
			
	res[0] = 1;
	res[1] = deletedSpot;
	return res;
}

/* Provided hash function */
unsigned strhash(char *s){
	unsigned hash =0;
	while(*s != '\0'){
		hash = 31 * hash + *s ++;
	}
	return hash;

}
