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
#include <vector>
#include <unordered_map>

#include "disjoint.h"
using namespace std;

class Superball {
public:
    Superball(int argc, char **argv);
    void sb_analyze(); // Method to analyze the game board using disjoint sets

    int r, c, mss, empty;
    vector<int> board;
    vector<int> goals;
    vector<int> colors;

    // Maps to track the size and properties of each disjoint set
    unordered_map<int, int> set_size;
    unordered_map<int, vector<pair<int, int> > > set_cells;
    unordered_map<int, bool> set_has_goal;

private:
    DisjointSetByRankWPC Dset; // Disjoint set for handling the sets
};

void usage(const char *s) {
    fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
    if (s != nullptr) {
        fprintf(stderr, "%s\n", s);
    }
    exit(1);
}

Superball::Superball(int argc, char **argv) : Dset(0) {
    if (argc != 5)
        usage(nullptr);

    // Parse inputs
    if (sscanf(argv[1], "%d", &r) == 0 || r <= 0)
        usage("Bad rows");
    if (sscanf(argv[2], "%d", &c) == 0 || c <= 0)
        usage("Bad cols");
    if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0)
        usage("Bad min-score-size");

    colors.resize(256, 0);

    // Initialize color mapping
    for (int i = 0; argv[4][i] != '\0'; i++) {
        if (!isalpha(argv[4][i]) || !islower(argv[4][i]))
            usage("Colors must be distinct lowercase letters");
        if (colors[argv[4][i]] != 0)
            usage("Duplicate color");
        colors[argv[4][i]] = i + 2;
        colors[toupper(argv[4][i])] = i + 2;
    }

    board.resize(r * c);
    goals.resize(r * c, 0);
    empty = 0;

    // Read the board from input
    string s;
    for (int i = 0; i < r; i++) {
        if (!(cin >> s)) {
            fprintf(stderr, "Bad board: not enough rows on standard input\n");
            exit(1);
        }
        if (s.size() != c) {
            fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
            exit(1);
        }
        for (int j = 0; j < c; j++) {
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

    Dset = DisjointSetByRankWPC(r * c); // Initialize the disjoint set
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
            if (j + 1 < c && board[index] == board[index + 1]) {
                int element1 = index + 1;
                int root1 = Dset.Find(element1);
                if (curr != root1) {
                    Dset.Union(Dset.Find(index), Dset.Find(root1));
                }
            }

            // Union down
            if (i + 1 < r && board[index] == board[index + c]) {
                int element1 = index + c;
                int root1 = Dset.Find(element1);
                if (curr != root1) {
                    Dset.Union(Dset.Find(index), Dset.Find(root1));
                }
            }
        }
    }

    // Assign cells to their root sets and calculate sizes
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int idx = i * c + j;
            if (board[idx] == '.' || board[idx] == '*') continue;

            int curr = Dset.Find(idx);
            set_cells[curr].emplace_back(i, j);
            set_size[curr]++;
            if (goals[idx]) {
                set_has_goal[curr] = true;
            }
        }
    }

    // Output the valid scoring sets that meet the minimum score size
    for (const auto& entry : set_cells) {
        int root = entry.first;
        const auto& cells = entry.second;

        if (set_size[root] >= mss && set_has_goal[root]) {
            std::pair<int, int> scoring_cell(-1, -1);
            for (const auto& cell : cells) {
                if (goals[cell.first * c + cell.second]) {
                    scoring_cell = cell;
                    break;
                }
            }

            if (scoring_cell.first == -1) {
                scoring_cell = cells[0];
            }

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
