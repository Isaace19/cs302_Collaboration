#include "volsort.h"

#include <stdexcept>
#include <string>
List::List()
{
    head = NULL;
    size = 0;
}

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
    // convert the string into int
    try
    {
        number = std::stoi(s); // convert string to integer
    }
	catch (const std::invalid_argument &e)
    {
		number = 0; // default to 0 if the conversion fails
    }
    catch (const std::out_of_range &e)
    {
		number = 0; // default to 0 if the conversion fails
    }

    Node *newNode = new Node();
    newNode->string = s;      // assign string
    newNode->number = number; // assign integer
    newNode->next = head;

    head = newNode;
    ++size;
}

void dump_node(Node *n)
{
    while (n != nullptr)
    {
        std::cout << "Node(string: " << n->string << ", number: " << n->number << ")\n";
        n = n->next;
    }
}

// implement node num compare and string compare
bool node_number_compare(const Node *a, const Node *b)
{
   return a->number < b->number; 
}

bool node_string_compare(const Node *a, const Node *b)
{
	return a->string < b->string;
}

