// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		//    Precondition: start_ptr and end_ptr are pointers to nodes on the same
		//    linked list, with the start_ptr node at or before the end_ptr node
		//    Postcondition: head_ptr and tail_ptr are the head and tail pointers for a
		//    new list that contains the items from start_ptr up to but not including
		//    end_ptr.  The end_ptr may also be NULL, in which case the new list
		//    contains elements from start_ptr to the end of the list.
		//ensure start_ptr is before end_ptr in the list??
		if(start_ptr == NULL || start_ptr == end_ptr) 					//check for empty list
			return;
		head_ptr = NULL;
		tail_ptr = NULL;
		//create head node for new list
		list_head_insert(head_ptr, start_ptr->data());
		tail_ptr = head_ptr;
			

		//copy list elements up to end ptr
		for(start_ptr = start_ptr->link(); start_ptr != end_ptr && start_ptr != NULL; start_ptr = start_ptr->link()) {
			list_insert(tail_ptr, start_ptr->data());
			tail_ptr = tail_ptr->link();
		}
	}

    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		//     Precondition: head_ptr is the head pointer of a linked list.
		//     Postcondition: The return value is the count of the number of times
		//     target appears as the data portion of a node on the linked list.
		//     The linked list itself is unchanged.
		size_t count = 0;
		if(head_ptr == NULL)		//handle empty list
			return count;
		
		for(head_ptr; head_ptr != NULL; head_ptr = head_ptr->link()) {	//loop through the list iterating when data being tested has been found
			if(head_ptr->data() == target) 
				++count;
		}
		return count;
	}

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		//     Precondition: head_ptr is the head pointer of a linked list, and
		//     position > 0 and position <= list_length(head_ptr)+1.
		//     Postcondition: A new node has been added to the linked list with entry
		//     as the data. The new node occurs at the specified position in the list.
		//     (The head node is position 1, the next node is position 2, and so on.)
		//     Any nodes that used to be after this specified position have been
		//     shifted to make room for the one new node.
		if(head_ptr == NULL) {							//handle empty list
			list_head_insert(head_ptr, entry);	
			return;
		}
		assert(position > 0 && position <= list_length(head_ptr) + 1);
		if(position == 1) {				//special case for inserting at head
			node* inserthead = new node(entry, head_ptr);
			head_ptr = inserthead;
			return;
		}
		//find nodes before and after location for insert if not inserting at head
		node* before = list_locate(head_ptr, position - 1);
		node* after = list_locate(head_ptr, position);

		node* to_insert = new node(entry, after);
		before->set_link(to_insert);
	}

    node::value_type list_remove_at(node*& head_ptr, size_t position) {
		//     Precondition: head_ptr is the head pointer of a linked list, and
		//     position > 0 and position <= list_length(head_ptr).
		//     Postcondition: The node at the specified position has been removed from
		//     the linked list and the function has returned a copy of the data from
		//     the removed node.
		//     (The head node is position 1, the next node is position 2, and so on.)
		if(head_ptr == NULL)		//handle empty list
			return NULL;
		assert(position > 0 && position <= list_length(head_ptr));

		node* to_delete = NULL;				//will be used to free heap memory
		node::value_type to_return = list_locate(head_ptr, position)->data();		//return value

		if(position == 1) {		//handle deletion of head_ptr
			to_delete = head_ptr;
			head_ptr = head_ptr->link();		//set new head_ptr
			delete to_delete;
			return to_return;
		}
		//deletion of all other nodes
		node* before = list_locate(head_ptr, position - 1);
		to_delete = list_locate(head_ptr, position);
		before->set_link(to_delete->link());	//restore new link in list
		delete to_delete;						//free heap memory
		return to_return;
	}	

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		//     Precondition: head_ptr is the head pointer of a linked list, and
		//     (1 <= start) and (start <= finish) and (finish <= list_length(head_ptr)).
		//     Postcondition: The value returned is the head pointer for
		//     a new list that contains copies of the items from the start position to
		//     the finish position in the list that head_ptr points to.
		//     (The head node is position 1, the next node is position 2, and so on.)
		//     The list pointed to by head_ptr is unchanged.
		if(head_ptr == NULL)  
			return NULL;      										//handle empty list
		assert(1 <= start && start <= finish && finish <= list_length(head_ptr));

		node* return_head;
		node* tail_ptr;
		//find portion of list to copy over
		node* begin = list_locate(head_ptr, start);
		node* end = list_locate(head_ptr, finish + 1);

		//use list piece to assign return_head as head of new list from elements start to finish
		list_piece(begin,end,return_head,tail_ptr);
		return return_head;
	}

    void list_print (const node* head_ptr) {
		//     Precondition: head_ptr is the head pointer of a linked list, and
		//     the operator << has been defined for the value_type
		//     Postcondition: The value_type of all the nodes in the linked list are printed
		if(head_ptr == NULL) {
			std::cout << std::endl;
			return;
		}
		for(const node* cursor = head_ptr; cursor != NULL; cursor = cursor->link()) {
			if(cursor->link() != NULL)
				std::cout << cursor->data() << ", ";
			else 
				std::cout << cursor->data();
		}
		std::cout << std::endl;
	}

    void list_remove_dups(node* head_ptr) {
		//     Precondition: head_ptr is the head pointer of a linked list
		//     Postcondition: All the duplicates are removed from the linked list
		//     Example: If the list contains 1,1,1,2, after running this function the list
		//     contains 1,2
		if(head_ptr == NULL) 											//check for empty list
			return;
		for(node* cursor = head_ptr; cursor->link() != NULL; cursor = cursor->link()) {		//check this element for duplicates in entire list
			node* cursor2 = cursor;
			while(cursor2->link() != NULL) {							//check for dups of cursor
				if(cursor->data() == cursor2->link()->data()) {			//if found target duplicate in list
					node* to_remove = cursor2->link();
					if(to_remove->link() == NULL) {						//if at end of list
						cursor->set_link(NULL);
						delete to_remove;
						return;
					}
					cursor2 = to_remove->link();
					cursor->set_link(cursor2);
					delete to_remove;									//free heap memory
					
				}
				else													//check next element if dup not found
					cursor2 = cursor2->link();
			}
		}
		
	}

    node* list_detect_loop (node* head_ptr) {
		//     Precondition: head_ptr is the head pointer of a linked list
		//     Postcondition: If there is a loop in the linked list, the returned value
		//     is a pointer to the start of the loop. The returned value is NULL if
		//     there is no loop in the list
		if(head_ptr == NULL)
			return NULL;
		node* fast = head_ptr;							//two nodes for utilizing floyds cycle finding algorithm
		node* slow = head_ptr;
		while(fast != NULL && fast->link() != NULL) {	//jump fast node twice as fast as slow node throuhg list
			fast = fast->link()->link();
			if(fast == slow) 							//if they meet, there is a loop in the list
				return fast;							//return the node of the loop
			slow = slow->link();
		}

		return NULL;
	}

	size_t position(const node* head_ptr, const node* position_ptr) {
		//		Precondition: head_ptr is the head pointer of a linked list
		//					position_ptr is present in the linked list.
		//		Post-condition: position of the position_ptr is returned
		if(head_ptr == NULL) 
			return 0;
		size_t position = 1;
		for(head_ptr; head_ptr != position_ptr; head_ptr = head_ptr->link()) {		//iterate through the list until position is found
			++position;
		}
		return position;															//return the postiion
	}


    
    
}
