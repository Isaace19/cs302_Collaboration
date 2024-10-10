/*
Challenge 06: Graph Paths

Name: Isaac Abella
Netid: iabella
Student #: 000641840

Description: given an input of an undirected graph tree, compute and output the corresponding minimum spanning tree
the minimum spanning tree will have the total edge of 10 and consist of: 

(A, C)
(B, C)
(C, E)
(D, E)
(D, F)
*/

// Solution: Convert the digraph from challenge04 into an undirected graph by adding in edges to both directions to turn
// the graph into a bidirectional edges.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <functional> // Required for std::function
#include <cctype> // alphanumeric converesion 



class Node; // use forward declaration to avoid compilation errors
class Edge
{
public:
    Node *source; // represents endpoint of edge 
    Node *sink;   // represents other endpoint of edge
    int weight;
    Edge(Node *n1, Node *n2, int w) : source(n1), sink(n2), weight(w) {}
};

// Class Node is the node containing the id of the current node and the incoming
// and outgoing edges that connect it to it's neighbors if possible.
class Node
{
public:
    std::string id;            // id is based on the source and sink
    std::vector<Edge *> edges; // convert to bidirectional edges
    Node(const std::string &id) : id(id) {}
};

class undirgraph
{
public:
    // We could make this an implementation without unordered map, but the memory mamagement
    // with manual pointers is rough/outdated. And the searching through a vector is linear.
    // Therefore using a map offers better mem. management and searching complexity.
    std::unordered_map<std::string, Node *> Nodes;
    std::vector<Edge *> Edges;

    // deconstructor -- memory management
    ~undirgraph()
    {
        for (Edge *edge : Edges)
        {
            delete edge;
        }
        for (auto &pair : Nodes)
        {
            delete pair.second;
        }
    }

    // create nodes given on their input -- modify the input to account for verticies and adjancey list. 
    Node *initialize_node(const std::string &id)
    {
        if (Nodes.find(id) == Nodes.end())
        {
            Nodes[id] = new Node(id);
        }
        return Nodes[id];
    }

    // undirected edge between source and sink -- modify to take in adjancey list and prim's algorithm
    void add_Edges(const std::string &source_id, const std::string &sink_id, int weight = 0)
    {
        Node *source = initialize_node(source_id);
        Node *sink = initialize_node(sink_id);

        Edge *edge = new Edge(source, sink, weight);
        source->edges.push_back(edge);
        sink->edges.push_back(edge);
        Edges.push_back(edge);
    }

    // compare Node A to B and return the greater than node. 
    bool compare(const std::pair<Node *, int>&a, const std::pair<Node *, int>&b) {
        return a.second > b.second;
    }

    // modify a dijkstra algorithm to be a prim's algorithm
    void Prim(const std::string source_id){        
        // use a heap to account for everything, will have to use multiple data structures
    }   
};

// Main Execution
int main(int argc, char *argv[])
{
    // perform bit ops to convert int V into proper alphanumeric conversion 
    undirgraph graphy;

    // the input of verticies to the list below it. // assume that these are A - Z. 
    // create an adjancey matrix, read into it with 2D matrix traversal

    int V;
    std::cin >> V;
    std::vector<std::vector<int>> graph(V, std::vector<int>(V));
    for(size_t i = 0; i < V; ++i){
        for(size_t j = 0; j < V; ++ j){
            std::cin >> graph[i][j];
            graphy.add_Edges(std::to_string(i), std::to_string(j));
        }
    }
    graphy.Prim("A");
    return (0);
}