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

    Edge(Node *src, Node *snk, int cap) : source(src), sink(snk), capacity(cap), flow(0), reverse(nullptr) {}

    int residual_capacity() const { return capacity - flow; }
};

class Node {
public:
    std::string id;
    std::vector<Edge*> edges;
    explicit Node(const std::string &id) : id(id) {}

    void add_edge(Edge *edge) { edges.push_back(edge); }
};

class Graph {
private:
    using NodePtr = Node*;
    using EdgePtr = Edge*;
    using NodeMap = std::unordered_map<std::string, NodePtr>;

    NodeMap nodes;

public:
    Graph() {}
    ~Graph() {
        for (auto &[id, node] : nodes) delete node;
    }

    Node* add_node(const std::string &id) {
        if (nodes.find(id) == nodes.end()) {
            nodes[id] = new Node(id);
        }
        return nodes[id];
    }

    Edge* add_edge(const std::string& src_id, const std::string& snk_id, int cap) {
        Node *source = add_node(src_id);
        Node *sink = add_node(snk_id);
        Edge *edge = new Edge(source, sink, cap);
        Edge *reverse_edge = new Edge(sink, source, 0);

        edge->reverse = reverse_edge;
        reverse_edge->reverse = edge;

        source->add_edge(edge);
        sink->add_edge(reverse_edge);

        return edge;
    }

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

                if (parent.find(vertex) == parent.end() && edge->residual_capacity() > 0) {
                    parent[vertex] = edge;
                    if (vertex == sink) return true;
                    queue.push(vertex);
                }
            }
        }
        return false;
    }

    int edmonds_karp(const std::string &src_id, const std::string &snk_id, std::vector<int>& dice_order) {
        Node* source = nodes[src_id];
        Node* sink = nodes[snk_id];
        std::unordered_map<Node*, Edge*> parent;
        int max_flow = 0;
        dice_order.clear();

        while (bfs(source, sink, parent)) {
            int path_flow = INT_MAX;
            for (Node* v = sink; v != source; v = parent[v]->source) {
                path_flow = std::min(path_flow, parent[v]->residual_capacity());
            }
            for (Node* v = sink; v != source; v = parent[v]->source) {
                Edge* edge = parent[v];
                edge->flow += path_flow;
                edge->reverse->flow -= path_flow;
                
                // Only add dice indices (ensure it’s not "Source" or "Sink")
                if (edge->source->id != src_id && edge->sink->id != snk_id) {
                    try {
                        int die_index = std::stoi(edge->source->id);
                        dice_order.push_back(die_index);
                    } catch (const std::invalid_argument&) {
                        // Ignore non-integer node IDs like "Source" and "Sink"
                    }
                }
            }
            max_flow += path_flow;
        }

        return max_flow;
    }
};

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

    for (const auto& word : words) {
        Graph g;
        std::string source = "Source";
        std::string sink = "Sink";

        g.add_node(source);
        g.add_node(sink);

        // Connect source to each die with capacity 1
        for (size_t i = 0; i < dice.size(); ++i) {
            g.add_edge(source, std::to_string(i), 1);
        }

        // Connect each letter of each word to sink with capacity 1
        for (size_t i = 0; i < word.size(); ++i) {
            std::string letter_node = "L" + std::to_string(i);
            g.add_node(letter_node);
            g.add_edge(letter_node, sink, 1);

            // Connect dice to letters in the word if the die has the letter
            for (size_t j = 0; j < dice.size(); ++j) {
                if (dice[j].find(word[i]) != std::string::npos) {
                    g.add_edge(std::to_string(j), letter_node, 1);
                }
            }
        }

        // Calculate max flow for the word
        std::vector<int> dice_order;
        int max_flow = g.edmonds_karp(source, sink, dice_order);

        if (max_flow == word.size()) {
            // Sort dice order and output in the required format
            std::sort(dice_order.begin(), dice_order.end());
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