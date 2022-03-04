#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    /*To initialize a database with an initial capacity. Everything else is empty by default.*/
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    /* Copies over all the data of a given database*/
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        aloc_slots = src.aloc_slots;
        used_slots = src.used_slots;
        company_array = new company[aloc_slots];
        *company_array = *src.company_array;
    }
    
    /* Overloading the assignment operator*/
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        //Checks for self-assignment
        if(this == &rhs) return *this;

        /*array is first deleted, and a new one is created to copy over the array of the given database*/
        delete [] company_array;
        company_array = new company[rhs.aloc_slots];
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array); 
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;

        std::cout<<"copying elements of database...";
        return *this; 
    }
    
    /*destructor*/
    database::~database() {
        delete [] company_array;
        aloc_slots=0;
        used_slots=0;
    }
    
    /*allocates memory with the given capacity*/
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        //not a new capacity specified
        if(new_capacity==aloc_slots) return; 
        
        //Can't allocate less data
        if(new_capacity<used_slots){
            new_capacity = used_slots; 
        }

        company* c = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, c); 
        delete[] company_array;
        company_array = c;
        aloc_slots = new_capacity;
        
    }
    
    /* Inserts company with the given name*/
    bool database::insert_company(const std::string &entry) {
        Debug("Insert company..." << std::endl);
        assert(entry.length() > 0);
        
        size_type index = search_company(entry);
        
        //Company with given name doesn't exist
        if(index!=COMPANY_NOT_FOUND) {
            return false;
        }else{
            reserve(aloc_slots+1);
            company_array[used_slots++] = company(entry);
            return true;
        }

    }
    
    /*Inserts a company with a product name and price.*/
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);
        // validating company length and product name's length 
        assert(company.length() > 0 && product_name.length() > 0);

        //If company is not found, we return false. Otherwise, it is inserted with insert().
        if(search_company(company) < 0){
            return false;
        }else{
            size_type index = search_company(company);
            company_array[index].insert(product_name, price); 
            return true;
        }
        
    }
    
    bool database::erase_company(const std::string &company) {
        size_type index = search_company(company);

        if(index == COMPANY_NOT_FOUND){
            return false;
        }else{
            for(int i=index+1; i < used_slots; i++){
                company_array[i-1]=company_array[i]; 
            }
            used_slots--;
            return true;
        }
        
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);
        size_type index = search_company(cName);
        
        if (index == COMPANY_NOT_FOUND){
            return false;
        }else{
            company_array[index].erase(pName); 
            return true;
        }
    }
    
    
    /*If company with given name is found, return the position. Otherwise, return COMPANY_NOT_FOUND*/
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
        size_t i;
        for(i=0; i<used_slots; i++){
            if(company == company_array[i].get_name()){
                return i;
                break;
            }
        }
        return COMPANY_NOT_FOUND;
    }
    
    /*Prints all the products of the company with the given name.*/
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length()>0);

        size_type index = search_company(cName);
        
        if(index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    /*Prints the names of all companies*/
    void database::print_companies() {
        std::cout << "Company List" << std::endl;
        size_t i;
        
        for(i=0; i<used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
