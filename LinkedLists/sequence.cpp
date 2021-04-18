
#include "sequence.h"
#include "node.h"
#include "assert.h"
#include <iostream>
#include <cstdlib>

using namespace coen79_lab6;

namespace coen79_lab6 {

        sequence::sequence( ) {
                //     Postcondition: The sequence has been initialized as an empty sequence.
                init();
        }
        sequence::sequence(const sequence& source) {
                //      copy constructor, new sequence initialized with source
                init();                                         //initialize new sequence
                if(source.head_ptr == NULL) return;             //if passed empty sequence, return
                list_copy(source.head_ptr, head_ptr, tail_ptr);
                if(source.is_item() && source.cursor != source.head_ptr) {   //handling a list with a cursor that is not NULL or not head
                        precursor = list_locate(head_ptr, position(source.head_ptr, source.precursor));
                        cursor =  precursor->link();
                }
                if(source.cursor == source.head_ptr)    //handling list with cursor aat head
                        cursor = head_ptr; 
                many_nodes = source.many_nodes;
                tail_ptr = list_locate(head_ptr, size());       //initialize tail ptr to end of new sequence.
        }
        sequence::~sequence( ) {
                //      DESTRUCTOR
                list_clear(head_ptr);

        }
        
        // MODIFICATION MEMBER FUNCTIONS
        void sequence::start( ) {
                //     Postcondition: The precursor and cursor are adjusted such that the first
                //     item in the sequence becomes the current item (but if the sequence is
                //     empty, then there is no current item).
                if(many_nodes == 0) 
                        return;
                cursor = head_ptr;
                precursor = NULL;
        }
        void sequence::end() {
                //     Postcondition: The precursor and cursor are adjusted such that the last
                //     item in the sequence becomes the current item (but if the sequence is
                //     empty, then there is no current item).
                if(many_nodes == 0) 
                        return;
                cursor = tail_ptr;
                precursor = list_locate(head_ptr, (position(head_ptr, cursor) - 1)); //uses position in list toolkit to set precursor

        }
        void sequence::advance( ) {
                //     Precondition: is_item returns true.
                //     Postcondition: If the current item was already the last item in the
                //     sequence, then there is no longer any current item. Otherwise, the new
                //     current item is the item immediately after the original current item.
                if(many_nodes == 0) 
                        return;
                if(cursor->link() == NULL) {    //if cursor is at tthe end of the list
                        precursor = cursor; 
                        cursor = NULL;
                        return;
                }
                precursor = cursor; 
                cursor = cursor->link();
        }
        void sequence::insert(const sequence::value_type& entry) {
                //     Postcondition: A new copy of entry has been inserted in the sequence
                //     before the current item. If there was no current item, then the new entry
                //     has been inserted at the front of the sequence. In either case, the newly
                //     inserted item is now the current item of the sequence.
                if(head_ptr == NULL) {                          //handles empty list. 
                        list_head_insert(head_ptr, entry);
                        cursor = head_ptr;
                        tail_ptr = head_ptr;
                        ++many_nodes;
                        return;
                }
                if(cursor == NULL) {                            //handles no current item
                        list_head_insert(head_ptr, entry);      //inserted item will be new head ptr if no current item
                        cursor = head_ptr;                      //no need to alter tail
                        ++many_nodes;
                        return;
                }
                list_insert_at(head_ptr, entry, position(head_ptr, cursor));
                if(head_ptr->link() == cursor) {                //if inserting when precursor is still == NULL
                        cursor = head_ptr;
                        ++many_nodes;
                        tail_ptr = list_locate(head_ptr, size());               //set tail
                        return;
                }
                cursor = precursor->link();                             
                ++many_nodes;
                tail_ptr = list_locate(head_ptr, size());                       //set tail
        }
        void sequence::attach(const sequence::value_type& entry) {
                //     Postcondition: A new copy of entry has been inserted in the sequence after
                //     the current item. If there was no current item, then the new entry has
                //     been attached to the end of the sequence. In either case, the newly
                //     inserted item is now the current item of the sequence.
                if(head_ptr == NULL) {                                          //handle empty list. 
                        list_head_insert(head_ptr, entry);
                        cursor = head_ptr;
                        tail_ptr = head_ptr;
                        ++many_nodes;
                        return;
                }
                if(cursor == NULL) {                                            //handle no current item
                        list_insert(tail_ptr, entry);                           //item is now inserted at the end and is the new tail
                        cursor = tail_ptr->link();
                        ++many_nodes;
                        tail_ptr = list_locate(head_ptr, many_nodes);   
                        return;
                }
                list_insert_at(head_ptr, entry, position(head_ptr, cursor->link()));
                precursor = cursor;
                cursor = cursor->link();
                ++many_nodes;
                tail_ptr = list_locate(head_ptr, many_nodes);                   //set tail 
        }        
        void sequence::operator =(const sequence& source) {
                init();                                         //initialize new sequence
                if(source.head_ptr == NULL) return;             //if passed empty sequence, return
                list_copy(source.head_ptr, head_ptr, tail_ptr);
                if(source.is_item() && source.cursor != source.head_ptr) {   //handling a list with a cursor that is not NULL or not head
                        precursor = list_locate(head_ptr, position(source.head_ptr, source.precursor));
                        cursor =  precursor->link();
                }
                if(source.cursor == source.head_ptr)    //handling list with cursor aat head
                        cursor = head_ptr; 
                many_nodes = source.many_nodes;
                tail_ptr = list_locate(head_ptr, size());       //initialize tail ptr to end of new sequence.
        }
	void sequence::remove_current( ) {
                //     Precondition: is_item returns true.
                //     Postcondition: The current item has been removed from the sequence, and
                //     the item after this (if there is one) is now the new current item.
                if(!is_item()) 
                        return;
                node* to_delete = cursor;
                if(cursor == head_ptr) {                //if item to remove is at the head
                        head_ptr = cursor->link();
                        cursor = head_ptr;
                        delete to_delete;               //free heap mem
                        --many_nodes;
                        return;
                }                                       //otherwise set new links and free heap mem
                cursor = cursor->link();
                precursor->set_link(cursor);
                delete to_delete;                       //free hea mem
                --many_nodes;
        }
        
        // CONSTANT MEMBER FUNCTIONS
        sequence::size_type sequence::size( ) const {
                //     Postcondition: The return value is the number of items in the sequence.
                return many_nodes;
        }
        bool sequence::is_item( ) const {
                //     Postcondition: A true return value indicates that there is a valid
                //     "current" item that may be retrieved by activating the current
                //     member function (listed below). A false return value indicates that
                //     there is no valid current item.
                return (cursor != NULL);
        }
        sequence::value_type sequence::current( ) const {
                //     Precondition: is_item( ) returns true.
                //     Postcondition: The item returned is the current item in the sequence.
                if(is_item()) 
                        return (cursor->data());
        }
}