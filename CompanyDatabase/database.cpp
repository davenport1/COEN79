// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifndef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        used_slots = 0;
        reserve(src.aloc_slots);
        for(int i = 0; i < src.used_slots; ++i) {
            this->company_array[i] = src.company_array[i];          //copy over elements of src.
            ++used_slots;
        }
    }
    
    
    database& database::operator= (const database &rhs) {
        //Debug("Assignment operator..." << std::endl);
        std::cout << "copying elements of database...";
        delete [] company_array;    //handle previously filled company array
        used_slots = 0;
        reserve(rhs.aloc_slots);
        for(int i = 0; i < rhs.used_slots; ++i) {
            this->company_array[i] = rhs.company_array[i];          //copy over elements of src.
            ++used_slots;
        }
        return *this;
    }
    
    
    database::~database() {
        delete [] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        //Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Can't allocate less than we are using.
        
        aloc_slots = new_capacity;                                  //set new capacity
        company* new_company_array = new company[aloc_slots];       //create temp array to copy oover

        for(int i = 0; i < used_slots; ++i) {
            new_company_array[i] = this->company_array[i];          //copy over to newly sized array
        }
        delete [] company_array;                                    //free heap mem
        company_array = new_company_array;                          //set array equal to newly sized array
        
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        //Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        company* new_company = new company(entry);
        if(used_slots == aloc_slots) 
            reserve(aloc_slots + 1);
        company_array[used_slots] = *new_company;
        ++used_slots;
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        //Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        database::size_type pos = search_company(company);
        if(pos == COMPANY_NOT_FOUND)                                    //check company exists in database
            return false;

        company_array[pos].insert(product_name, price);                 //insert into company
        return true;
    }
    
    
    bool database::erase_company(const std::string &company_name) {
        
        size_type company_index = search_company(company_name);
        if(company_index == COMPANY_NOT_FOUND)  {                        //company does not exist in database
            return false;              
        }
        company_array[company_index] = company_array[used_slots - 1];   //take last element and have it take the place of desired company to erase
        --used_slots;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        //Debug("Erase item..." << std::endl);
        assert(cName.length() > 0 && pName.length() > 0);
        size_type company_index = search_company(cName);
        if(company_index == COMPANY_NOT_FOUND)  {                        //company does not exist in database
            return false; 
            std::cout << "Item was not found" << std::endl;             
        }
        return(company_array[company_index].erase(pName));              //return result of erasure of the product
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
        for(int i = 0; i < used_slots; ++i) {
            if(company_array[i].get_name() == company)
                return i;
        }
        return COMPANY_NOT_FOUND;
        
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
