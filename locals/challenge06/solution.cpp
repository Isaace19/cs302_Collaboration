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

	void init_matrix(int num_vertex, const std::vector<std::vector<int>> &input_graph){
		// initialize verticies and converts them to alphanumeric names 
		std::vector<std::string> vertex_ids;
		for(int i = 0; i < num_vertex; ++i){
			vertex_ids.push_back(std::string(1, 'A' + i)); // Generates the IDS to A, B, C
		}

		// create the actual nodes 
		for(int i = 0; i < num_vertex; ++i){
			for(int j = i + 1; j < num_vertex; ++j){
				int weight = input_graph[i][j];
				if(weight > 0){ // ignore -1 with no correction
					add_Edges(vertex_ids[i], vertex_ids[j], weight);
				}
			}
		}
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
	void print_initial(const std::vector<std::vector<int>>& input_graph){
		std::cout << "DEBUGGING: TESTING INPUT " << std::endl;
			
		int V = input_graph.size(); // is the number of verticies in the graph
		std::cout << V << std::endl;		
		for(int i = 0; i < V; ++i){
			for(int j = 0; j < V; ++j){
				// print out the input again
				if(input_graph[i][j] == -1){
					std::cout << "-1";
				}else{
					std::cout << input_graph[i][j] << " ";
				}
			}
			std::cout << std::endl; // newline to next row
		}
		std::cout << std::endl; // newline

	}


    bool compare(const std::pair<Node *, int>&a, const std::pair<Node *, int>&b) {
        return a.second > b.second;
    }

	 bool dijkstra(const std::string &start_id)
    {
    	std::unordered_map<std::string, int> distances;
		std::unordered_map<std::string, bool> visited;
		std::priority_queue<std::pair<int, Node *>, std::vector<std::pair<int, Node *>>, std::greater<std::pair<int, Node *>>> pq;
		
		// initialize all distances to infinity and the visited nodes to false
		for(const auto &pair : Nodes){
			distances[pair.first] = std::numeric_limits<int>::max(); // set to infinity
			visited[pair.first] = false;     // set visited to false
		}
		// set the starting node to 0
		distances[start_id] = 0;
		pq.push({0, Nodes[start_id]}); // insert the starting node into the pq
		
		while(!pq.empty()){
			
		}
	};

    // modify a dijkstra algorithm to be a prim's algorithm
    void Prim(const std::string source_id){
        
    }
};

// Main Execution
int main(int argc, char *argv[])
{
	int V;
	std::cin >> V;

	std::vector<std::vector<int>> input_graph(V, std::vector<int>(V));	
	
	for(int i = 0; i < V; ++i){
		for(int j = 0; j < V; ++j){
			std::cin >> input_graph[i][j];
		}
	}

	undirgraph g;
//	g.print_initial(input_graph); // this is the debugging the input
	g.init_matrix(V, input_graph);
	g.print();
	return (0);
}
