#include "volsort.h"

List::List()
{
    head = NULL;
    size = 0;
}

List::~List()
{
    Node *curr = head;
    while (curr != 0)
    {
        Node *next = curr->next;
        delete next;
        curr = next;
    }
    head = 0;
}

void List::push_front(const std::string &s)
{

    int number = 0;
    // convert the string into int
    try
    {
        number = std::stoi(s); // convert string to integer
    }

    // invliad input catch exceptions
    catch (const std::invalid_argument &e)
    {
        // handle weight chars in input stream
        std::cerr << "Invalid input " << e.what() << '\n';
    }
    catch (const std::out_of_range &e)
    {
        // handle out of range errors
        std::cerr << "Invalid input " << e.what() << '\n';
    }

    Node *newNode = new Node();
    newNode->string = s;      // assign string
    newNode->number = number; // assign integer
    newNode->next = head;

    head = newNode;
    size++;
}

void dump_node(Node *n) // implement in this file (volsort.h) to make it easier for TAs to grade
{
    Node *temp = n;
    while (temp != NULL)
    {
        std::cout << n->number << '\n';
        temp = temp->next;
    }
};

// implement node num compare and string compare
bool node_number_compare(const Node *a, const Node *b)
{
    if (a->string == b->string)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool node_string_compare(const Node *a, const Node *b)
{
    if (a->number == b->number)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

int qsort_number_compare(const void *a, const void *b)
{
    if (a == b)
    {
        return (0);
    }
    else if (a < b)
    {
        return (-1);
    }
    else
    {
        return (1);
    }
}

int qsort_string_compare(const void *a, const void *b)
{
    if (a == b)
    {
        return (0);
    }
    else if (a < b)
    {
        return (-1);
    }
    else
    {
        return (1);
    }
}