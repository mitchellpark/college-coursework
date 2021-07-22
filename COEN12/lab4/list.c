/*
 *	Author: Mitchell Park
 *	This file implements the functions for "list" interface. To represent the linked list,
 *	it declares to structs, list and node.
 */
#include <stdlib.h>
#include <assert.h>
#include "list.h"
/*
 * A struct that represents a node of a list.
 */
typedef struct node{
	void *data;		
	struct node *next;
	struct node *prev;
} NODE;

/*
 *	A struct that represents the list itself.
 */
struct list {
	int count;	//the number of elements
	struct node *head;	//pointer to the head node
	int (*compare)();	//function to compare elements
};

/*
 *	Initializes a list with count 0 and a dummy node, whose next and prev pointers
 *	we set to itself. Every variable of the struct list is initialized. 
 * Runtime: O(1)
 */
LIST *createList(int (*compare)()) {
	LIST *lp;

	lp=malloc(sizeof(LIST));						
	assert(lp!=NULL);

	lp->count = 0;	
	lp->head = malloc(sizeof(struct node));
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	lp->compare = compare;		

	return lp;
}

/*
 *	Frees the memory for all nodes, the list's other variables, eventually deallocates the list itself.
 *	Runtime: O(n)
 */
void destroyList(LIST *lp) {
	assert(lp!=NULL);
	while(lp->count>0) {
		removeLast(lp);
	}
	free(lp);
}

/*
 * Returns the number of elements in the list
 * Runtime: O(1);
 */
int numItems(LIST *lp) {
	assert(lp!=NULL);
	return lp->count;
}

/*
 * Adds the given value to the beginning of the list. It takes the space after the
 * dummy node (lp->head->next). The previous head node now becomes the node after the new
 * head node, and pointers are updated accordingly.
 * Runtime: O(1)
 */
void addFirst(LIST *lp, void *item) {
	NODE *toAdd = malloc(sizeof(struct node));
	assert(toAdd!=NULL);

	toAdd->data = item;

	toAdd->next = lp->head->next;
	toAdd->prev = lp->head;
	toAdd->next->prev = toAdd;
	lp->head->next = toAdd;


	lp->count++;
}
/* 
 * Adds a node with the given value to the end of the list. The process of updating pointers
 * is similar to that of addFirst.
 * Runtime: O(1)
 */
void addLast(LIST *lp, void *item) {
	NODE *toAdd = malloc(sizeof(struct node));
	assert(toAdd != NULL);

	toAdd->data = item;

	toAdd->prev = lp->head->prev;
	toAdd->next = lp->head;		//points to head because it is a circularly linked list
	lp->head->prev = toAdd;
	toAdd->prev->next = toAdd;

	lp->count++;
}

/*
 * Removes the first element of the list. The function declares variable firstNode, which
 * represents the first node (not the dummy node). firstNode is removed by updating dummy node's "next" 
 * pointer to the node that was after firstNode. Lastly, the memory of firstNode is freed.
 * Runtime: O(1)
 */
void *removeFirst(LIST *lp) {
	assert(lp->count>0);

	NODE *firstNode = lp->head->next;
	void *firstData = firstNode->data;

	lp->head->next = firstNode->next;
	firstNode->next->prev = lp->head;
	free(firstNode);

	lp->count--;

	return firstData;
}

/*
 * Function: removeLast
 * Removes the last element in the list. Variable lastNode represents the last node, and to delete it,
 * the "prev" pointer has to point to head (the list is circularly linked). Thus, the "prev" pointer of head
 * must be updated to point to the new last node. Lastly, lastNode is freed from memory.
 * Runtime: O(1)
 */
void *removeLast(LIST *lp) {
	assert(lp->count>0);

	NODE *lastNode = lp->head->prev;
	void *lastData = lastNode->data;

	lastNode->prev->next = lp->head;	//The list is circularly linked, so the last node points to head
	lp->head->prev = lastNode->prev;

	free(lastNode);

	lp->count--;

	return lastData;
}

/*
 * Returns the first element in the list.
 * Runtime: O(1)
 */
void *getFirst(LIST *lp) {
	assert(lp->count>0);
	return lp->head->next->data;
}

/*
 * Returns the last element, taking advantage of the "prev" pointer
 * Runtime: O(1)
 */
void *getLast(LIST *lp) {
	assert(lp->count>0);
	return lp->head->prev->data;
}

/*
 * Traverses the list through a for loop to locate a node with the given value. It uses the compare function to ascertain
 * whther the value is found. If found, it removes the node, patching up the list accordingly. Its previous element points to 
 * its next element, and vice versa. The node's memory is freed, and the list's length is decremented.
 * Runtime: O(n)
 */
void removeItem(LIST *lp, void *item) {
	assert( lp->count>0 && item!=NULL && lp->compare!=NULL);

	int i;
	NODE *curr = lp->head->next; 	//points to the current node to traverse
	for(i=0; i<lp->count; i++) {
		if (lp->compare(curr->data,item)==0){
			curr->prev->next = curr->next;			//Before removal, pointers are updated appropriately
			curr->next->prev = curr->prev;

			free(curr);
			lp->count--;
			break;		//Element is removed; we don't need to traverse the list anymore
		} else curr = curr->next;	//Current node updated to the next node
	}
}

/*
 * Finds an node with the given value, traversing the list with a for loop. If a node with the value is found, we return the value.
 * At the end, if it has never seen the value. it returns NULL.
 * Runtime: O(n)
 */
void *findItem(LIST *lp, void *item) {
	assert(lp->compare!=NULL && item!=NULL);

	int i;
	NODE *curr = lp->head->next;					//Points to the current element
	for(i=0; i<lp->count; i++) {
		if(lp->compare(curr->data, item)==0) {			//When the node's value matches the given value, return it.
			return curr->data;
		}
		curr = curr->next;							//Otherwise, keep traversing
	}
	return NULL;
}
/*
 * Returns an array of void elements that stores the value in the list in order. A while loop traverses the 
 * list, and within it, the values are inserted into the array.
 * Runtime: O(n)
 */
void *getItems(LIST *lp) {
	void **arr;
	arr = malloc(sizeof(void*)*lp->count);
	assert(arr!=NULL);

	int index = 0;	//index for the array
	NODE *curr = lp->head->next;		//Points to the current node
	while(curr!=NULL){
		arr[index] = curr->data;
		++index;
		curr = curr->next;		//Node is updated to the next node
	}
	return arr;
}