/*
 * Name: Isaac Abella
 * Netid: iabella
 * ID #: 000641840
 * 
 * Program Name: Worddice.cpp
 * Program Description - take in input dice, check against a list of available words possible
 * However, this challenge must be done by only using 1 word on each dice only. So even if
 * a dice contains multiple letters that could form the desired word, we can only use it once.
 *
 * */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <algorithm>
#include <limits.h>

class Node;
class Edge;
class Edge {
public:
    Node *source;
    Node *sink;
    int capacity;
    int flow;
    Edge *reverse;

    // redefine the edge objects to contain the source, sink, the capacity beteween each edge, and a reverse pointer to track residual paths
    Edge(Node *src, Node *snk, int cap) : source(src), sink(snk), capacity(cap), flow(0), reverse(nullptr) {}

    // residual capacity is just the capacity value of each edge subtracted by the flow that is pushed through it when using bfs
    int residual_capacity() const { return capacity - flow; }
};

// this is used to contain the adjacency list with unique identifiers for each incoming edge
class Node {
public:
    std::string id;
    std::vector<Edge*> edges;
    explicit Node(const std::string &id) : id(id) {}

    void add_edge(Edge *edge) { edges.push_back(edge); }
};

// construct a graph structure of node objects with edges connecting them
class Graph {
private:
    using NodePtr = Node*;
    using EdgePtr = Edge*;
    // map a node string to a node pointer for lookups
    using NodeMap = std::unordered_map<std::string, NodePtr>;
    NodeMap nodes;
public:
    Graph() {}
    ~Graph() {
        for (auto &[id, node] : nodes) delete node;
    }

    // add in node if it doesn't already exist in the graph
    Node* add_node(const std::string &id) {
        if (nodes.find(id) == nodes.end()) {
            nodes[id] = new Node(id);
        }
        return nodes[id];
    }

    // add the edges between nodes as usual, but this time include a reverse edge for tracking residual flow.
    Edge* add_edge(const std::string& src_id, const std::string& snk_id, int cap) {
        Node *source = add_node(src_id);
        Node *sink = add_node(snk_id);
        Edge *edge = new Edge(source, sink, cap);
        Edge *reverse_edge = new Edge(sink, source, 0);

        // attach the reverse edge to it's respective edge object for residual calculations. Should initialize to 0
        edge->reverse = reverse_edge;
        reverse_edge->reverse = edge;

        source->add_edge(edge);
        sink->add_edge(reverse_edge);

        return edge;
    }
    // This BFS is practically the same code reused from challenge04, just updated to account for the residual capacity in each edge between node objects

    // bfs required to employ edmounds karp algorithm, use a map data structure to store the Node and the edge leading to it. 
    // this is needed because tracking the node will allow us to back track each residual path. 

    // BFS is used to find all valid paths in the graph constructed, than we use the edmound's karp to see the max flow through each path possible.
    bool bfs(Node *source, Node *sink, std::unordered_map<Node*, Edge*>& parent) {
        std::queue<Node *> queue;
        queue.push(source);
        parent.clear();
        parent[source] = nullptr;

        while (!queue.empty()) {
            Node* unvisited = queue.front();
            queue.pop();
            for (Edge *edge : unvisited->edges) {
                Node *vertex = edge->sink;
                
                // if the vertex stored and it's edge have a residual capacity greater than 0, than there is a path from source to sink 
                // this should be recorded in the queue. 
                if (parent.find(vertex) == parent.end() && edge->residual_capacity() > 0) {
                    parent[vertex] = edge;
                    if (vertex == sink) return true;
                    queue.push(vertex);
                }
            }
        }
        // return false if no path exists.
        return false;
    }

    int edmonds_karp(const std::string &src_id, const std::string &snk_id, std::vector<int>& dice_order, int word_length) {
        Node* source = nodes[src_id];
        Node* sink = nodes[snk_id];
        std::unordered_map<Node*, Edge*> parent;
        int max_flow = 0;
        
        // Create an ordered vector to store dice indices for each letter in the word
        dice_order.assign(word_length, -1);  // Initialize with -1 for clarity
        // this solves the problem of path finding not being in the right order. By indexing them as soon as we start, this solves the problem. 
        
        // run BFS to find all the possible paths, at the same time we are pushing flow through each path to grab the residual flow
        while (bfs(source, sink, parent)) {
            int path_flow = INT_MAX;

            // Traverse the path from sink to source, find minimum residual capacity (path_flow)
            for (Node* v = sink; v != source; v = parent[v]->source) {
                path_flow = std::min(path_flow, parent[v]->residual_capacity());
            }
            // using the std::min should give the smallest path if the flow is set to an arbitrary high value

            // Traverse again to update flow values and record dice order
            // Go through again and update all the flow values, as we traverse record the order traversed.
            // recording the indicies as you traverse here gives the proper order of the dice indicies when storing them into the DS>
            for (Node* v = sink; v != source; v = parent[v]->source) {
                Edge* edge = parent[v];
                // as we update the path flow, we have to subtract flow from the residual flow via the edge
                edge->flow += path_flow;
                edge->reverse->flow -= path_flow;

                // Only record the dice indices for letters in the word, exclude source/sink since those are starting strings we set
                if (edge->source->id != src_id && edge->sink->id != snk_id) {
                    try {
                        int die_index = std::stoi(edge->source->id);
                        int letter_position = std::stoi(edge->sink->id.substr(1)); // Extract letter position
                        dice_order[letter_position] = die_index;
                    } catch (const std::invalid_argument&) {
                        // Ignore non-integer node IDs
                    }
                }
            }
            max_flow += path_flow;
        }

        return max_flow;
    }
};

// Builds the graph structure for each word to check if it can be spelled with the dice
void build_graph_for_word(Graph& g, const std::vector<std::string>& dice, const std::string& word) {
    std::string source = "Source";
    std::string sink = "Sink";

    g.add_node(source);
    g.add_node(sink);

    // Connect the source to the all the dice as shown in the representation picture
    for (size_t i = 0; i < dice.size(); ++i) {
        g.add_edge(source, std::to_string(i), 1);
    }

    // Connect each letter of each word to the sink as shown in the representation picture
    for (size_t i = 0; i < word.size(); ++i) {
        std::string letter_node = "L" + std::to_string(i);
        g.add_node(letter_node);
        g.add_edge(letter_node, sink, 1);

        // connect the letter dice to the word dice and construct the graph
        for (size_t j = 0; j < dice.size(); ++j) {
            if (dice[j].find(word[i]) != std::string::npos) {
                g.add_edge(std::to_string(j), letter_node, 1);
            }
        }
    }
}

// simple function that grabs the files listed in the command line and parses their input into the respective vectors found in main. 
void read_input(const std::string& diceFile, const std::string& wordsFile, std::vector<std::string>& dice, std::vector<std::string>& words) {
    std::ifstream diceStream(diceFile);
    std::ifstream wordsStream(wordsFile);

    std::string line;
    while (std::getline(diceStream, line)) {
        dice.push_back(line);
    }
    while (std::getline(wordsStream, line)) {
        words.push_back(line);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./worddice <dice> <words>" << std::endl;
        return 1;
    }

    std::vector<std::string> dice;
    std::vector<std::string> words;
    read_input(argv[1], argv[2], dice, words);

    // build the graph object
    for (const auto& word : words) {
        Graph g;
        build_graph_for_word(g, dice, word);

        // store possible combinations as we run the max flow algorithm 
        std::vector<int> dice_order;
        int max_flow = g.edmonds_karp("Source", "Sink", dice_order, word.size());

        if (max_flow == word.size()) {
            // Print dice order directly in the correct sequence
            for (size_t i = 0; i < dice_order.size(); ++i) {
                if (i > 0) std::cout << ",";
                std::cout << dice_order[i];
            }
            std::cout << ": " << word << std::endl;
        } else {
            std::cout << "Cannot spell " << word << std::endl;
        }
    }

    return 0;
}