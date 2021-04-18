// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


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
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        this->company_name = src.company_name;                          //copy company name
        this->head_ptr = NULL;                                          //init both tail and head ptrs
        this->tail_ptr = NULL;        
        if(src.head_ptr == NULL)                                     //if src is empty, no need to copy
            return;
        list_copy(src.head_ptr, this->head_ptr, this->tail_ptr);        //copy over if src has a list
    }

    
    company& company::operator= (const company &src) {

        Debug("Company assignemnt operator..." << std::endl);
        if(head_ptr != NULL) 
            list_clear(head_ptr);                                       //handles previously initialized list
        this->company_name = src.company_name;                          //copy company name
        this->head_ptr = NULL;                                          //init both tail and head ptrs
        this->tail_ptr = NULL;        
        if(src.head_ptr == NULL)                                     //if src is empty, no need to copy
            return *this;
        list_copy(src.head_ptr, this->head_ptr, this->tail_ptr);         
        return *this;
    }
    
    
    company::~company() {
       list_clear(head_ptr);
        head_ptr = NULL;
        tail_ptr = NULL;
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            head_ptr = new node(product_name, price, NULL);
            tail_ptr = head_ptr;
        }
        else {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        if(head_ptr->getName() == product_name) {
            node* temp = head_ptr; 
            head_ptr = head_ptr->getLink();
            delete temp;
            return true;
        }
        for(node* cursor = head_ptr;  cursor->getLink() != NULL; cursor = cursor->getLink()) {
            if(cursor->getLink()->getName() == product_name) {
                node* temp = cursor->getLink();
                cursor->setLink(temp->getLink());
                delete temp;
                return true;
            }
        }
        return false;
    }
    
    
}
