// qsort.cpp

#include "volsort.h"

#include <cstdlib>
#include <array>

// create function prototypes
int qsort_number_compare(const void *a, const void *b);
int qsort_string_compare(const void *a, const void *b);

void qsort_sort(List &l, bool numeric)
{
    Node **arrayOfNodes = new Node*[l.size];

	Node *temp = l.head;
	int i = 0;

	// copy the list into the array of pointers
	while (temp != NULL)
    {
        arrayOfNodes[i] = temp;
        temp = temp->next;
		i++;
    }

    if (numeric)
    {
        std::qsort(arrayOfNodes, l.size, sizeof(Node*), qsort_number_compare);
    }
    else
    {
        std::qsort(arrayOfNodes, l.size, sizeof(Node*), qsort_string_compare);
    }

	// rebuild linked list properly
	l.head = arrayOfNodes[0];
	for(size_t i = 0; i < l.size - 1; ++i){
		arrayOfNodes[i]->next = arrayOfNodes[i+1];
	}
	arrayOfNodes[l.size - 1]->next = NULL;

	delete[] arrayOfNodes;
}

// create proper comparison functions
int qsort_number_compare(const void *a, const void *b){
	// must dereference const void pointers to get the Node*
	Node* nodeA = (*(Node**)a);
	Node* nodeB = (*(Node**)b);

	// compare the int fields
	if (nodeA->number < nodeB->number){
		return (-1);
	}else if(nodeA->number > nodeB->number){
		return (1);
	}else{
		return (0);
	}
}

int qsort_string_compare(const void *a, const void *b){
	// do the same thing and dereference the void pointers to get Node*
	Node* nodeA = (*(Node**)a);
	Node* nodeB = (*(Node**)b);

	//compare the fields
	return nodeA->string.compare(nodeB->string);
}
