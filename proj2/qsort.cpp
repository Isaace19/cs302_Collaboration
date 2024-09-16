// qsort.cpp

#include "volsort.h"

#include <cstdlib>
#include <vector>

// create function prototypes
int qsort_number_compare(const void *a, const void *b);
int qsort_string_compare(const void *a, const void *b);

void qsort_sort(List &l, bool numeric)
{
    std::vector<Node *> nodes;
    Node *temp = l.head;
    //	std::cout << "BEFORE SORTING...\n";
    //	dump_node(l.head);

    // copy the list into the array of pointers
    while (temp != NULL)
    {
        nodes.push_back(temp);
        temp = temp->next;
    }

    if (numeric)
    {
        std::qsort(nodes.data(), nodes.size(), sizeof(Node *), qsort_number_compare);
    }
    else
    {
        std::qsort(nodes.data(), nodes.size(), sizeof(Node *), qsort_string_compare);
    }

    // Rebuild the linked list from the sorted nodes
    l.head = nodes[0]; // Set the new head to the first node in the sorted list

    // Relink the nodes in the sorted order
    for (size_t i = 0; i < nodes.size() - 1; ++i)
    {
        nodes[i]->next = nodes[i + 1]; // Link current node to the next one
    }
    // Ensure the last node points to NULL
    nodes[nodes.size() - 1]->next = NULL;

    //	std::cout << "AFTER SORTING...\n";
    //	dump_node(l.head);
}

// create proper comparison functions
int qsort_number_compare(const void *a, const void *b)
{
    // must dereference const void pointers to get the Node*
    const Node *nodeA = *static_cast<const Node *const *>(a);
    const Node *nodeB = *static_cast<const Node *const *>(b);

    if (nodeA->number > nodeB->number)
        return 1;
    if (nodeA->number < nodeB->number)
        return -1;
    return 0;
}

int qsort_string_compare(const void *a, const void *b)
{
    // do the same thing and dereference the void pointers to get Node*
    const Node *nodeA = *static_cast<const Node *const *>(a);
    const Node *nodeB = *static_cast<const Node *const *>(b);

    // compare the fields
    return nodeA->string.compare(nodeB->string);
}
