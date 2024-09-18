// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

/*void stl_sort(List &l, bool numeric)
{
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
}*/
void stl_sort(List &l, bool numeric) {
    // Check if the list is empty
    if (l.head == NULL)
    {
      return;
    }
    // create an array to copy the linked list into
    std::vector<Node *> nodes;
    Node *curr = l.head;
    // Push all nodes into the vector
    while (curr != NULL)
    {
      nodes.push_back(curr);
      curr = curr->next;
    }
    // Sort the nodes based on the comparison function
    if (numeric)
    {
      std::sort(nodes.begin(), nodes.end(), node_number_compare);
    }
    else
    {
      std::sort(nodes.begin(), nodes.end(), node_string_compare);
    }
    // Relink the nodes in sorted order
    l.head = nodes[0];
    for (size_t i = 0; i < nodes.size() - 1; ++i)
    {
        nodes[i]->next = nodes[i + 1];
    }
    // Set the last node's next to null
    nodes.back()->next = NULL;
}
