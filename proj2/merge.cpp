// merge.cpp

#include "volsort.h"

#include <iostream>

// Prototypes

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) //wrapper function calls all the below funtions
{
    Node *head = l.head;
        l.head = msort(head, numeric);
}

Node *msort(Node *head, bool numeric) //recursive function, split(divide), merge(conquer)
{
        // pseudocode
        if(head == NULL || head->next == NULL)
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

void split(Node *head, Node *&left, Node *&right) //splits the linked list in half with the slow/faster pointer trick
{
    if (head == NULL || head->next == NULL)
    {
        left = head;
        right = NULL;
        return;
    }

    Node *fast = head->next;
    Node *slow = head;

    // finding the midpoint via fast and slow pointers
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    left = head;
    right = slow->next; // splits the list in half
    slow->next = NULL;
}

Node *merge(Node *left, Node *right, bool numeric) //combines left and right lists
{
   Node* newhead = NULL;
   Node* NHTemp = NULL;

    // Compare and merge nodes
    while (left != NULL && right != NULL)
    {
      bool numcheck;
      if (numeric) 
      {
        numcheck = node_number_compare(left, right);
      }
      else
      {
        numcheck = node_string_compare(left, right);
      }
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
    if(NHTemp->next != NULL)
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
