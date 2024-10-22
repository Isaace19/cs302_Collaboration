#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <map>
#include <algorithm> // For sorting edges

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

    void init_matrix(int num_vertex, const std::vector<std::vector<int>> &input_graph) {
        std::vector<std::string> vertex_ids;
        for (int i = 0; i < num_vertex; ++i) {
            vertex_ids.push_back(std::string(1, 'A' + i)); // Generates 'A', 'B', 'C', etc.
        }

        // Create edges based on input graph
        for (int i = 0; i < num_vertex; ++i) {
            for (int j = i + 1; j < num_vertex; ++j) {
                int weight = input_graph[i][j];
                if (weight > 0) {
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

    void Dijkstra(const std::string &start_node_id) {
        std::map<std::string, int> dist;           // Distance to each node from the start
        std::map<std::string, std::string> parent; // Parent of each node in the shortest path
        std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;

        // Initialize all distances to infinity and parents to an empty string (no parent)
        for (const auto &node_pair : Nodes) {
            dist[node_pair.first] = std::numeric_limits<int>::max();
            parent[node_pair.first] = "";
        }

        // Set the distance of the start node to 0 and push it to the priority queue
        dist[start_node_id] = 0;
        pq.push({0, start_node_id});

        // actual dijkstra's logic
        while (!pq.empty()) {
            std::string u = pq.top().second; 
            pq.pop();

            // Loop through all edges connected to node `u`, use ternary logic to deduce the source to sink
            for (Edge *edge : Nodes[u]->edges) {
                std::string v = (edge->sink->id == u) ? edge->source->id : edge->sink->id; // Get neighbor node
                int weight = edge->weight;

                // if the distance evaluate is not infinity and the distance + weight is less than the current processed vertex
                if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v}); // Push updated distance for `v` to priority queue
                }
            }
        }

        // Output the shortest distances from the start node to all other nodes
        for (const auto &pair : dist) {
            std::cout << "Distance to node " << pair.first << " is " << pair.second << std::endl;
        }

        // Reconstruct the shortest path for a specific target node (optional)
        std::string target_node_id = "some_target"; // Replace with an actual target node ID
        std::string path = target_node_id;
        std::string current_node = target_node_id;
        
        while (parent[current_node] != "") {
            path = parent[current_node] + " -> " + path;
            current_node = parent[current_node];
        }

        std::cout << "Shortest path to " << target_node_id << ": " << path << std::endl;
    }

};

int main(){
    // fix parsing logic
}
