#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4
{

    keyed_bag::keyed_bag()
    {
        int i;
        for (i = 0; i < CAPACITY; i++)
        {
            keys[i] = '\0';
            data[i] = '\0';
        }
        used = 0;
    }
    void keyed_bag::erase()
    {
        int i;
        for (i = 0; i < used; i++)
        {
            keys[i] = '\0';
            data[i] = '\0';
        }
        used = 0;
    }

    bool keyed_bag::erase(const key_type &key)
    {
        assert(used > 0);
        int i;
        int j;
        for (i = 0; i < used; ++i)
        {
            if (keys[i] == key)
            {
                for (j = i; j < used - 1; ++j)
                {
                    keys[j] = keys[j + 1];
                    data[j] = data[j + 1];
                }
                used--;
                return true;
            }
        }
        return false;
    }
    void keyed_bag::insert(const value_type &entry, const key_type &key)
    {
        assert((size() < CAPACITY) && (has_key(key) == false));
        keys[used] = key;   
        data[used] = entry; 
        used++;      
    }
    void keyed_bag::operator+=(const keyed_bag &addend)
    {
        assert(size() + addend.size() <= CAPACITY);
        int i;
        for (i = 0; i < addend.used; ++i)
        {
            if (!has_key(addend.keys[i]))
            {                         
                keys[used] = addend.keys[i]; 
                data[used] = addend.data[i];
                used++;
            }
        }
    }
    bool keyed_bag::has_key(const key_type &key) const
    {
        int i;
        for (i = 0; i < used; ++i)
        {
            if (keys[i] == key)
            {
                return true; 
            }
        }
        return false; 
    }
    keyed_bag::value_type keyed_bag::get(const key_type &key) const
    {
        assert(has_key(key));
        int i;
        for (i = 0; i < used; ++i)
        {
            if (keys[i] == key)
            { //see if has key
                return data[i];
            }
        }
        //return NULL;
    }

    keyed_bag::size_type keyed_bag::size() const
    {
        return used;
    }
    keyed_bag::size_type keyed_bag::count(const value_type &target) const
    {
        size_type count = 0;
        int i;
        for (i = 0; i < used; ++i)
        {
            if (data[i] == target)
            { 
                count++;
            }
        }
        return count;
    }
    bool keyed_bag::hasDuplicateKey(const keyed_bag &otherBag) const
    {
        int i;
        for (i = 0; i < otherBag.used; ++i)
        {
            if (has_key(otherBag.keys[i]))
            {
                return true; 
            }
        }
        return false;
    }

    keyed_bag operator+(const keyed_bag &b1, const keyed_bag &b2)
    {
        assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
        keyed_bag result; 
        result += b1;
        result += b2;

        return result;
    }
} // namespace coen79_lab4
