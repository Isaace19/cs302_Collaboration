// merge.cpp

#include "volsort.h"

// Prototypes

Node *msort(Node *head, bool numeric);
void split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric)
{
    // should just start the sorting process calling qsort
    l.head = msort(l.head, numeric);
}

Node *msort(Node *head, bool numeric)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *left = NULL;
    Node *right = NULL;

    split(head->next, left, right);
    left = msort(left, numeric);
    right = msort(right, numeric);

    return merge(left, right, numeric);
}

void split(Node *head, Node *&left, Node *&right)
{
    if (head == NULL || head->next == NULL)
    {
        left = head;
        right = NULL;
        return;
    }

    Node *fast = head;
    Node *slow = head;

    // finding the midpoint via fast and slow pointers
    while (fast->next->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    left = head;
    right = slow->next; // splits the list in half
    slow->next = NULL;
}

Node *merge(Node *left, Node *right, bool numeric)
{
    Node *newhead = NULL;
    Node *NHTemp = NULL;
    Node *LTemp = left;
    Node *RTemp = right;
    while (LTemp != NULL && RTemp != NULL)
    {
        bool numcheck;
        if (numeric)
        {
            numcheck = node_number_compare(LTemp, RTemp);
        }
        else
        {
            numcheck = node_string_compare(LTemp, RTemp);
        }
        if (numcheck)
        {
            if (newhead == NULL)
            {
                newhead = LTemp;
                NHTemp = newhead;
                LTemp = LTemp->next;
            }
            else
            {
                NHTemp->next = LTemp;
                NHTemp = NHTemp->next;
                LTemp = LTemp->next;
            }
        }
        else
        {
            if (newhead == NULL)
            {
                newhead = RTemp;
                NHTemp = newhead;
                RTemp = RTemp->next;
            }
            else
            {
                NHTemp->next = RTemp;
                NHTemp = NHTemp->next;
                RTemp = RTemp->next;
            }
        }
    }
    return (newhead);
}
