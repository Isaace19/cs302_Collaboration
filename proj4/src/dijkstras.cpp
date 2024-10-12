/*
Project 4: Dijkstra's Algorithm

Name: Isaac Abella
Netid: iabella
Student #: 000641840

Convert an incoming matrix file with a starting location, ending location, and map values and verticies, and than we can 
turn that matrix into an list and perform a dijkstra's shortest path algorithm on it.

First: grab and parse the input information properly. Than create an undirected edge centric list. 
Take that created list and perform a dijkstra traversal and shortest path calculation.

print out the total weight of the path that is found and the actual table after traversal. This is the path the runner took from
the starting location to the ending location, and the value of the dijkstra path is determined by the parsed input from the start of 
the program.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <cctype>

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

    // I'm creating a debugging output function in order to see what we're actually creating in the init_matrix and add_Edges
	void print(){
		for(const auto &node_pair : Nodes){
			Node *node = node_pair.second;
			std::cout << "Node " << node->id << " connects to:\n";
			for(Edge *edge : node->edges){
				std:: cout << " - Node " << edge->sink->id << " has a weight " << edge->weight << "\n";
			}
		}
	}

    // another debugging function to check if we're even reading in the distance table from input.txt properly
	void print_initial(const std::vector<std::vector<int>>& map_weight){
		std::cout << "DEBUGGING: TESTING INPUT " << std::endl;
			
		int V = map_weight.size(); // is the number of verticies in the graph
		std::cout << V << std::endl;		
		for(int i = 0; i < V; ++i){
			for(int j = 0; j < V; ++j){
				// print out the input again
				if(map_weight[i][j] == -1){
					std::cout << "-1";
				}else{
					std::cout << map_weight[i][j] << " ";
				}
			}
			std::cout << std::endl; // newline to next row
		}
		std::cout << std::endl; // newline
	}

    bool compare(const std::pair<Node *, int>&a, const std::pair<Node *, int>&b) {
        return a.second > b.second;
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

	void init_matrix(int row, int col, std::vector<std::vector<int>>& map_weights){
     
    }

    bool dijkstra(const std::string &start_id)
    {

	}

    // modify a dijkstra algorithm to be a prim's algorithm
    void Prim(const std::string source_id){

    }
};

// Main Execution
int main(int argc, char *argv[])
{
	return (0);
}
