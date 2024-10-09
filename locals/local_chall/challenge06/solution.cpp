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

    // create a set of indegrees and verticies for our directed graph in order to run a topological sort

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

    // Helper function to find or create nodes by their id
    Node *initialize_node(const std::string &id)
    {
        if (Nodes.find(id) == Nodes.end())
        {
            Nodes[id] = new Node(id);
        }
        return Nodes[id];
    }

    // undirected edge between source and sink
    void add_Edges(const std::string &source_id, const std::string &sink_id, int weight = 0)
    {
        Node *source = initialize_node(source_id);
        Node *sink = initialize_node(sink_id);

        Edge *edge = new Edge(source, sink, weight);
        source->edges.push_back(edge);
        sink->edges.push_back(edge);
        Edges.push_back(edge);
    }

    // modify a dijkstra algorithm to be a prim's algorithm
    void Prim_Alg(const std::string source_id){
        std::unordered_map<Node *, int> distances;

        auto compare = [](std::pair<Node *, int>&a, std::pair<Node *, int >&b){
            return a.second > b.second:
        }
        // while this looks disgusting, this is a priority queue of a node with an edge, and a vector list of all nodes and edges, and a function to compare the node edges 
        std::priority_queue<std::pair<Node *, int>, std::vector<std::pair<Node *, int>, std::function<bool(std::pair<Node *, int > &, std::pair<Node*, int> &)>> pq(compare);
        
        // set the distances of everything to infinity since you don't know the actual distances, these will update
        for(std::unordered_map<std::string, Node*>::iterator it = Nodes.begin(), it != Nodes.end(); ++it){
            distance[it->second] = std::numeric_limits<int>::max();
        }

        // start from source and calc(slang for calculate )distances
        Node *source = Nodes[source_id];
        distances[source] = 0;

        // set the source to new distances
        pq.push_back(std::make_pair<source, 0>);

        while(!pq.empty()){
            //acquire the node with the smallest distance, which is the top of the priority queue using .top()
            std::pair<Node*, int> curr_pair = pq.top();
            Node *curr = curr_pair.first;
            int curr_distance = curr_pair.second;
            pq.pop();

            if(curr_distance > distances[curr]){
                
            }
        }
    }


};

// Main Execution
int main(int argc, char *argv[])
{
    return (0);
}