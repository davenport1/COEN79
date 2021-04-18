#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "node.h"

using namespace coen79_lab7;

/* void list_print(const node* head) {
    std::cout << std::setw(10);
    for(head; head != NULL; head = head->getLink()) {
        std::cout << "Name: " << head->getName() << " | Price: " << head->getPrice() << " | \n";
    }
    std::cout << std::endl;
} */

int main(int argc, char const *argv[]) {
    // Make a list.
    node *my_list = NULL;
    node* temp;
    my_list = new node("zero", 0, NULL);
    std::cout << "The list: \n";
    list_print(my_list);
    
}