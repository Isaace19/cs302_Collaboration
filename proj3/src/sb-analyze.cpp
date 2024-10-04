#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "disjoint.h"
using namespace std;

class Superball {
public:
    Superball(int argc, char **argv);
    void sb_analyze(); // New method to analyze the game board using disjoint sets

    int r, c, mss, empty;
    vector<int> board;
    vector<int> goals;
    vector<int> colors;

private:
    DisjointSetByRankWPC Dset; // Use the DisjointSetByRankWPC class
};

void usage(const char *s) {
    fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
    if (s != NULL) {
        fprintf(stderr, "%s\n", s);
    }
    exit(1);
}

Superball::Superball(int argc, char **argv) : Dset(0) {  // Initialize the disjoint set with r*c elements
    int i, j;
    string s;

    if (argc != 5)
        usage(NULL);

    if (sscanf(argv[1], "%d", &r) == 0 || r <= 0)
        usage("Bad rows");
    if (sscanf(argv[2], "%d", &c) == 0 || c <= 0)
        usage("Bad cols");
    if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0)
        usage("Bad min-score-size");

    colors.resize(256, 0);

    for (i = 0; i < strlen(argv[4]); i++) {
        if (!isalpha(argv[4][i]))
            usage("Colors must be distinct letters");
        if (!islower(argv[4][i]))
            usage("Colors must be lowercase letters");
        if (colors[argv[4][i]] != 0)
            usage("Duplicate color");
        colors[argv[4][i]] = 2 + i;
        colors[toupper(argv[4][i])] = 2 + i;
    }

    board.resize(r * c);
    goals.resize(r * c, 0);

    empty = 0;

    for (i = 0; i < r; i++) {
        if (!(cin >> s)) {
            fprintf(stderr, "Bad board: not enough rows on standard input\n");
            exit(1);
        }
        if (s.size() != c) {
            fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
            exit(1);
        }
        for (j = 0; j < c; j++) {
            if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
                fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
                exit(1);
            }
            board[i * c + j] = s[j];
            if (board[i * c + j] == '.')
                empty++;
            if (board[i * c + j] == '*')
                empty++;
            if (isupper(board[i * c + j]) || board[i * c + j] == '*') {
                goals[i * c + j] = 1;
                board[i * c + j] = tolower(board[i * c + j]);
            }
        }
    }
    Dset = DisjointSetByRankWPC(r * c);
}

void Superball::sb_analyze() {
    // Map to track the size of each disjoint set component
    std::unordered_map<int, int> set_size;
    std::unordered_map<int, std::vector<std::pair<int, int> > > set_cells;

    // Union connected cells of the same color (right and down neighbors)
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int index = i * c + j;  // Current index in the one-dimensional array

            // Skip if the cell is empty or a goal
            if (board[index] == '.' || board[index] == '*')
                continue;

            int curr = Dset.Find(index);


            // Union right neighbor if it exists and has the same color
            if (j + 1 < c && board[index] == board[index + 1]){
                int element1 = index + 1;
                int root1 = Dset.Find(element1);
                if(curr != root1){
                    Dset.Union(Dset.Find(curr), Dset.Find(root1));
                }
            }

            // Union down neighbor if it exists and has the same color
            if (i + 1 < r && board[index] == board[index + c]){
                int element1 = index + c;
                int root1 = Dset.Find(element1);
                if(curr != root1){
                    Dset.Union(Dset.Find(curr), Dset.Find(root1));
                }
            }
        }
    }

    // Analyze the connected components
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int index = i * c + j;
            if (board[index] == '.' || board[index] == '*')
                continue;

            int root = Dset.Find(index);  // Find the root of the set
            set_size[root]++;                     // Increment the size of the set
            set_cells[root].emplace_back(i, j);   // Track the cells in this set
        }
    }

    // print out scoring sets if they pass the criteria of MSS
    std::cout << "Scoring Sets:\n";
    for (std::unordered_map<int, std::vector<std::pair<int, int> > >::iterator it = set_cells.begin(); it != set_cells.end(); ++it) {
        int root = it->first;
        std::vector<std::pair<int, int> >& cells = it->second;  // Reference to the vector of cells for this set

        // Check if the set size meets the minimum scoring size requirement
        if (set_size[root] >= mss) {
            // get color and than get the scoring pair
            char color = std::tolower(board[cells[0].first * c + cells[0].second]);

            std::pair<int, int> scoring_cell = cells[0];

            // output
            std::cout << "  Size: " << set_size[root]
                      << "  Char: " << color
                      << "  Scoring Cell: " << scoring_cell.first << "," << scoring_cell.second << "\n";
        }
    }

}

int main(int argc, char **argv) {
    Superball s(argc, argv);
    s.sb_analyze();  // Call the analyze function to union sets and output scoring sets
    return 0;
}