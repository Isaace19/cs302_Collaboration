#include "volsort.h"

#include <stdexcept>
#include <string>
List::List()
{
    head = NULL;
    size = 0;
}

// Proper Deconstructor call, deletes current node to prevent bad memory access.
List::~List()
{
    Node *curr = head;
    while (curr != NULL)
    {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }
    head = NULL;
}

void List::push_front(const std::string &s)
{
    int number = 0;
    try
    {
        number = std::stoi(s); // convert string to integer
    }
    catch (const std::invalid_argument &e)
    {
        number = 0;
    }
    catch (const std::out_of_range &e)
    {
        number = 0;
    }
    // removed the error checking with e.what() since there is no explicitly bad input.
    // However should there be bad conversion, default to number = 0

    // assign node string and integer for both regular string sort and numeric flag sorting
    Node *newNode = new Node();
    newNode->string = s;
    newNode->number = number;
    newNode->next = head;

    head = newNode;
    ++size;
}

// Dump node is used for error checking throughout the code. Can be inserted and called as dump_node(l.head)
// Gives the list as it comes in before sorting and than you can call again to get list after sorting
void dump_node(Node *n)
{
    while (n != nullptr)
    {
        std::cout << "Node(string: " << n->string << ", number: " << n->number << ")\n";
        n = n->next;
    }
}

// C++ style pointer comparisions
bool node_number_compare(const Node *a, const Node *b)
{
    return a->number < b->number;
}

bool node_string_compare(const Node *a, const Node *b)
{
    return a->string < b->string;
}
