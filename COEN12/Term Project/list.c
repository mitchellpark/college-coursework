/*
 * Author: Mitchell Park
 * Assignment: Term Project
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

/* 
 * Node has pointers to the next and previous nodes because the list
 * is doubly linked. 
 */
typedef struct node {
	void **data;
	int first;      //keeps track of the first slot
	int length;     //capacity of data array
	int count;    //number of elements
	struct node *next;
	struct node *prev;
}NODE;

/* The list has both head and tail pointers. */
typedef struct list {
	int count;
	NODE* head;
	NODE* tail;
}LIST;

NODE *createNode(int length);

/*
 * Allocates memory and initializes variables for a list, and returns it.
 * Head and tail pointers are initialized with arrays of size 10.
 * Runtime: O(1)
 */
LIST *createList(void) {
	LIST *lp = malloc(sizeof(LIST));
    assert(lp!=NULL);

	lp->head = lp->tail = createNode(10);
	lp->count = 0;

	return lp;
}

/* 
 * Traverses all data of all the nodes, the nodes themselves,
 * and finally, the list.
 * Runtime: O(n), where n is the number of elements in the list.
 */
void destroyList(LIST *lp) {
	assert(lp != NULL);
	NODE* curr = lp->head;
    NODE* toDel;
	while(curr!= NULL) {
        toDel = curr;
        curr = curr->next;
		free(toDel->data);
        free(toDel);
	}
	free(lp);
}

/* 
 * Returns the number of items in the list. 
 * Runtime: O(1)
 */
int numItems(LIST *lp) {
	assert(lp != NULL);
	return lp->count;
}

/* 
 * Using createNode, a node is added to the beginning of the list.
 * If the head node's array is full, a new node with an empty array is created to insert the value.
 * Runtime: O(1)
 */
void addFirst(LIST *lp, void *item) {
	assert(lp != NULL && item != NULL);

	if(lp->head->count==lp->head->length) {         //If the array is full, a new node is created.
		NODE *firstNode = createNode(lp->head->length*2);
		firstNode->next = lp->head;
		lp->head = firstNode;
		firstNode->next->prev = firstNode;
	}
	
	int index = (lp->head->first + lp->head->length-1) % lp->head->length;      //generated index of first slot
	lp->head->data[index] = item;
	lp->head->first = index;
	lp->head->count++;
	lp->count++;
}

/*
 * Using createdNode(), a node is added to the last index of the list.
 * If the tail opint's array is full, then we create a new node with an empty array to insert the value.
 * Runtime: O(1)
 */
void addLast(LIST *lp, void *item) {
	assert(lp != NULL &&  item != NULL);

	if(lp->tail->count == lp->tail->length) {       //If the array  is full, a new node with empty array is created.
		NODE* lastNode = createNode(lp->tail->length*2);
		lastNode->prev = lp->tail;
		lp->tail->next = lastNode;
		lp->tail = lastNode;
	}

	int index = (lp->tail->first+lp->tail->count)%lp->tail->length;     //last index of array
	lp->tail->data[index] = item;
	lp->tail->count++;
	lp->count++;
}

/*
 * If the head node is empty, we free the node frmo memory and set the node after it as the new head node.
 * If it is not empty, the first node is still removed, and the data is returned.
 * Runtime: O(1)
 */
void *removeFirst(LIST *lp) {
	assert(lp != NULL);

	if(lp->head->count==0) {		//If the head node is empty, we delete it and patch the removal
		lp->head = lp->head->next;
		free(lp->head->prev);
		lp->head->prev = NULL;
	}

	void *delVal = lp->head->data[lp->head->first];     //value of the deleted item to be returned
	lp->head->first = (lp->head->first+1)%lp->head->length;     //new index for first slot
	lp->head->count--;
	lp->count--;

	return delVal;
}
/*
 * If the tail node is empty, we delete the node and set its prev node as the new tail node. Otherwise, the last node is removed.
 * Runtime: O(n), where n is the number of elements in the list.
 */
void *removeLast(LIST *lp) {
	assert(lp != NULL);

	if(lp->tail->count==0) {	//If the tail has no elements, we delete it and patch the removed spot.
		NODE* toDel = lp->tail;
		lp->tail = lp->tail->prev;
		lp->tail->next = NULL;
		free(toDel->data);
		free(toDel);
	}

	int index = ((lp->tail->first + lp->tail->count)%lp->tail->length);     //index of the last item

	lp->tail->count--;
	lp->count--;

	return lp->tail->data[index];
}

/*
 * Given an index parameter, this function returns the data of the node at that index.
 * Rutnime: O(n), where n is the number of elements in the list.
 */
void *getItem(LIST *lp, int index) {
	assert(lp != NULL && index >= 0 && index < lp->count);      //Checking if given index is valid

	NODE* curr = lp->head;

	while(index >= curr->count) {		//Subtract from the index until we find a node's counter that is larger than it
		index -= curr->count;
		curr = curr->next;
	}

	void* item = curr->data[(curr->first+index)%curr->length];
	return item;
}

/*
 * Like getItem, it receives an index to locate, and gets the node at that index. Here, the node's
 * data is changed to the given data.
 * Runtime: O(n), where n is the number of elements in the list.
 */
void setItem(LIST *lp, int index, void *item) {
	assert(lp != NULL && item != NULL);
	assert(index >= 0 && index < lp->count);        //index must be valid

	NODE* curr =  lp->head;

	while(index >= curr->count) {		//Decrementing while traversing until we are at the right node
		index -= curr->count;
		curr = curr->next;
	}

    /* The node's data is now updated */
	int i = (curr->first+index)%curr->length;
	curr->data[i] = item;
}

/*
 * Creates a new node with an empty array, and null prev and next pointers.
 * Runtime: O(1)
 */
NODE *createNode(int size) {
	NODE *np = malloc(sizeof(NODE));
	assert(np != NULL);

	np->data = malloc(sizeof(void**)*size);
	np->count = 0;
	np->first = 0;
	np->length = size;
	np->next = NULL;
	np->prev = NULL;
	return np;
}