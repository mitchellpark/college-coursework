/**
 * Author: Mitchell Park
 * Project 5
 * This file implements a struct called pqueue and various functions necessary for huffman.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"	

/* A priority queue */
struct pqueue {
	int count;		//counts the number of elements
	int length;		//Keeps track of the array capacity
	void **data;		//Array of elements of type void*
	int (*compare)();		//function to compare elements
};

/*
 * Creates a pqueue, allocating memory for all of its members. The initial length of the
 * "data" array is 10, and it holds elements of type void*. 
 * Runtime: O(1)
 */
PQ *createQueue(int (*compare)()) {
	PQ *pq;
	pq = malloc(sizeof(PQ));
	assert(pq!=NULL);

	pq->count = 0;
	pq->length = 10;
	pq->data = malloc(sizeof(void*)*10);
	pq->compare = compare;

	return pq;
}

/*
 * Traverses the array of the pqueue to free all the element. After freeing the 
 * array itself, it deallocates memory of the pqueue.
 * Runtime: O(n), where n is the number of elements in the pqueue.
 */
void destroyQueue(PQ *pq) {
	int i; 
	for(i=0; i<pq->count; i++){
		free(pq->data[i]);
	}
	free(pq->data);
	free(pq);
}

/*
 * Returns the number of elements in the pquque
 * Runtime: O(1)
 */
int numEntries(PQ *pq){
	return pq->count;
}

/*
 * Adds an element, initially, at the end of the array. Swaps with parent until
 * the array is organized in a min-heap fashion. Also, if the array is full, we double the size
 * of the array with realloc(). pqueue's count is incremented in the end.
 * Runtime: O(log n), where n is the number of elements in the pqueue.
 */
void addEntry(PQ *pq, void *entry) {
	assert(pq!=NULL && entry!=NULL);

	if(pq->count==pq->length){
		pq->data = realloc(pq->data,  sizeof(void*)*pq->length*2);		//The array is full, so we double its size.	
		pq->length = pq->length*2;
	}

	pq->data[pq->count] = entry;									

	int index = pq->count;		//Initial index set to the last, because we start from the bottom
	while(pq->compare(pq->data[index],pq->data[(index-1)/2])<0) {		//Loop runs when parent's value is larger than the child's
		
		/* swapping with parent */
		void* tmp = pq->data[(index-1)/2];
		pq->data[(index-1)/2] = pq->data[index];					
		pq->data[index] = tmp;

		index = (index-1)/2;
	}

	pq->count++;											
}
/**
 * Removes the first element in the pqueue, fills the empty spot with the value of the last
 * elemnt, and reheapsdown. In the reheapdown, the parent always swaps with the smaller child, 
 * swapping downwards until it is at the right place. At the end, we return the removed element.
 * Runtime: O(logn), where n is the number of elements in the pqueue	
 */
void *removeEntry(PQ *pq) {
	void* first=pq->data[0];			//To return the first element at the end
	int index=0, smallerIndex=0;
	
	pq->data[index] = pq->data[pq->count-1];		//first element is swapped with the last
	pq->count--;

	while( (index*2)+1 < pq->count){		//The loop runs while is a left child
		smallerIndex = (index*2)+1;		//smallestIndex holds the index of the smaller child, initially set as the left child.

		/* If there is a right child, we compare. */
		if( (index*2)+2 < pq->count) {
			if(pq->compare(pq->data[(index*2)+1],pq->data[(index*2)+2])<0){
				smallerIndex = (index*2)+1;
			} else{
				smallerIndex = (index*2)+2;
			}
		}
		
		/* Now that we know the smaller child, we compare with the parent and swap if it is smaller. */
		if (pq->compare(pq->data[smallerIndex],pq->data[index])<0) {		
			void* tmp = pq->data[smallerIndex];
			pq->data[smallerIndex] = pq->data[index];
			pq->data[index] = tmp;
			index = smallerIndex;											
		} else break;	//If the parent is smaller, we know that the parent is at the right place. We can exit the loop.
	}

	return first;
}