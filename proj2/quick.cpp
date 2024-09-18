// quick.cpp

#include "volsort.h"

#include <string>
#include <cstring>
// Prototypes

Node *qsort(Node *head, bool numeric);
void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations

void quick_sort(List &l, bool numeric)
{
    Node *head = l.head;
    l.head = qsort(head, numeric);
}

Node *qsort(Node *head, bool numeric)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    // partition list
    Node *left = NULL;
    Node *right = NULL;
    Node *pivot = head;

    // recursive sort
    partition(head->next, pivot, left, right, numeric);
    left = qsort(left, numeric);
    right = qsort(right, numeric);

    // logic checks if left or right sublists are empty. if so, connect the pivot to the left or right to make concatenation work
    if (left == NULL)
    {
        pivot->next = right;
        return pivot;
    }
    else
    {
        Node *TempLeft = left;
        while (TempLeft->next != NULL)
        {
            TempLeft = TempLeft->next;
        }
        pivot->next = NULL;
        TempLeft->next = pivot;
    }

    // concatenate the two sides back together - Returns the new head of the list
    return concatenate(left, right);
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric)
{
    // pointers track the end of the left and right sublists
    Node *less_than = NULL;
    Node *great_than = NULL;
    left = NULL;
    right = NULL;

    while (head)
    {
        Node *nextNode = head->next; // save before modifying our head

        // sort based on if the numeric flag is true or false
        bool compare_result;
        if (numeric)
        {
            compare_result = node_number_compare(pivot, head);
        }
        else
        {
            compare_result = node_string_compare(pivot, head);
        }

        // if the value is less than our pivot, add to the left sublist
        if (!compare_result)
        {
            if (left == NULL)
            {
                left = head;
                less_than = head;
            }
            else
            {
                less_than->next = head;
                less_than = head;
            }
        }
        // else, if the value is greater than our pivot, add to the right sublist
        else
        {
            if (right == NULL)
            {
                right = head;
                great_than = right;
            }
            else
            {
                great_than->next = head;
                great_than = head;
            }
        }
        // disconnect node from list, moves to next node
        head->next = NULL;
        head = nextNode;
    }

    // ensure tail is pointing to a nullptr for both left and right sublists
    if (less_than != NULL)
    {
        less_than->next = NULL;
    }
    if (great_than != NULL)
    {
        great_than->next = NULL;
    }
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
