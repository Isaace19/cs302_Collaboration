// quick.cpp

#include "volsort.h"

#include <string>
#include <cstring>
// Prototypes

Node *qsort(Node *head, bool numeric);
void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);
Node *get_tail(Node *head);

// Implementations

void quick_sort(List &l, bool numeric)
{
    // should just start the sorting process calling qsort
    Node *head = l.head;
    if (head)
    {
        l.head = qsort(head, numeric);
    }
}

Node *qsort(Node *head, bool numeric)
{
    /*     // pseudocode
        if (head || !head->next)
            return head;

        // partition list
        Node *left = NULL;
        Node *right = NULL;
        Node *pivot = head; // head node as pivot

        // recursive sort -- TODO: handle the bool numerics
        partition(head->next, pivot, &left, &right, numeric);
        left = qsort(left, numeric);
        right = qsort(right, numeric);

        // concatenate the two sides back together
        return concatenate(left, right); */
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric)
{
    /*     // make nodes greater than or less than the pivot as we go in the linked list
        Node *less_than_tail = NULL;
        Node *greater_than_tail = NULL;

        *left = NULL;
        *right = NULL;

        while (head)
        {
            Node *nextNode = head->next; // save before modifying our head
                                         //
                                         // now we have to deal with numeric
            bool compare_result;
            if (numeric)
            {
                // convert string to number and compare
                int pivot_val = (pivot->number);
                int node_val = (head->number);
                compare_result = (node_val < pivot_val);
            }
            else
            {
                // string compare -- uses list value directly if numeric is false.
                compare_result = (head->number < pivot->number);
            }

            if (compare_result)
            {
                if (!left)
                {
                    left = head;
                    less_than_tail = head;
                }
                else
                {
                    less_than_tail->next = head;
                    less_than_tail = head;
                }
            }
            else
            {
                if (!right)
                {
                    right = head;
                    greater_than_tail = right;
                }
                else
                {
                    greater_than_tail->next = head;
                    greater_than_tail = head;
                }
            }
            head->next = NULL;
            head = nextNode;
        }

        // ensure tail is pointing to a nullptr
        if (less_than_tail)
        {
            less_than_tail->next = NULL;
        }
        if (greater_than_tail)
        {
            greater_than_tail->next = NULL;
        } */
}

Node *concatenate(Node *left, Node *right)
{
    // if one side of the list is empty, just return the other
    if (!left)
        return right;
    if (!right)
        return left;

    // start with left list
    Node *head = left;
    Node *tail = left;

    // traverse to the end of left list
    while (tail->next)
    {
        tail = tail->next;
    }

    // connect tail of left to head of right
    tail->next = right;

    return head;
}
