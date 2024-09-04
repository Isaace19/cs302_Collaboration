// volsort.h

#ifndef VOLSORT_H
#define VOLSORT_H

#include <string>

struct Node {
    std::string string;
    int         number;
    Node       *next;
};

struct List {
    Node       *head;
    size_t      size;

    List(); 					// define in list.cpp
    ~List();					// define in list.cpp

  void push_front(const std::string &s);	//define below
};

// Functions -------------------------------------------------------------------


void List::push_front(const std::string &s){
	
	int number = 0;
	// convert the string into int
	try{
		number = std::stoi(s); // convert string to integer
	}catch (const std::invalid_arguments& e){
		// handles invalid input
		// .what() is apart of invalid arg  
		std::cerr << "Invalid input " << e.what()  << '\n';
	}catch (const std::out_of_range& e){
		// handle out of range errors 
		std::cerr << "Invalid input " << e.what() << '\n';
	}
		
	Node * newNode = new Node();
	newNode->string = s; // assign string
	newNode->number = num; // assign integer
	newNode->next = head;

	head = newNode;
	size++;
}




bool node_number_compare(const Node *a, const Node *b); 	//implement in list.cpp to avoid compile-time issues, used by quick, merge and stl
bool node_string_compare(const Node *a, const Node *b);		//implement in list.cpp to avoid compile-time issues, merge and stl

void dump_node(Node *n);					// implement in this file (volsort.h) to make it easier for TAs to grade

void stl_sort(List &l, bool numeric);	// define in stl.cpp - sort using std::sort
void qsort_sort(List &l, bool numeric);	// define in qsort.cpp - sort using qsort from cstdlib
void merge_sort(List &l, bool numeric);	// define in merge.cpp - your implementation
void quick_sort(List &l, bool numeric);	// define in quick.cpp - your implementation

#endif
