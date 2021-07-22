/*
 * Author: Mitchell Park
 * File that tests Huffman encoding, with the help of pack.c.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;

/* Helper functions that were suggested in the preview video */
int nodecmp(NODE* left, NODE* right);
NODE* mknode(int data, NODE* left, NODE* right);
int getDepth( NODE* child);

int main(int argc, char* argv[]) {
	int counts[257];

	/* All nodes in the node array are initialized with 0. */
	NODE* nodes[257];		
	int a;
	for(a=0; a<257;a++){
		counts[a] = 0;
	}

	/* Tries to open the file. Returns an error message if it cannot; otherwise,
		it populates the counts array with the characters it reads in */
	FILE* fp = fopen(argv[1],"r");
	if(fp==NULL){
		printf("Cannot open file.\n");
		return -1;
	}
	int c;
	while((c=getc(fp)) != EOF){
		counts[c]++;
	}
	fclose(fp);

	PQ *pq = createQueue(nodecmp);		//Instantiating a pqueue
	
	int i;
	for(i=0; i<256; i++){		//The elements of counts are inserted into the tree.
		if(counts[i] > 0) {
			nodes[i] = mknode(counts[i], NULL, NULL);
			addEntry(pq, nodes[i]);
		}
		else nodes[i] = NULL;
	}
	nodes[256] = mknode(0, NULL, NULL);		//tree to act as an EOF marker
	addEntry(pq, nodes[256]);
	
	int sum;
	/* We add the values of the two lowest priority trees for the value for one new tree 
     * that will be inserted back into the priority queue. Eventually, we will end up with one big tree. */
	while(numEntries(pq)>1){
		NODE *first = removeEntry(pq);
		NODE *second = removeEntry(pq);
		sum = first->count+second->count;
		NODE *third = mknode(sum, first, second);
		addEntry(pq, third);
	}

	//Printing out the number of bits.
	int b, depth, times;
	for(b=0; b<257; b++){
		if(nodes[b]!=NULL){
			depth = getDepth(nodes[b]);
			times = counts[b]*depth;

			if(isprint(b)==0){
				printf("%o", b);
			}else{
				printf("'%c'", b);
			}
			printf(": %d x %d bits = %d bits\n", counts[b], depth, times);
		} 
	}

	pack(argv[1], argv[2], nodes);

	return 0;
}

/*
 * Comapres the two given nodes, returning -1 if the left node is greater
 * than the right, 1 if vice versa, and 0 if they are equal.
 * Runtime: O(1)
 */
int nodecmp(NODE* left, NODE* right){
	if(left->count < right->count) 	return -1;
	if(left->count > right->count) 	return 1;
	return 0;	
}

/*
 * Creates a new node with the given data. It is then set as the parent of the given
 * left and right nodes.
 * Runtime: O(1)
 */
NODE* mknode(int data, NODE* left, NODE* right) {
	NODE* newNode = malloc(sizeof(NODE*));	
	assert(newNode!=NULL);

	newNode->parent = NULL;
	newNode->count = data;

	if(left!=NULL && right!=NULL) {
		left->parent = newNode;
		right->parent = newNode;
	}
	return newNode;	
}

/*
 * Returns the depth of the given node, using recursion
 * Runtime: O(1)
 * */
int getDepth(NODE* child) { 
	if(child->parent==NULL){
		return 0;
	}
	return getDepth(child->parent)+1;
}