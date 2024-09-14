// volsort.h

#ifndef VOLSORT_H
#define VOLSORT_H

#include <string>
#include <stdexcept>
#include <iostream>

struct Node
{
    std::string string;
    int number;
    Node *next;
};

struct List
{
    Node *head;
    size_t size;

    List();  // define in list.cpp --> DONE
    ~List(); // define in list.cpp

    void push_front(const std::string &s); // define below

    // To get the number value for the new struct Node,
    // you should use the std::stoi function (if this conversion fails,
    // you can default to 0 for the number value).
};

// Functions -------------------------------------------------------------------

void dump_node(Node *n);

bool node_number_compare(const Node *a, const Node *b); // implement in list.cpp to avoid compile-time issues, used by quick, merge and stl
bool node_string_compare(const Node *a, const Node *b); // implement in list.cpp to avoid compile-time issues, merge and stl

void stl_sort(List &l, bool numeric);   // define in stl.cpp - sort using std::sort
void qsort_sort(List &l, bool numeric); // define in qsort.cpp - sort using qsort from cstdlib
void merge_sort(List &l, bool numeric); // define in merge.cpp - your implementation
void quick_sort(List &l, bool numeric); // define in quick.cpp - your implementation

#endif
