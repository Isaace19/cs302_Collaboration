/*
*****************************
Name: Isaac Abella
Netid: iabella
ID: 000641840

Description: Reconstructing program to be more efficient, moving away from graph class implementation and using a 

Previous implementations became really hard to understand, so moving to a simpler implementaiton might yield more promising results
*****************************
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

// Node structure to be used in the priority queue
struct Node {
    int x, y, weight;
    Node(int x, int y, int w) : x(x), y(y), weight(w) {}

    // operator overload for the dijkstra's shortest path when we compare unvistied to current pq node
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

// Direction vectors for moving up, down, left, right
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// Reconstruct the path from end to start using the parent array
vector<pair<int, int>> reconstructPath(const vector<vector<pair<int, int>>>& parent, pair<int, int> start, pair<int, int> end) {
    vector<pair<int, int>> path;
    pair<int, int> current = end;
    
    while (current != start) {
        path.push_back(current);
        current = parent[current.first][current.second];
    }
    
    path.push_back(start);
    reverse(path.begin(), path.end());
    
    return path;
}

// Dijkstra's algorithm to find the shortest path
int dijkstra(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end, vector<pair<int, int>>& path) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX)); // Distance array - adjusted all starting values to infinity
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1})); // Parent array for path reconstruction
    priority_queue<Node, vector<Node>, greater<Node>> pq; // Min-heap priority queue
    
    // start with the source node and push that to the front of the pq. 
    dist[start.first][start.second] = grid[start.first][start.second];
    pq.push(Node(start.first, start.second, grid[start.first][start.second]));
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        int d = current.weight;
        int x = current.x;
        int y = current.y;
        
        // if we're already at the destination, than there is no need to traverse the matrix
        if (x == end.first && y == end.second) {
            path = reconstructPath(parent, start, end);
            return d; // Return the total distance when we reach the destination
        }
        
        // traverse in 4 directions (hence the i < 4) allows use to look in left, right, above, below locations

        // iterate over the cardinal directions that are constants above. 
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // bounds checking, if the new distance is less than the current stored distance, update the current distance and push it onto the pq.
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                int newDist = d + grid[nx][ny];
                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                    pq.push(Node(nx, ny, newDist));
                    parent[nx][ny] = {x, y}; // Set parent for path reconstruction
                }
            }
        }
    }
    
    return -1; // If no path is found
}

// Adjusted function to calculate the total cost, ignoring the destination tile
int calculateTotalCost(const vector<vector<int>>& grid, const vector<pair<int, int>>& path) {
    int total_cost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int x = path[i].first;
        int y = path[i].second;
        total_cost += grid[x][y]; // Only include the cost of leaving each tile
    }
    return total_cost;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int tile_count;
    cin >> tile_count;
    
    unordered_map<char, int> tile_cost; // Map to store tile costs
    
    for (int i = 0; i < tile_count; i++) {
        char tile_name;
        int cost;
        cin >> tile_name >> cost;
        tile_cost[tile_name] = cost;
    }

    int rows, cols;
    cin >> rows >> cols;

    vector<vector<int>> grid(rows, vector<int>(cols));
    vector<vector<char>> tile_grid(rows, vector<char>(cols));

    // Parse the map layout
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char tile;
            cin >> tile;
            grid[i][j] = tile_cost[tile]; // Convert tile symbol to its corresponding cost
            tile_grid[i][j] = tile;
        }
    }

    int start_x, start_y, end_x, end_y;
    cin >> start_x >> start_y >> end_x >> end_y;

    pair<int, int> start = {start_x, start_y};
    pair<int, int> end = {end_x, end_y};

    vector<pair<int, int>> path; // Vector to store the shortest path
    int total_weight = dijkstra(grid, start, end, path);

    if (total_weight == -1) {
        cout << "No path found." << endl;
    } else {
        // Calculate the total cost excluding the destination tile
        int adjusted_total_cost = calculateTotalCost(grid, path);
        
        // Print the total path cost
        cout << adjusted_total_cost << endl;

        // Print the path row by row
        for (auto& p : path) {
            cout << p.first << " " << p.second << endl;
        }
    }

    return 0;
}
