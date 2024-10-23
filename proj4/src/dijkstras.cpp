/*
*****************************
Name: Isaac Abella
Collaboration with: Colton Coughlin
Netid: iabella
ID: 000641840

Description: Reconstructing program to be more efficient, moving away from graph class implementation and using a 

Previous implementations became really hard to understand, so moving to a simpler implementaiton might yield more promising results.

Things that I've changed for this version. Creating more efficient lookup algorithms and improving the data structures themselves
*****************************
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm> // For sorting edges
#include <memory>
#include <utility>

const int INFINITY = std::numeric_limits<int>::max();
typedef std::pair<int, int> Node;	    // stores the x,y coordinate of the node 
typedef std::pair<int, Node> pq_elm; // represents a pair in the priority queue for dijkstra's algorithmz 


// represent grid in moves of up, down, left, and right.
std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

inline int get_index(int row, int col, int width){
	return row * width +col; // grab the index of the current spot in the 2D matrix in order for fast lookup.
}

// create a dijkstra algorithm for the shortest path on the grid
void dijkstra(const std::vector<char>& map_layout, const std::unordered_map<char, int>& cost, int start_row, int start_col, int end_row, int end_col, int ROW, int COL){

	std::priority_queue<pq_elm, std::vector<pq_elm>, std::greater<pq_elm>> pq;
	std::vector<int> distance(ROW * COL, INFINITY); // set all nodes to infinity at initial start
	std::vector<Node> parent(ROW * COL, {-1,-1});
	
	int start_index = get_index(start_row, start_col, COL);
	int end_index = get_index(end_row, end_col, COL);

	pq.push({cost.at(map_layout[start_index]), {start_row, start_col}});
	distance[start_index] = cost.at(map_layout[start_index]);

	while(!pq.empty()){
		// access the smallest element in the priority queue, where the weight is held first in pq_elm, and than the Node is the second in the pair which contains the x and y (first and second)
		int current_cost = pq.top().first;
		int current_row = pq.top().second.first;
		int current_col = pq.top().second.second;
		pq.pop();

		int curr_index = get_index(current_row, current_col, COL);

		if (curr_index == end_index) {
            // Path reconstruction
            std::vector<Node> path;
            for (Node at = {end_row, end_col}; at != Node{-1, -1}; at = parent[get_index(at.first, at.second, COL)]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end()); // Reverse the path to get it from start to end
            
            // Output the result
            std::cout << distance[end_index] << "\n";
            for (const auto& p : path) {
                std::cout << p.first << " " << p.second << "\n";
            }
            return;
        }

		// traverse the neighbors
		for(const auto& dir : directions){
			// using the directions vector defined
			int new_row = current_row + dir.first;
			int new_col = current_col + dir.second;
			// this moves us up, down, left, right by assigning a shift in the current x and y axis

			if(new_row >= 0 && new_row < ROW && new_col >= 0 && new_col < COL){
				int new_index = get_index(new_row, new_col, COL);
				int new_cost = current_cost + cost.at(map_layout[new_index]);

				// if new path is found: update the distance matrix with the new cost of the current tile explored, and update the location x and y in the typedef
				if(new_cost < distance[new_index]){
					distance[new_index] = new_cost;
					// update the parent vector in order to build the reversal path
					parent[new_index] = {current_row, current_col};
					pq.push({new_cost, {new_row, new_col}});
				}
			}
		}
	}
	std::cout << "NO PATH IS FOUND.\n";	
}

int main(){
    // input optimization
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int TILES;
	std::cin >> TILES;

	// grab and store the tile costs form input
	std::unordered_map<char, int> cost;
	for(int i = 0; i < TILES; i++){
		char tile; 
		int value;
		std::cin >> tile >> value;
		cost[tile] = value;
	}

	// initialize map dimensions
	int ROW, COL;
	std::cin >> ROW >> COL;

	// turn the input into a flat 1D layout;
	std::vector<char> map_layout(ROW * COL);
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			std::cin >> map_layout[get_index(i, j, COL)];
		}
	}

	// grab the start and end positions
	int start_row, start_col, end_row, end_col;
	std::cin >> start_row >> start_col >> end_row >> end_col;

	// run the dijkstra algorithm
	dijkstra(map_layout, cost, start_row, start_col, end_row, end_col, ROW, COL);

	return 0;
}
