/*
*****************************
Name: Isaac Abella
Netid: iabella
ID: 000641840

Description: Create a program that generates map for the dijkstra's cpp to create the map 

create a n x n matrix given our random generated values. 
*****************************
*/

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
#include <fstream>  // For file output

// Generate tile weights as a map
std::map<char, int> generate_tile_weights() {
    return {{'f', 3}, {'g', 1}, {'G', 2}, {'h', 4}, {'m', 7}, {'r', 5}};
}

// Generate a random n x n matrix based on the tile set
std::vector<std::vector<char>> generate_map_layout(int map_size, const std::string& tile_set) {
    std::vector<std::vector<char>> map_layout(map_size, std::vector<char>(map_size));
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < map_size; ++j) {
            map_layout[i][j] = tile_set[rand() % tile_set.size()];
        }
    }
    return map_layout;
}

// Write output to a specified file
void write_to_file(const std::string& file_name, int map_size, 
                   const std::map<char, int>& tile_weights, 
                   const std::vector<std::vector<char>>& map_layout, 
                   const std::pair<int, int>& start, 
                   const std::pair<int, int>& end) {
    std::ofstream out_file(file_name);

    if (!out_file.is_open()) {
        std::cerr << "Failed to open file for output.\n";
        return;
    }

    // Write the number of tiles and their weights
    out_file << tile_weights.size() << "\n";
    for (const auto& pair : tile_weights) {
        out_file << pair.first << " " << pair.second << "\n";
    }

    // Write the map dimensions
    out_file << map_size << " " << map_size << "\n";

    // Write the map layout
    for (const auto& row : map_layout) {
        for (char tile : row) {
            out_file << tile << " ";
        }
        out_file << "\n";
    }

    // Write the runner's start and end positions
    out_file << start.first << " " << start.second << "\n";
    out_file << end.first << " " << end.second << "\n";

    out_file.close();
    std::cout << "Map generated and written to '" << file_name << "'.\n";
}

// Function to generate a map of a given size and write it to a file
void generate_random_map(int map_size, const std::string& file_name) {
    srand(time(0));  // Seed the random number generator

    // Get the tile weights
    std::map<char, int> tile_weights = generate_tile_weights();

    // Define the set of possible tiles
    std::string tile_set = "fghGmr";

    // Generate the random map layout
    std::vector<std::vector<char>> map_layout = generate_map_layout(map_size, tile_set);

    // Set starting position to (0, 0) and ending position to (map_size - 1, map_size - 1)
    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {map_size - 1, map_size - 1};

    // Write everything to the output file
    write_to_file(file_name, map_size, tile_weights, map_layout, start, end);
}

// Main function to generate maps for various sizes
int main() {
    // List of map sizes to generate
    std::vector<int> map_sizes = {10, 20, 50, 100, 200, 500, 1000};

    // Generate a map for each size and save it to a file
    for (int size : map_sizes) {
        std::string file_name = "map_" + std::to_string(size) + "x" + std::to_string(size) + ".txt";
        generate_random_map(size, file_name);
    }

    return 0;
}