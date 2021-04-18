//ADVANCE WASS BROKEN
#include <iostream>
#include <algorithm>  
#include <cassert>    
#include "sequence.h" 
#include "node.h"     

using namespace std;

namespace coen79_lab6
{
    void sequence::init()
    {

        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
  
        many_nodes = 0;
    }


    sequence ::sequence()
    {
        init();
    }


    sequence::sequence(const sequence &source)
    {
        init();
        *this = source;
    }
    sequence::~sequence()
    {
        list_clear(head_ptr);
        init();
    }

    void sequence::start()
    {
        precursor = head_ptr;
        cursor = head_ptr;
        return;
    }

    void sequence::end()
    {
        cursor = tail_ptr;
        if (head_ptr == tail_ptr)
        {
            precursor = NULL;
        }
        else
        {
            precursor = head_ptr;
            while (precursor->link() != cursor)
            {
                precursor = precursor->link();
            }
        }
        return;
    }

    void sequence::advance()
    {
        assert(is_item());
        if(cursor ==tail_ptr){
            cursor = NULL;
            return;
        }
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const value_type &entry)
    {
        if (head_ptr == NULL)
        { 
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        else if (is_item() && cursor == head_ptr)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
        }
        else if (is_item() && cursor != head_ptr)
        { 
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
        else if (!is_item())
        { 
            list_head_insert(head_ptr, entry);
            tail_ptr = precursor->link();
            cursor = head_ptr;
            precursor = NULL;
        }
        many_nodes++;
        return;
    }

    void sequence::attach(const value_type &entry) 
    {
        if (head_ptr == NULL)
        { 
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
        }
        else if (is_item() && many_nodes == 1)
        { 
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            tail_ptr = precursor->link();
            cursor = tail_ptr;
        }
        else if (is_item() && many_nodes > 1 && cursor == head_ptr)
        { 
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            cursor = precursor->link();
        }
        else if (is_item() && cursor != head_ptr)
        { 
            if (cursor != tail_ptr)
            { 
                list_insert(cursor, entry);
                advance();
            }
            else
            { 
                list_insert(tail_ptr, entry);
                tail_ptr = cursor->link();
                precursor = cursor;
                cursor = tail_ptr;
            }
        }
        else if (!is_item() && many_nodes > 0)
        { 
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            cursor = precursor->link();
            tail_ptr = cursor;
        }
        many_nodes++;
        return;
    }

    void sequence::operator=(const sequence &source)
    {
        if (this == &source) 
            return;
        list_copy(source.head_ptr, head_ptr, tail_ptr); 
        many_nodes = source.many_nodes;                 
        start();                                        
        node *tmp = source.head_ptr;                   
        while (tmp != source.cursor)
        {                   
            advance();       
            tmp = tmp->link(); 
        }
    }

    void sequence::remove_current()
    {
        assert(is_item());
        if (head_ptr->link() == NULL)
        { 
            delete cursor;
            head_ptr = NULL;
            tail_ptr = NULL;
            precursor = NULL;
            cursor = NULL;
        }
        else if (cursor == head_ptr && head_ptr->link() != NULL)
        { 
            cursor = head_ptr->link();
            list_head_remove(head_ptr);
            precursor = NULL;
        }
        else if (cursor == tail_ptr && many_nodes > 1)
        { 
            tail_ptr = precursor;
            delete cursor;
            cursor = NULL;
            tail_ptr->set_link(NULL);
        }
        else if (cursor != head_ptr && cursor != tail_ptr)
        { 
            precursor->set_link(cursor->link());
            delete cursor;
            cursor = precursor->link();
        }
        many_nodes--;
    }

    sequence::size_type sequence::size() const
    {
        return many_nodes;
    }

    bool sequence::is_item() const
    {
        if (cursor == NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    sequence::value_type sequence::current() const
    {
        assert(is_item());

        return cursor->data();
    }

} // namespace coen79_lab6