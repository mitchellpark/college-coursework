
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"
#include <cassert>

namespace coen79_lab7
{
    /*initializing a node with the given name, price and pointer to the next node.*/
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    /*modifies the name*/
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    /*modifies the price*/
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    /*modifies the next node*/
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    /*returns the next node*/
    node* node::getLink() {
        return link;
    }
    
    /*(const function) returns the next node*/
    const node* node::getLink() const {
        return link;
    }
    
    /*returns the name*/
    std::string node::getName() const{
        return name;
    }
    
    /*returns the price*/
    float node::getPrice() const {
        return price;
    }
    
    
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    /*Inserts a node at the tail*/
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {
        assert(newName.length() > 0);
        node* n = new node(newName, newPrice);
        tail->setLink(n); 
        tail = tail->getLink(); 
    }
    
    
    /*delets all nodes*/
    void list_clear(node*& head) {
        while (head != NULL){
            list_head_remove(head);
        }
    }
    
    /*Creates a new list, copying over a list, given a head pointer.*/
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;
        
        const node *curr = old_head;
        while(curr != NULL){
            //At first iteration, new node created as head. From then on, the we add to the tail.
            if(new_head==NULL){
                new_head = new node(curr->getName(), curr->getPrice());
                new_tail = new_head;
            }else{
                new_tail->setLink(new node(curr->getName(), curr->getPrice()));
                new_tail=new_tail->getLink();
            }
            curr=curr->getLink();
        }
    }
    
    /*Removes the head node*/
    void list_head_remove(node*& head) {
        node *n;
        
        n = head;
        head = head->getLink();
        delete n;
    }
    
    /*Iterates through the nodes, printing the name and price of the product*/
    void list_print(node *head) {
        node *cur = head;
        while(cur != NULL){
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    /*returns true if a product with the given name exists*/
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return list_search(head_ptr, newName) != NULL;
    }
    
    /*Iterates through the nodes, and returns the node with the given name.*/
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *curr;
        
        for(curr = head_ptr; curr != NULL; curr=curr->getLink()){
            if(curr->getName()==target){
                return curr;
            }
        }
        return NULL;
    }
    
    /*(const function) Iteratres through the nodes, andc retursn the node with the given name.*/
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *curr;
        
        for(curr = head_ptr; curr != NULL; curr=curr->getLink( )){
            if(curr->getName()==target){
                return curr;
            }
        }
        return NULL;
    }
    
}

#endif
