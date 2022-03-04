#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function
namespace coen79_lab6
{
    void sequence::init(){
        //All pointers set to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;

        many_nodes = 0;
    }
    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence::sequence (){
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source){
        init();
        *this = source;
    }
    
    //Destructor: we empty all of our variables.
    sequence::~sequence(){
        list_clear(head_ptr);
        cursor = NULL;
        precursor = NULL;
        tail_ptr = NULL;
        head_ptr = NULL;
        many_nodes = 0;
    }
    
    /* The cursor is set to first node.*/
    void sequence::start( ){
        cursor=head_ptr;
        precursor = NULL;
    }

    /* The cursor is set to the end node.*/
    void sequence::end(){
        if(head_ptr==NULL && tail_ptr==NULL)return;

        cursor = tail_ptr;
        if(head_ptr==tail_ptr){
            precursor = NULL;
        }else{
            precursor = list_locate(head_ptr, many_nodes-1);
        }
    }
    /*Moves the precursor and cursor up an index.*/
    void sequence::advance( ){
        assert(is_item());
        precursor=cursor;
        cursor=cursor->link();
    }
    
    /* Inserts a node with the specified entry in the back.*/
    void sequence::insert(const value_type& entry){
        if (precursor==NULL||is_item()==false){
            list_head_insert(head_ptr, entry);
            many_nodes++;
            cursor=head_ptr;
            precursor = NULL;

            if(tail_ptr==NULL){
                tail_ptr = head_ptr;
            }
            return;
        }
        list_insert(precursor, entry);
        cursor = precursor->link();
        many_nodes++;
    }
    /**/
    void sequence::attach(const value_type& entry){
        if (!is_item()){
            if (head_ptr == NULL && tail_ptr == NULL){
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
                tail_ptr = head_ptr;
                many_nodes++;
                return;
            }
            else{
                list_insert(precursor,entry);
                cursor = precursor-> link();
                tail_ptr = tail_ptr-> link();
                many_nodes++;
                return;
            }
        }
        bool update(cursor == tail_ptr);
        precursor = cursor;
        list_insert(precursor,entry);
        cursor = cursor->link();
        if(update){
            tail_ptr = tail_ptr-> link();
        }
        many_nodes++;
    }
    
    /*Overloading the assignment operator.*/
    void sequence::operator =(const sequence& source){
        //Checking for self-assignment.
        if(this==&source) return;

        list_clear(head_ptr);
        cursor = NULL;
        precursor = NULL;
        head_ptr = NULL;
        tail_ptr = NULL;
        many_nodes = 0;
        if (source.cursor == NULL){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
        }else if(source.cursor==source.tail_ptr){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            end();
        }else if(source.cursor==source.head_ptr){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            start();
        }else{
            list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
            list_piece(source.cursor, NULL,cursor,tail_ptr);
            precursor->set_link(cursor);
        }
        many_nodes = source.many_nodes;
    }
    
    /*removes the node at the where the cursor is currently is.*/
    void sequence::remove_current( ){
        assert(is_item());
        if(cursor == head_ptr){
            if(head_ptr == tail_ptr){
                list_head_remove(head_ptr);
                cursor = NULL;
                precursor = NULL;
                tail_ptr = NULL;
                head_ptr = NULL;
            }else{
                list_head_remove(head_ptr);
                cursor = head_ptr;
                precursor = NULL;
            }
        }else if(cursor==tail_ptr){
            list_remove(precursor);
            tail_ptr = precursor;
            precursor = NULL;
            cursor = NULL;
        }else{
            list_remove(precursor);
            cursor = cursor->link();
        }
        many_nodes--;
    } 
    size_t sequence::size( )const{ return many_nodes;}
    
    bool sequence::is_item( )const{ return (cursor != NULL);}
    
    /* Returns the data held by the cursor.*/
    sequence::value_type sequence::current( ) const{
        assert(is_item());
        return cursor->data();
    }
}