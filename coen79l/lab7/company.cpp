
#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    /*by default, every field is empty*/
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    /* When company name is specified*/
    company::company(const std::string& company_name) {
        assert(company_name.length()>0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    /* copies company_name, and head_ptr to tail_ptr from one company to another*/
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        node* tail;
        list_copy(src.head_ptr, head_ptr, tail); 
        head_ptr = src.head_ptr;
        tail_ptr = tail;
        company_name = src.company_name;
    }

    
    /* overloading the assignment operator*/
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        //checking for self-assignment
        if(this==&src) return *this;

        list_copy(src.get_head(), head_ptr, tail_ptr); 
        company_name = src.company_name;
        return *this;
    }
    
    //Destructor
    company::~company() {
        list_clear(head_ptr);
    }
    
    /* return the name*/
    std::string company::get_name() const {
        return company_name;
    }
    
    /* (const function) return the head pointer*/
    const node *company::get_head() const {
        return head_ptr;
    }
    
    /* (const function) return the tail pointer*/
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    /* return the head pointer*/
    node* company::get_head() {
        return head_ptr;
    }
    
    /* return the tail pointer*/
    node* company::get_tail() {
        return tail_ptr;
    }
    
    /*prints the nodes*/
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    /*inserts a product as a node, with spe cified name and price*/
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        //If there is no head pointer, new node is created.
        if(head_ptr==NULL) {
            node* head = new node(product_name, price); 
            head_ptr = head;
            tail_ptr = head_ptr;
        }else{
            list_tail_insert(tail_ptr, product_name, price); 
        }
        
        return true;
    }

    /* Deletes a node with the specified product name. */
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        node *product = list_search(head_ptr, product_name); 

        //If product is not found
        if(product == NULL) return false;
        
        product->setName(head_ptr->getName());
        product->setPrice(head_ptr->getPrice());
        list_head_remove(head_ptr); 
        return true;
    }
    
    
}
