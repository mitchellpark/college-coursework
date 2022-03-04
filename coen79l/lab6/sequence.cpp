//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    sequence::~sequence() {
        list_clear(head_ptr);
        many_nodes = 0;
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    void sequence::start() {
    precursor = NULL;
    cursor = head_ptr;
  }

  void sequence::end() {
    precursor = list_locate(head_ptr,many_nodes-1);
    cursor = precursor->link();
    tail_ptr = cursor;
  }

  void sequence::advance() {
    assert(is_item());
    cursor = cursor->link();
    if (precursor == NULL) {
      precursor = head_ptr;
    } else {
    precursor = precursor->link();
    }
  }

  void sequence::insert(const value_type& entry) {
    if (many_nodes == 0 || many_nodes == 1) {
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
      tail_ptr = cursor;
    } else if (precursor==NULL){
      // precursor = head_ptr;
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor=NULL;
    } else {
      list_insert(precursor, entry);
      cursor = precursor->link();
    }
    many_nodes++;
  }

  void sequence::attach(const value_type& entry) {
    if (head_ptr == NULL) {
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
      tail_ptr = head_ptr;
    } else if (precursor==NULL) {
      list_insert(cursor, entry);
      precursor = head_ptr;
      cursor = precursor->link();
      tail_ptr = cursor;
    } else {
      list_insert(cursor, entry);
      precursor = precursor->link();
      cursor = precursor->link();
      if (cursor->link()==NULL) {
        tail_ptr = cursor;
      }
    }
    many_nodes++;
  }

  void sequence::operator =(const sequence& source) {
    if (this == &source)
      return;
    list_clear(head_ptr);
    many_nodes = 0;
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    many_nodes = source.size();
  }

  void sequence::remove_current() {
    assert(is_item());
    if (many_nodes == 0)
      return;
    if (precursor == NULL) {
      list_head_remove(head_ptr);
    } else {
      node* ptr_to_remove = cursor;
      precursor->set_link(cursor->link());
      delete ptr_to_remove;
      cursor = precursor->link();
    }
  }

  sequence::size_type sequence::size() const {
    return many_nodes;
  }

  bool sequence::is_item() const {
    if (cursor!=NULL) {
      return true;
    }
    return false;
  }

  sequence::value_type sequence::current() const {
    assert(is_item());
    return cursor->data();
  } 
    
}
