#include <iostream>
#include "sequence.h"

// Main Function Stuff

using namespace std;
using coen79_lab6::sequence;

void printSequence(sequence &s) {
	sequence seq(s);
	seq.start();
	// Loop to print the sequence.
	while(seq.is_item()) {
		cout << seq.current() << " ";
		seq.advance();
	}
	cout << endl;
}

int main(int argc, const char * argv[])
{
	sequence seq1, seq2;
	// Testing attach
	seq1.attach(42);
	printSequence(seq1);
	seq1.attach(25);
	printSequence(seq1);
	seq1.attach(2);
	printSequence(seq1);
	// Testing insert
	seq1.insert(9);
	printSequence(seq1);
	seq1.insert(17);
	printSequence(seq1);
	seq1.attach(13);
	printSequence(seq1);

	// Test remove from end.
	cout << " *** End Removal Test *** " << endl;
	seq1.end();
	if (seq1.is_item()) seq1.remove_current();
	printSequence(seq1);
	// Test remove from front.
	cout << " *** Start Removal Test *** " << endl;
	seq1.start();
	if (seq1.is_item()) seq1.remove_current();
	printSequence(seq1);
	// Test remove from middle
	cout << " *** Middle Removal Test *** " << endl;
	seq1.start();
	seq1.advance();
	seq1.remove_current();
	printSequence(seq1);

	cout << " *** First Assignment Test *** " << endl;
	seq2 = seq1;
	seq1.attach(5);
	printSequence(seq1);
	printSequence(seq2);
	seq2.insert(18);
	seq2.attach(92);
	printSequence(seq2);
	
	cout << " *** More Assignment Tests *** " << endl;
	sequence seqA, seqEmpty, seqOneItem, seqTenItems;
	for (int i = 0; i < 5; i++) seqA.attach(i);
	seqOneItem.attach(1.001);
	for (int i = 0; i < 10; i++) seqTenItems.attach(i);
	printSequence(seqA);
	// Empty Assignment test.
	seqA = seqEmpty;
	printSequence(seqA);
	// One item assignment, precursor is NULL.
	seqA = seqOneItem;
	printSequence(seqA);
	cout << "Is item: " << seqA.is_item() << endl;
	// One item assignment, cursor is NULL.
	seqOneItem.advance();
	seqA = seqOneItem;
	printSequence(seqA);
	cout << "Is item: " << seqA.is_item() << endl;
	// Many items, cursor at start.
	seqTenItems.start();
	seqA = seqTenItems;
	printSequence(seqA);
	cout << "Is item: " << seqA.is_item() << endl;
	// Many items, cursor in middle.
	for (int i = 0; i < 4; ++i) seqTenItems.advance();
	seqA = seqTenItems;
	printSequence(seqA);
	cout << "Is item: " << seqA.is_item() << endl;
	// Many items, cursor at end.
	seqTenItems.end();
	seqA = seqTenItems;
	printSequence(seqA);
	cout << "Is item: " << seqA.is_item() << endl;
	// Many items, cursor off end.
	seqTenItems.advance();
	seqA = seqTenItems;
	printSequence(seqA);
	cout << "Is item: " << seqA.is_item() << endl;
	
	// Example from lab. Can't do perfectly because printing moves the index.
	cout << " *** Lab Example *** " << endl;
	sequence labSequence;
	cout << "Size: " << labSequence.size() << endl;
	cout << "Is_Item: " << labSequence.is_item() << endl;
	labSequence.insert(12);
	printSequence(labSequence);
	labSequence.insert(17);
	printSequence(labSequence);
	labSequence.advance();
	cout << "Is_Item: " << labSequence.is_item() << endl;
	labSequence.insert(7);
	printSequence(labSequence);
	labSequence.attach(4);
	printSequence(labSequence);
	labSequence.advance();
	labSequence.advance();
	cout << "Size: " << labSequence.size() << endl;
	cout << "Is_Item: " << labSequence.is_item() << endl;
	labSequence.insert(3);
	printSequence(labSequence);
	labSequence.advance();
	labSequence.remove_current();
	printSequence(labSequence);
	labSequence.advance();
	labSequence.remove_current();
	printSequence(labSequence);
	labSequence.advance();
	labSequence.attach(11);
	printSequence(labSequence);
	labSequence.start();
	cout << "Start: " << labSequence.current() << endl;
	labSequence.end();
	cout << "End: " << labSequence.current() << endl;

	//BEGIN STUDENT TESTING

	cout << endl << " *** Begin Student Testing *** " << endl;
	sequence empty;
	sequence empty_copy(empty);
	sequence empty_assign = empty;
	cout << " Empty testing:  " << endl;
	printSequence(empty);
	printSequence(empty_copy);
	printSequence(empty_assign);

	cout << empty.size() << endl;
	empty.advance();
	empty.advance();
	if(empty.is_item()) cout << "fail" << endl;
	else cout << "pass advancing empty list" << endl;
	empty.start();
	if(empty.is_item()) cout << "fail" << endl;
	else cout << "pass start empty list" << endl;
	empty.end();
	if(empty.is_item()) cout << "fail" << endl;
	else cout << "pass end empty list" << endl;
	empty.remove_current();

	sequence attachtest;
	sequence inserttest;

	for(int i = 1; i < 6; ++i) attachtest.attach(i);
	for(int i = 5; i > 0; --i) inserttest.insert(i);
	cout << endl << " *** Following should be equal *** " << endl;
	printSequence(attachtest);
	printSequence(inserttest);

	cout << "attachtest current is: " << attachtest.current() << endl;
	cout << "attachtest after advancing out of bounds: " << endl;
	if(attachtest.is_item()) cout << "fail" << endl;
	else cout << "pass" << endl;

	cout << " *** Inserting at front *** " << endl;
	attachtest.start();
	for(int i = 2; i < 6; ++i) attachtest.insert(i);
	inserttest.start();
	for(int i = 2; i < 6; ++i) inserttest.insert(i);
	printSequence(attachtest);
	printSequence(inserttest);

	cout << " *** Attaching at front *** " << endl;
	attachtest.start();
	for(int i = 1; i < 4; ++i) attachtest.attach(i);
	inserttest.start();
	for(int i = 1; i < 4; ++i) inserttest.attach(i);
	printSequence(attachtest);
	printSequence(inserttest);

	cout << " *** attaching at end *** " << endl;
	attachtest.end();
	for(int i = 4; i > 0; --i) attachtest.attach(i);
	printSequence(attachtest);
	cout << " *** Inserting at end *** " << endl;
	attachtest.end();
	for(int i = 4; i > 0; --i) attachtest.insert(i);
	printSequence(attachtest);

	
}
