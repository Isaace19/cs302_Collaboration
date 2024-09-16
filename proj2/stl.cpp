#include "volsort.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void stl_sort(List &l, bool numeric)
{
    // implement an STL sort for a linked list implementation.

    // create an array for copying the linked list into a vector
    std::vector<Node *> nodes;
    Node *curr = l.head;

    // Push all nodes into the vector
    while (curr != NULL)
    {
        nodes.push_back(curr);
        curr = curr->next;
    }

    // Sort the nodes using std::sort
    if (numeric)
    {
        std::sort(nodes.begin(), nodes.end(), node_number_compare);
    }
    else
    {
        std::sort(nodes.begin(), nodes.end(), node_string_compare);
    }

    // Relink the sorted nodes back into a linked list:
    l.head = nodes[0]; // Set the new head to the first node in the sorted list

    // Relink the nodes in the sorted order
    for (size_t i = 0; i < nodes.size() - 1; ++i)
    {
        nodes[i]->next = nodes[i + 1]; // Link current node to the next one
    }
    // Ensure the last node points to NULL
    nodes[nodes.size() - 1]->next = NULL;
}
