/*
Name: Isaac Abella
Netid: iabella
Number: 000641840

Description: Analayze the game board and output all the possible disjoint sets that are greater 
than the minimum scoring size required to play superball.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <utility>
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

    // Map to track the size of each disjoint set component
    std::unordered_map<int, int> set_size;
    std::unordered_map<int, std::vector<std::pair<int, int> > > set_cells;
    std::unordered_map<int, bool> set_has_goal;

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
    // Union connected cells of the same color (right and down neighbors)
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int index = i * c + j;  // Current index in the one-dimensional array

            // Skip if the cell is empty or a goal
            if (board[index] == '.' || board[index] == '*')
                continue;

            int curr = Dset.Find(index);

            // Union right
            if (j + 1 < c && board[index] == board[index + 1]){
                int element1 = index + 1;
                int root1 = Dset.Find(element1);
                if(curr != root1){
                    Dset.Union(Dset.Find(index), Dset.Find(root1));
                }
            }

            // Union down
            if (i + 1 < r && board[index] == board[index + c]){
                int element1 = index + c;
                int root1 = Dset.Find(element1);
                if(curr != root1){
                    Dset.Union(Dset.Find(index), Dset.Find(root1));
                }
            }
        }
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int index = i * c + j;  // Current index in the one-dimensional array

            // Skip if the cell is empty or a goal
            if (board[index] == '.' || board[index] == '*')
                continue;

            int curr = Dset.Find(index);
            set_cells[curr].emplace_back(i, j);
            set_size[curr]++;


            // find the root of the current cell, and check if that cell is goal.
            // this evaluates to true if it's a goal, meaning that the connected component curr contains a goal cell
            if (goals[index]) {
                set_has_goal[curr] = true;
            }
        }
    }

    // print out scoring sets if they pass the criteria of MSS
    // fix logic to only print out when on a scoring set
    // Output valid scoring sets
    cout << "Scoring Sets:\n";
    for (unordered_map<int, vector<pair<int, int> > >::iterator it = set_cells.begin(); it != set_cells.end(); ++it) {
        int root = it->first;
        vector<pair<int, int> > &cells = it->second;


        // output all the valid scoring sets. process all cells, and then iterate the set_cells. which contains the disjoint sets.

        // for each disjoint set, it checks the size of the set_size[root] and whether it has a goal or not.
        if (set_size[root] >= mss && set_has_goal[root]) {
            // initialize the scoring cell to -1,-1 -- no goal cell here
            // for each cell as we iterate, where first is the row and second is the column, calculates the index in the goals array.
            // if a goal cell is found, assigns that coordinate to the scoring cell and breaks the loop.
            std::pair<int, int> scoring_cell(-1,-1);
            for (vector<pair<int, int> >::iterator cell_it = cells.begin(); cell_it != cells.end(); ++cell_it) {
                if (goals[cell_it->first * c + cell_it->second]) {
                    scoring_cell = *cell_it;
                    break;
                }
            }

            // Fallback: use the first cell if no goal is found -- worst case shouldn't happen...
            if (scoring_cell.first == -1) {
                scoring_cell = cells[0];
            }

            // output the Size of the score, the color, and the location on the board.
            char color = board[cells[0].first * c + cells[0].second];
            cout << "  Size: " << set_size[root]
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