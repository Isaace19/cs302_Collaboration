/*
Name: Isaac Abella
Netid: iabella
Number: 000641840

Description: Analayze the game board and output all the possible disjoint sets that are greater 
than the minimum scoring size required to play superball.

Than print out SCORE if score vector is full, if not, generate random cells and swap them around.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <ctime>

#include "disjoint.h"
using namespace std;


// create global variable of cell1 and cell2 to bypass c++ syntax
std::pair<int, int> cell1(-1,-1);
std::pair<int, int> cell2(-1,-1);

class Superball {
public:
    Superball(int argc, char **argv);
    void sb_traverse();  // Generates disjoint sets of connected components.
    void sb_analyze();   // Identifies the scoring zones.

    void sb_score(std::pair<int, int> cell);    
    void sb_swap(std::pair<int, int>cell1, std::pair<int, int>cell2);
    void sb_play();



    // make public DSs from SB analyze for our scoring algorithm
    std::unordered_map<int, int> set_size;
    std::unordered_map<int, std::vector<std::pair<int, int> > > set_cells;
    std::unordered_map<int, bool> set_has_goal;

    int r, c, mss, empty;
    vector<int> board;
    vector<int> goals;
    vector<int> colors;
    vector<std::pair<int, int> > scoring_sets;  // Holds scoring cells to target.

private:
    DisjointSetByRankWPC Dset;
    int largest_dset(int& second);
    bool eval(int idx1, int idx2); // evaluates whether a good swap can be made based on our largest DSET object's SET ID;
};

void usage(const char *s) {
    fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
    if (s != NULL) {
        fprintf(stderr, "%s\n", s);
    }
    exit(1);
}

// Constructor initializes board parameters and reads the input.
Superball::Superball(int argc, char **argv) : Dset(0) {
    int i, j;
    string s;

    if (argc != 5) usage(NULL);

    if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
    if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
    if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

    colors.resize(256, 0);
    for (i = 0; i < strlen(argv[4]); i++) {
        if (!isalpha(argv[4][i]) || !islower(argv[4][i]) || colors[argv[4][i]] != 0) {
            usage("Colors must be distinct lowercase letters.");
        }
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
            if (board[i * c + j] == '.' || board[i * c + j] == '*') empty++;
            if (isupper(board[i * c + j]) || board[i * c + j] == '*') {
                goals[i * c + j] = 1;
                board[i * c + j] = tolower(board[i * c + j]);
            }
        }
    }
    Dset = DisjointSetByRankWPC(r * c);
}

void Superball::sb_analyze() {
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
            scoring_sets.push_back(scoring_cell); // score all possible scoring sets in a vector...
        }
    }
}

int Superball::largest_dset(int& second){
    // initialize DSET IDS we want to find and store to, -1 makes them invalid entries
    int largest = -1, Slargest = -1;
    int max_size = 0, SMAx_size = 0; // initialize the sizes of the largest and second largest to 0, now compare and update

    // go through the set_size unordered map so we can determine the largest dset objects generated
    for(unordered_map<int, int>::iterator set_it = set_size.begin(); set_it != set_size.end(); ++set_it){
        // retrieve the ID and SIZE of the current DSET
        int set_id = set_it -> first;
        int size = set_it -> second;

        if(size > max_size){
            Slargest = largest;
            SMAx_size = max_size;

            largest = set_id;
            max_size = size;
            // if not largest, than compare to the second largest 
        }else if(size > SMAx_size){
            Slargest = set_id;
            SMAx_size = size;
        }
    }
    return largest;
}

bool Superball::eval(int idx1, int idx2){
    // this should check if the swap potential is good or not for sb_swap.

    // swap, analyze, compare with largest and second largest, and return a true or false?
    std::swap(board[idx1], board[idx2]); // swap the indexes

    sb_analyze();
    // determine if the largest or second largest increases

    int new_largest = -1;
    int new_slargest = -1;
    largest_dset(new_largest);

    bool is_good = (set_size[new_largest] > set_size[idx1] || set_size[new_largest] > set_size[idx2]);

    std::swap(board[idx1], board[idx2]); // have to revert the swap in order to not break the program
    return is_good;
}


// Score a specific cell.
void Superball::sb_score(std::pair<int, int> cell) {
    std::cout << "SCORE " << cell.first << " " << cell.second << std::endl;
}

// Swap two cells on the board. -- Improve with global access to sb_analyze data
void Superball::sb_swap(std::pair<int, int>cell1, std::pair<int, int>cell2) {
    sb_analyze();

    // update to find the best smart swap;
    std::pair<int, int> smart_swap(-1,-1);
    
    // find the largest and second largest DSETs
    int second = -1;
    int largest = largest_dset(second);

    // iterate the the cells form sb_analyze to calculate the best swaps based on largest and second largest DSETs.
    vector<std::pair<int, int> >& largest_set_cell = set_cells[largest]; // store the largest set ID into a std::vector pair in order to traverse. 
    if(largest != -1 && set_size[largest] > 1){
        // check all the cells in the largest set. 
        for(size_t i = 0; i < largest_set_cell.size(); ++i){
            for(size_t j = 0; j < largest_set_cell.size(); ++j){
                // traverse the vector and grab the IDs and store in a first and second cell to access location
                int idx1 = largest_set_cell[i].first * c + largest_set_cell[i].second;
                int idx2 = largest_set_cell[j].first * c + largest_set_cell[j].second;   

                // use this information to see if a swap is good or not
                // motive -- aim to swap elements of the same color to the largest DSET or Second largest DSET, if not, swap randomly and analyze again.
                if(eval(idx1, idx2)){
                    // execute our smart swap
                    smart_swap = std::make_pair(idx1, idx2);
                    break; // now that we have a new swap, don't continue;
                }
            }
        }

        // now check the second largest DSET object

        if(smart_swap.first == -1 && second != -1){
            vector<std::pair<int, int> >& Slargest_set_cell = set_cells[second];
            for(size_t i = 0; i < Slargest_set_cell.size(); ++i){
                for(size_t j = 0; j < Slargest_set_cell.size(); ++j){
                    // traverse the vector and grab the IDs and store in a first and second cell to access location
                    int idx1 = Slargest_set_cell[i].first * c + Slargest_set_cell[i].second;
                    int idx2 = Slargest_set_cell[j].first * c + Slargest_set_cell[j].second;   

                    // use this information to see if a swap is good or not
                    // motive -- aim to swap elements of the same color to the largest DSET or Second largest DSET, if not, swap randomly and analyze again.
                    if(eval(idx1, idx2)){
                        // execute our smart swap
                        smart_swap = std::make_pair(idx1, idx2);
                        break; // now that we have a new swap, don't continue;
                    }
                }
            }
        }

        // if the smart_swap was found, than we can execute the actual swap
        if(smart_swap.first != -1 && smart_swap.second != 1){
            std::pair<int, int> cell1, cell2;

            // creates the cell objects
            cell1 = std::make_pair(smart_swap.first / c, smart_swap.first % c);
            cell2 = std::make_pair(smart_swap.second / c, smart_swap.second % c);

            // execute the swap
            std::swap(board[cell1.first * c + cell1.second], board[cell2.first * c + cell2.second]);
            std::cout << "SWAP " << cell1.first << " " << cell1.second << " "
                      << cell2.first << " " << cell2.second << std::endl;
        }else{
            // means this shit did not work and we're just gonna do a random swap because idk lol
            std::pair<int, int> cell1, cell2;
            // Find two different cells to swap. -- Generate two random cell locations
            do {
                cell1 = std::make_pair(rand() % r, rand() % c);
            } while (board[cell1.first * c + cell1.second] == '.' || board[cell1.first * c + cell1.second] == '*');

            do {
                cell2 = std::make_pair(rand() % r, rand() % c);
            } while ((cell1 == cell2) || (board[cell2.first * c + cell2.second] == '.') || (board[cell2.first * c + cell2.second] == '*'));

            // swap
                std::swap(board[cell1.first * c + cell1.second], board[cell2.first * c + cell2.second]);
                std::cout << "SWAP " << cell1.first << " " << cell1.second << " "
                         << cell2.first << " " << cell2.second << std::endl;
        }
    }
}

void Superball::sb_play() {
    sb_analyze();  
    // if there is a scoring set, output that score:
    if(!scoring_sets.empty()){
        sb_score(scoring_sets.front());
    }else{
        sb_swap(cell1, cell2);
    }
}


int main(int argc, char **argv) {
    Superball s(argc, argv);
    s.sb_play();
    return 0;
}
