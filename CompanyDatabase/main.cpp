//
//  main.cpp
//
//  Test file for the database class
//
// 
//

#include "database.h"

using namespace coen79_lab7;

int main(int argc, const char * argv[]) {
    
    std::cout << "\nTesting constructor...!\n";
    database myDB1;
    std::cout << "\nInserting company names...!\n";
    myDB1.insert_company("Intel");
    myDB1.insert_company("NVIDIA");
    myDB1.insert_company("Cypress");

    std::cout << "\nPrinting myDB1...\n";
    myDB1.print_companies();


    std::cout << "\nInserting company names to invoke reserve...!\n";
    myDB1.insert_item("Intel", "Core i7", 300.0);
    myDB1.insert_item("Intel", "Core i5", 200.0);
    std::cout << "\nPrinting myDB1...\n";
    myDB1.print_items_by_company("Intel");


    std::cout << "\nInserting company names to invoke reserve...!\n";

    myDB1.insert_company("Qualcomm");
    myDB1.insert_company("Apple");
    
    std::cout << "\nInserting product names...!\n";
    myDB1.insert_item("Apple", "iPhone 6", 400.0);
    myDB1.insert_item("Apple", "iPhone X", 900.0);
    std::cout << "\nPrinting products of Apple and Intel...\n";
    myDB1.print_items_by_company("Apple");
    myDB1.print_items_by_company("Intel");

    
    std::cout << "\nCreating myDB2 on heap...\n";
    database *myDB2 = new database();
    myDB2->insert_company("Google");
    myDB2->insert_item("Google", "glass", 1000.0);
    myDB2->insert_item("Google", "phone", 1000.0);
    myDB2->insert_item("Google", "Android", 0.0);
    myDB2->insert_item("Google", "TensorFlow", 0.0);
    myDB2->erase_item("Google", "phone");
    std::cout << "\nPrinting myDB2...\n";
    myDB2->print_items_by_company("Google");

    
    std::cout << "\nCreating myDB3 on heap...\n";
    database *myDB3 = new database();
    std::cout << "\nAssigning myDB2 to myDB3...\n";
    *myDB3 = *myDB2;
    std::cout << "\nPrinting myDB3...\n";
    myDB3->print_items_by_company("Google");

    
    myDB2->erase_company("Google");
    std::cout << "\nPrinting myDB2...\n";
    myDB2->print_items_by_company("Google");
    std::cout << "\nPrinting myDB3...\n";
    myDB3->print_items_by_company("Google");

    
    std::cout << "\nDeleting myDB2 and myDB3...\n";
    delete myDB2;
    delete myDB3;

        std::cout << "\nTesting constructor\n";
    database db1;
    database blankdb;
    std::cout << "\nInserting company names\n";
    db1.insert_company("company1");
    db1.insert_company("company2");
    db1.insert_company("company3");

    std::cout << "\nPrinting db1\n";
    db1.print_companies();


    std::cout << "\nTesting reserve function my inserting products\n";              //testing allocation of dynamic memory
    db1.insert_item("company1", "p1", 100.0);
    db1.insert_item("company1", "p2", 200.0);
    std::cout << "\nPrinting db1 company1 items\n";
    db1.print_items_by_company("company1");

    std::cout << "\nAttempting to enter pre-existing company\n";
    bool insertiontest = db1.insert_company("company1");
    if(!insertiontest)                                                                  //duplicate companies
        std::cout << "Passed inserting company1 copy\n";
    else 
        std::cout << "Failed: inserted a copy of company 1\n";
    
    insertiontest = db1.insert_company("company2");
    if(!insertiontest) 
        std::cout << "Passed inserting company2 copy\n";
    else 
        std::cout << "Failed: inserted a copy of company 2\n";
    
    insertiontest = db1.insert_company("company3");
    if(!insertiontest) 
        std::cout << "Passed inserting company3 copy\n";
    else 
        std::cout << "Failed: inserted a copy of company 3\n";

    std::cout << "\nAttempting to insert copies of products of company 1\n";
    db1.insert_item("company1", "p1", 50000.0);                                         //duplicate products
    db1.insert_item("company1", "p2", 50000.0);
    db1.print_items_by_company("company1");

    std::cout << "\nFilling company 2 to test company erase\n";
    db1.insert_item("company2", "p1", 300.0);
    db1.insert_item("company2", "p2", 400.0);
    db1.insert_item("company2", "p3", 500.0);
    db1.print_items_by_company("company2");

    std::cout << "\nNow erasing company 2\n";
    db1.erase_company("company2");                                      //erasure of company
    db1.erase_company("company5");                                      //erasure of non existent company
    std::cout<< "Products of company 2: \n";
    db1.print_items_by_company("company2");
    db1.print_companies();

    std::cout << "\nTesting erasure of specific items in company 1 \n";
    db1.insert_item("company1", "p3", 300.0);                           
    db1.insert_item("company1", "p4", 400.0);                       
    db1.insert_item("company5", "thiscompanyisnthere", 50000.0);        //non existent company test
    db1.print_items_by_company("company1");
    
    db1.erase_item("company1", "p4");                                   //delete from end                   
    db1.erase_item("company1", "p2");                                   //delete from mid
    db1.erase_item("company1", "p1");                                   //delete from front
    db1.erase_item("company1", "negativetest");                         //delete something non existent
    std::cout << "Deleted from back, front and middle, should only have p3 remaining\n";
    db1.print_items_by_company("company1");

    std::cout << "\nNow creating databases on heap memory\n";
    database *db2 = new database();
    database *blankdb2 = new database();
    db2->insert_company("company2");
    db2->insert_item("company2", "p1", 300.0);
    db2->insert_item("company2", "p2", 400.0);
    db2->insert_item("company2", "p3", 500.0);
    db2->insert_item("company2", "p4", 600.0);
    db2->print_items_by_company("company2");
    std::cout <<"blankdb2... should be empty\n";

    std::cout <<"\nNow testing assignment with filled and empty database\n";            //TESTING COPYING OF DATABASES
    database* equalsdb2 = new database();                                               //FAILED 1ST ITERATION
    database* equalsblank = new database();                                             //Passed second
    *equalsdb2 = *db2;
    *equalsblank = *blankdb2;
    std::cout << "Printing equivalent of db2\n";
    equalsdb2->print_companies();
    equalsdb2->print_items_by_company("company2");
    std::cout << "Printing blank equivalent: \n";

    std::cout << "\nDeleting databases on heap\n";
    delete db2;
    delete blankdb2;
    delete equalsdb2;
    delete equalsblank;
    std::cout << "Delete successful\n";
    
    return 0;
}
