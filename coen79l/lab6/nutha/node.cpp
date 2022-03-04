#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <stdio.h>
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    /* returns the size of the list. */
    size_t list_length(const node* head_ptr){
        const node *curr;
        size_t answer = 0;

        for(curr=head_ptr;  curr!= NULL; curr = curr->link()) {
            ++answer;
        }
	    return answer;
    }

    /* Inserts an element at the head.*/
    void list_head_insert(node*& head_ptr, const node::value_type& entry){
    	head_ptr = new node(entry, head_ptr);
    }

    /*Inserts an element at the tail.*/
    void list_insert(node* previous_ptr, const node::value_type& entry){
    	node *insert;

    	insert = new node(entry, previous_ptr->link());
    	previous_ptr->set_link(insert);
    }

    /*Searches the list for a target value. If found, we return the node.*/
    node* list_search(node* head_ptr, const node::value_type& target){
    	node *curr;

    	for (curr=head_ptr; curr!=NULL; curr=curr->link()){
    	    if(target==curr->data()) return curr;
        }

    	return NULL;
    }

    /*A const version of the function above.*/
    const node* list_search(const node* head_ptr, const node::value_type& target){
    	const node *curr;

    	for (curr=head_ptr;  curr!=NULL; curr=curr->link( ))
    	    if(target==curr->data()){
        		return curr;
            }

    	return NULL;
    }

    /* 
     * The pointer returned points to the node at the specified
     * position in the list. 
     */
    node* list_locate(node* head_ptr, size_t position){
    	assert (0 < position);

    	node *curr;
    	curr = head_ptr;
    	for(int i=1; (i<position) && (curr!= NULL); i++){
            curr = curr->link();
        }
    	return curr;
    }

    /* Const version of the function above.*/
    const node* list_locate(const node* head_ptr, size_t position){
    	assert (0 < position);

    	const node *curr;
    	curr = head_ptr;

    	for(int i=1; (i<position) && (curr!= NULL); i++)
    	    curr=curr->link();

    	return curr;
    }

    /* Removes the head node.*/
    void list_head_remove(node*& head_ptr)
    {
    	node *remove;

    	remove = head_ptr;
    	head_ptr=head_ptr->link( );
    	delete remove;
    }

    /* Removes the tail node from the list.*/
    void list_remove(node* previous_ptr)
    {
    	node *remove;

    	remove=previous_ptr->link();
    	previous_ptr->set_link(remove->link());
    	delete remove;
    }

    /*Removes all elements.*/
    void list_clear(node*& head_ptr){
    	while (head_ptr != NULL){
    	    list_head_remove(head_ptr);
        }
    }
    /* 
     * head_ptr and tail_ptr are the head and tail pointers for
     * a new list that contains the same items as the list pointed to by
     * source_ptr. 
     */
    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;


    	if(!source_ptr)return;

    	list_head_insert(head_ptr, source_ptr->data());
    	tail_ptr = head_ptr;

    	source_ptr = source_ptr->link();
    	while(source_ptr!= NULL){
    	    list_insert(tail_ptr, source_ptr->data());
    	    tail_ptr = tail_ptr->link();
    	    source_ptr = source_ptr->link();
    	}
        //And the original list is unaltered.
    }

    /* 
     * head_ptr and tail_ptr are the head and tail pointers for a
     * new list that contains the items from start_ptr up to but not including
     * end_ptr.
     */
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
    {
        if ((start_ptr==end_ptr) || (start_ptr == NULL)) return;
        
        head_ptr = NULL;
        list_head_insert(head_ptr, start_ptr -> data());
        tail_ptr = head_ptr;
        
        //The end_ptr may also be NULL, in which case the new list
        //contains elements from start_ptr to the end of the list.
        while (start_ptr!=NULL && start_ptr->link() != end_ptr){
            start_ptr=start_ptr->link();
            list_insert(tail_ptr,start_ptr->data());
            tail_ptr=tail_ptr->link();
        }
    }

    /* 
     * The return value is the count of the number of times
     * target appears as the data portion of a node on the linked list.
     */
    size_t list_occurrences(node* head_ptr, const node::value_type& target)
    {
        node* curr;
        size_t count = 0;
        
        if (head_ptr == NULL) return count;
        
        //The linked list remains unchanged.
        for(curr=head_ptr; curr!=NULL; curr=curr->link()){

            if(curr->data()==target) count++;
        }

        return count;
    }

    /*
     *  new node has been added to the linked list with entry
     *  as the data.
     */
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
    {
        assert((position>0)&&(position <= list_length(head_ptr)+1));
        
        /* nodes that used to be after this specified position have been
             shifted to make room for the one new node.*/
        if (position==1){
            list_head_insert(head_ptr, entry);
        }else if(position==list_length(head_ptr)+1){
            list_insert(list_locate(head_ptr, list_length(head_ptr)), entry);
        }else{
            list_insert(list_locate(head_ptr, position-1), entry);
        }
    }

    /* 
     * The node at the specified position is removed from
     * the linked list and the function has returned a copy of the data from
     * the removed node.
     */
    node::value_type list_remove_at(node*& head_ptr, size_t position)
    {
        assert((position>0)&&(position <= list_length(head_ptr)+1));
        
        if (position==1){
            list_head_remove(head_ptr);
            return head_ptr->data();
        }else{
            list_remove(list_locate(head_ptr, position-1));
            return head_ptr->data();
        }
    }

    /*
     * The value returned is the head pointer for
     * a new list that contains copies of the items from the start position to
     * the finish position.
     */
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
    {
        assert((1<=start) && (start<=finish) && (finish<=list_length(head_ptr)));
        
        if(!head_ptr) return NULL;

        node* head = NULL;
        node* tail = NULL;
        list_piece(list_locate(head_ptr, start),list_locate(head_ptr,finish+1), head, tail);

        return head;
    }

    /* Prints values of the list in an orderly format.*/
    void list_print (const node* head_ptr){   
        //If there are no nodes, return with a blank line.
        if(!head_ptr) {
            std::cout << endl;
            return;
        }

        while(head_ptr != NULL){
            //If there it is the last element, we don't put a comma.
            if(head_ptr->link() == NULL){
                std::cout << head_ptr->data();
            }else{
                std::cout<<head_ptr->data() << ", ";
            }
            head_ptr=head_ptr->link();
        }
            
        std::cout << endl;
        return;
    }

    /* Scans the list and removes any nodes with duplicate values.*/
    void list_remove_dups(node* head_ptr){
        node* n1;
        node* n2;
        n1 = head_ptr;
        while(n1!=NULL&&n1->link()!=NULL){
            n2 = n1;
            while(n2->link()!=NULL){
                if(n1->data()==n2->link()->data()){
                    list_remove(n2);
                }else  n2=n2->link();
            }
        }
        n1=n1->link();
    }

    /* Returns true if there is a cycle in the list.*/
    node* list_detect_loop (node* head_ptr){
        if (head_ptr == NULL) return NULL;
        
        node* n1;
        node* n2;
        n1 = head_ptr;
        n2 = head_ptr;
        while( (n1->link() != NULL) && (n1 != NULL)){
            n2 = n2->link();
            n1 = n1->link()->link();

            if(n2 == n1) break;
        }

        if((n1 == NULL)|| (n1->link()==NULL)) return NULL;

        n2 = head_ptr;
        while(n2 != n1){
            n2 = n2->link();
            n1 = n1->link();
        }
        return n2;
    }
}