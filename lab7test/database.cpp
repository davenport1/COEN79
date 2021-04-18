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

#ifdef USEDEBUG
#define Debug(x) std::cout << x
#else
#define Debug(x)
#endif

namespace coen79_lab7
{

    database::database(const size_type &initial_capacity)
    {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }

    database::database(const database &src)
    {
        Debug("Copy constructor..." << std::endl);
        used_slots = 0;
        reserve(src.aloc_slots);
        for (int i = 0; i < src.used_slots; ++i)
        {
            this->company_array[i] = src.company_array[i]; 
            ++used_slots;
        }
    }

    database &database::operator=(const database &rhs)
    {
        Debug("Assignment operator..." << std::endl);
        if (this == &rhs)
        {
            return *this; //self assignment check
        }
        delete[] company_array;
        company_array = new company[rhs.aloc_slots];
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
        std::cout << "copying elements of database...";
        return *this;
        // COMPLETE THE IMPLEMENTATION...//do this third
    }

    database::~database()
    {
        // COMPLETE THE IMPLEMENTATION...
        delete[] company_array;
        used_slots = 0;
        aloc_slots = 0;
    }

    void database::reserve(size_type new_capacity)
    {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.

        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.

        // COMPLETE THE IMPLEMENTATION...

        company *larger_array = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, larger_array);
        delete[] company_array;
        company_array = larger_array;
        aloc_slots = new_capacity;
    }

    bool database::insert_company(const std::string &entry)
    {
        //      Precondition: company_name is a non-empty string
        //      Postcondition: A new Company is added to the list

        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);

        size_type pos = search_company(entry);

        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND)
        {
            return false;
        }

        // COMPLETE THE IMPLEMENTATION...
        //reserve needed
        if (used_slots == aloc_slots)
            reserve(aloc_slots + 1);
        company new_company = company(entry);
        company_array[used_slots++] = new_company;
        return true;
    }

    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price)
    {
        Debug("Insert item..." << std::endl);
        //      Precondition: company_name and product_name are non-empty strings
        //      Postcondition: A new product is added to the list pertaining to the company
        //      This function also checks to see if the company is already in the database.
        //      Returns false if the compnay is already in the database, otherwise returns true.

        assert(company.length() > 0 && product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        size_type position = search_company(company); // Check if the company exists
        if (position == COMPANY_NOT_FOUND)
            return false;
        else
        {
            company_array[position].insert(product_name, price); // Insert product and price into last item of company
            return true;
        }
    }

    bool database::erase_company(const std::string &company)
    {

        size_type company_index = search_company(company);

        // COMPLETE THE IMPLEMENTATION...
        //      Precondition: company_name is a non-empty string
        //      Postcondition:  A company (as well as all its products) are removed from the database.  All elements to
        //      the right of the company are shifted to the left.
        //      Returns false if the company was not found in the list.
        if (company_index == COMPANY_NOT_FOUND)
            return false;
        for (size_type i = company_index; i < used_slots - 1; i++)
            company_array[i] = company_array[i + 1];
        used_slots--;
        return true;
        //
    }

    bool database::erase_item(const std::string &cName, const std::string &pName)
    {

        assert(cName.length() > 0 && pName.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        //  bool erase_item(const std::string &company_name, const std::string& product_name)
        //      Precondition: company_name and product_name are non-empty strings
        //      Postcondition:  A product is erased from the company in the database.  Returns false if
        //      the company or the item was not found.
        //
        assert(cName.length() > 0 && pName.length() > 0);
        size_type index = search_company(cName);
        if (index == COMPANY_NOT_FOUND) // Check if the company exists
            return false;
        return company_array[index].erase(pName);
    }

    database::size_type database::search_company(const std::string &company)
    {
        assert(company.length() > 0);

        // COMPLETE THE IMPLEMENTATION...start with this
        //      Precondition: company is a non-empty string
        //      Postcondition:  Searches the DB for the company of the specified name.  Returns the position if found, but if
        //      not found, returns COMPANY_NOT_FOUND.
        assert(company.length() > 0);
        for (size_type i = 0; i < used_slots; i++)
            if (company_array[i].get_name() == company)
                return i;
        return COMPANY_NOT_FOUND;
    }

    bool database::print_items_by_company(const std::string &cName)
    {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);

        if (c_index == COMPANY_NOT_FOUND)
        {
            return false;
        }

        std::cout << "Printing the products of " << cName << ":" << std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;

        return true;
    }

    void database::print_companies()
    {

        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++)
        {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif