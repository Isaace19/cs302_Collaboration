// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void stl_sort(List &l, bool numeric)
{
    // Base Case
    if (l.head == NULL)
    {
        return;
    }
    std::vector<Node *> nodes;
    Node *curr = l.head;
    while (curr != NULL)
    {
        nodes.push_back(curr);
        curr = curr->next;
    }
    // Sort the nodes based on the comparison function & use stl's std::sort
    if (numeric)
    {
        std::sort(nodes.begin(), nodes.end(), node_number_compare);
    }
    else
    {
        std::sort(nodes.begin(), nodes.end(), node_string_compare);
    }
    // rebuild linked list properly - assign next pointers to correct nodes, link head back to the front of the vector
    // and ensure last node points to a NULL pointer.
    l.head = nodes[0];
    for (size_t i = 0; i < nodes.size() - 1; ++i)
    {
        nodes[i]->next = nodes[i + 1];
    }
    // Set the last node's next to null
    nodes.back()->next = NULL;
}
