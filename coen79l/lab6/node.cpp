// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include <iostream>
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <unordered_set>
#include "node.h"

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
		node* tmp = head_ptr;		
    	head_ptr = new node(entry, head_ptr);
		head_ptr->set_link(tmp);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
    {
        // cerr << "You have not implemented list_piece." << endl;
        head_ptr = NULL;
        tail_ptr = NULL;

        // Handle the case of the empty list.
        if (start_ptr == NULL)
            return;

        // Make the head node for the newly created list, and put data in it.
        list_head_insert(head_ptr, start_ptr->data( ));
        tail_ptr = head_ptr;

        // Copy the rest of the nodes one at a time, adding at the tail of new list.
        start_ptr = start_ptr->link( );
        while (start_ptr != end_ptr)
        {
            list_insert(tail_ptr, start_ptr->data( ));
            tail_ptr = tail_ptr->link( );
            start_ptr = start_ptr->link( );
        }
    }

    size_t list_occurrences(node* head_ptr, const node::value_type& target)
    {
        // cerr << "You have not implemented list_occurrences." << endl;
        size_t count = 0;
        while (head_ptr!=NULL) {
            if (head_ptr->data()==target) {
                count++;
            }
            head_ptr = head_ptr->link();
        }
        return count;;
    }

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
    {
        // cerr << "You have not implemented list_insert_at." << endl;
        assert(position > 0 && position <= list_length(head_ptr));
        if (position == 1) {
            list_head_insert(head_ptr,entry);
        } else {
            node* prev = head_ptr;
            for (int i = 1; i < position - 1; ++i) {
                prev = prev->link();
            }
            list_insert(prev,entry);
        }
    }

    node::value_type list_remove_at(node*& head_ptr, size_t position)
    {
        // cerr << "You have not implemented list_remove_at." << endl;
        assert(position > 0 && position <= list_length(head_ptr));
        node::value_type theData = 0.0;

        if (position == 1) {
            list_head_remove(head_ptr);
        } else {
            node* prev = head_ptr;
            for (int i = 1; i < position - 1; ++i) {
                prev = prev->link();
            }
            theData = prev->link()->data();
            list_remove(prev);
        }

        return theData;
    }

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
    {
        // cerr << "You have not implemented list_copy_segment." << endl;
        node* dest_head_ptr = NULL;
        if (head_ptr == NULL) {
            return dest_head_ptr;
        }

        for (int i = 1; i < start; ++i) {
            dest_head_ptr = dest_head_ptr->link();
        }

        list_head_insert(dest_head_ptr,head_ptr->data());
        node* dest_tail_ptr = dest_head_ptr;
        size_t iterations = finish - start;

        while(iterations!=0) {
            list_insert(dest_head_ptr, head_ptr->data( ));
            dest_tail_ptr = dest_tail_ptr->link();
            head_ptr = head_ptr->link();
            --iterations;
        }

        return dest_head_ptr;
    }

	void list_print (const node* head_ptr){
		const node *curr = head_ptr;
		while(curr!=NULL){
			std::cout<< " " << curr->data();
			if((*curr).link()!=NULL) {
				std::cout<<",";
			}else std::cout<<"\n";
			curr=curr->link();
		}
	}

    void list_remove_dups(node* head_ptr){
		std::unordered_set<int> s;
		while(head_ptr!=NULL){
			if(s.find(head_ptr->data())!=s.end()){
				list_remove(head_ptr);
			}else s.insert(head_ptr->data());
			head_ptr=head_ptr->link();
		}
	}

    node* list_detect_loop (node* head_ptr){
		node *curr = head_ptr;
		unordered_set<node*> set;

		while(curr){
			if(set.find(curr)!=set.end()) return curr;

			set.insert(curr);
			curr = curr->link();
		}
		return NULL;

	}
    
}
