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

    bool compare(const std::pair<Node *, int>&a, const std::pair<Node *, int>&b) {
        return a.second > b.second;
    }

    // modify a dijkstra algorithm to be a prim's algorithm
    void Prim(const std::string source_id){
        std::vector<Edge *> MST_EDGES;
        std::unordered_map<Node *, int> distance;
        std::unordered_map<Node *, Node *> parent;
        std::unordered_map<Node *, bool> INCLUDED_MST;
        int total_weight = 0;

        // initilaize all nodes to infinity distance
        for(std::unordered_map<std::string, Node *>::iterator it = Nodes.begin(); it != Nodes.end(); ++it){
            distance[it->second] = std::numeric_limits<int>::max();
            INCLUDED_MST[it->second] = false; // unvisited
        }

        Node *source = initialize_node(source_id);
        distance[source] = 0;
        parent[source] = nullptr;

        // create priority queue forest
        std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node *>>, std::greater<std::pair<int, Node*>>> pq;
        pq.push(std::make_pair(0, source));

        while(!pq.empty()){
            Node *unvisted = pq.top().second;
            pq.pop();

            if(INCLUDED_MST[unvisted]){
                continue;
            }
            // mark the current vertex as INCLUDED
            INCLUDED_MST[unvisted] = true;
            // now explore all adjacent nodes
            for(std::vector<Edge *>::iterator it = unvisted->edges.begin(); it != unvisted->edges.end(); ++it){
                Edge *edge = *it;
                Node *neighbor = (edge->source == unvisted) ? edge->sink : edge-> source;
                // if the vertex is not in the MSt, than there exists an edge from unvisted to vertex and the weight is smaller than our current key of vertex.
                if(!INCLUDED_MST[neighbor] && edge->weight < distance[neighbor]){
                    distance[neighbor] = edge->weight;
                    parent[neighbor] = unvisted;

                    pq.push(std::make_pair(edge->weight, neighbor));
                }
            }
        }
        // output the total MST
        std::cout << "OUTPUT...\n";
        for(std::unordered_map<Node *, Node *>::iterator it = parent.begin(); it != parent.end(); ++it){
            if(it->second != nullptr){
                std::cout << it->second->id << " -- " << it->first->id <<  "Weight: " << distance[it->first] << '\n';
                total_weight += distance[it->first];
            }
        }
        std::cout << " TOTAL WEIGHT: " << total_weight << '\n';
    }
};

// Main Execution
int main(int argc, char *argv[])
{
    int graph_number = 0;
    std::cin >> graph_number;

    for(int i = 0; i < graph_number; ++i){
        int n;
        std::cin >> n;

        undirgraph g;

        for(int row = 0; row < n; ++row){
            for(int col = 0; col < n; ++col){
                int weight;
                std::cin >> weight;
                if (weight != -1 && row != col) { // Exclude self-loops and -1 (no edge)
                    g.add_Edges(std::to_string(row), std::to_string(col), weight);
                }
            }
        }
        g.Prim("A");
    }
    return (0);
}