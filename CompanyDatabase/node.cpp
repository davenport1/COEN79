
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace coen79_lab7
{
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    node* node::getLink() {
        return link;
    }
    
    const node* node::getLink() const {
        return link;
    }
    
    std::string node::getName() const{
        return name;
    }
    
    float node::getPrice() const {
        return price;
    }
    
    
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {
        if(tail == NULL || newName.empty()) 
            return;                                                     //check for tail
        node* new_tail = new node(newName, newPrice, NULL);             //initialize new node with passed data
        tail->setLink(new_tail);                                        //set link from former tail
        tail = new_tail;                                                //new tail is new node inserted

    }
    
    
    void list_clear(node*& head) {
        if(head == NULL) 
            return;
        node* temp = head;              //store node to delete
        head = head->getLink();         //set next head node
        delete temp;                    //free heap memory
        list_clear(head);               //recursively call list_clear, will return when head == NULL
    }
    
    
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;
        
        const node *cur = old_head;
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    
    void list_head_remove(node*& head) {   
        if(head == NULL) 
            return;                     //if there is not at least one element in the list no elemnt to remove
        node* temp = head;
        head = head->getLink();            //create temporary node to hold the head and then set head to next
        delete temp;                    //free heap memory
    }
    
    
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }

    void list_delete_item (node* head_ptr, const std::string& target) {
        if(head_ptr == NULL || !(list_contains_item(head_ptr, target)))
            return;

        if(target == head_ptr->getName()) {   //check if head_ptr contains target
            list_head_remove(head_ptr);
            return;
        }

        for ( node *cursor = head_ptr->getLink(); cursor->getLink() != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getLink()->getName( )) {                //find node containing target if it exists
                node* temp = cursor->getLink();                         //standard deletion of node in linked list
                cursor->setLink(temp->getLink());
                delete temp;
            }
    }
    
}

#endif
