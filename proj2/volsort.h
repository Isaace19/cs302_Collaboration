// volsort.h

#ifndef VOLSORT_H
#define VOLSORT_H

#include <iostream>
#include <stdexcept>
#include <string>

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

    List();  // define in list.cpp
    ~List(); // define in list.cpp

    void push_front(const std::string &s); // define below
};

// Functions -------------------------------------------------------------------

void dump_node(Node *n);

bool node_number_compare(const Node *a, const Node *b); // implement in list.cpp to avoid compile-time issues, used by quick, merge and stl
bool node_string_compare(const Node *a, const Node *b); // implement in list.cpp to avoid compile-time issues, merge and stl

// create comparator function because return ints instead;
int qsort_number_compare(const void *a, const void *b); // implement in list.cpp to avoid compile-time issues, used by quick, merge and stl
int qsort_string_compare(const void *a, const void *b); // implement in list.cpp to avoid compile-time issues, merge and stl

void stl_sort(List &l, bool numeric);   // define in stl.cpp - sort using std::sort
void qsort_sort(List &l, bool numeric); // define in qsort.cpp - sort using qsort from cstdlib
void merge_sort(List &l, bool numeric); // define in merge.cpp - your implementation
void quick_sort(List &l, bool numeric); // define in quick.cpp - your implementation

#endif
