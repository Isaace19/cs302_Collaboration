#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <algorithm>


#include "disjoint.h"
using namespace std;

class Superball {
public:
    Superball(int argc, char **argv);
    void swap();
    void score();
    void sb_play();


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

void Superball::score(){

    // traverse the board again.
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int index = i * c + j;  // Current index in the one-dimensional array

            // Skip if the cell is empty or a goal
            if (board[index] == '.' || board[index] == '*')
                continue;
        }
    }
}

void Superball::swap(){
    int x1, x2, y1, y2;
    
}


void Superball::sb_play() {
    // check for empty cells and skip them when something can be scored, score it. 
    // when we can't score, we should aim to swap things. 
}

int main(int argc, char **argv) {
    Superball s(argc, argv);
    return 0;
}