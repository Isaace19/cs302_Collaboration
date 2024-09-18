// merge.cpp

#include "volsort.h"

#include <iostream>

// Prototypes

Node *msort(Node *head, bool numeric);
void split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) // wrapper function calls all the below funtions
{
    Node *head = l.head;
    l.head = msort(head, numeric);
}

Node *msort(Node *head, bool numeric) // recursive function, split(divide), merge(conquer)
{
    // base case returns head
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    // partition list
    Node *left = NULL;
    Node *right = NULL;

    split(head, *&left, *&right);
    left = msort(left, numeric);
    right = msort(right, numeric);

    // concatenate the two sides back together
    return merge(left, right, numeric);
}
// splits the linked list in half with the slow/faster pointer trick
void split(Node *head, Node *&left, Node *&right)
{
    // base case returns head
    if (head == NULL || head->next == NULL)
    {
        left = head;
        right = NULL;
        return;
    }

    Node *fast = head->next;
    Node *slow = head;

    // finding the midpoint via fast and slow pointers - If the fast pointer is 2 ahead, than we know the slow pointer is the midpoint
    // once the fast pointer hits null
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    left = head;
    right = slow->next; // splits the list in half by setting the right to the midpoint.
    slow->next = NULL;
}

Node *merge(Node *left, Node *right, bool numeric) // combines left and right lists
{
    Node *newhead = NULL;
    Node *NHTemp = NULL;

    // Compare and merge nodes
    while (left != NULL && right != NULL)
    {
        // compare based on numeric flag
        bool numcheck;
        if (numeric)
        {
            numcheck = node_number_compare(left, right);
        }
        else
        {
            numcheck = node_string_compare(left, right);
        }
        // append smaller nodes to the left sublist, initialize if empty
        if (numcheck)
        {
            if (newhead == NULL)
            {
                newhead = left;
                NHTemp = newhead;
            }
            else
            {
                NHTemp->next = left;
                NHTemp = NHTemp->next;
            }
            left = left->next;
        }
        // append larger nodes to the right sublist, initialize if empty
        else
        {
            if (newhead == NULL)
            {
                newhead = right;
                NHTemp = newhead;
            }
            else
            {
                NHTemp->next = right;
                NHTemp = NHTemp->next;
            }
            right = right->next;
        }
    }

    // ensures that the last nodes are null in both left and right lists.
    if (NHTemp->next != NULL)
    {
        NHTemp->next = NULL;
    }
    // Attach remaining nodes
    if (left != NULL)
    {
        NHTemp->next = left;
    }
    else if (right != NULL)
    {
        NHTemp->next = right;
    }

    return newhead;
}
