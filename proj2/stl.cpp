// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void stl_sort(List &l, bool numeric)
{
    // implement an STL sort for a linked list implementation.

    // create an array for copy the linked list into
    std::vector<Node *> nodes;
    Node *curr = l.head;
    int counter = 1;
    while (curr != NULL)
    {
        nodes.push_back(curr);
        curr = curr->next;
        counter = counter + 1;
    }

    if (numeric)
    {
        std::sort(nodes.begin(), nodes.end(), node_number_compare);
    }
    else
    {
        std::sort(nodes.begin(), nodes.end(), node_string_compare);
    }
    // relink our linked list:
    l.head = nodes[0];
    for (int i = 0; i < counter - 1; ++i)
    {
        nodes[i]->next = nodes[i + 1];
        if (i == counter - 1)
        {
            nodes[i + 1]->next = NULL;
        }
    }
}
