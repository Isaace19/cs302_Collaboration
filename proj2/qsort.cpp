// qsort.cpp

#include "volsort.h"

#include <cstdlib>
#include <array>

void qsort_sort(List &l, bool numeric)
{
    int i = 1;
    Node *arayOfNodes[l.size];
    Node *Temp = l.head;
    arayOfNodes[0] = Temp;

    while (Temp != NULL)
    {
        arayOfNodes[i] = Temp->next;
        Temp = Temp->next;
    }

    // create an array for copy the linked list into

    if (numeric)
    {
        std::qsort(arayOfNodes, i, sizeof(struct Node), qsort_number_compare);
    }
    else
    {
        std::qsort(arayOfNodes, i, sizeof(struct Node), qsort_string_compare);
    }
}
