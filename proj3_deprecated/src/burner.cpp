#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <memory> // use for std::unique_ptr
#include <unordered_map>

#include "disjoint.h"
using namespace std;

#define talloc(type, num) (type *)malloc(sizeof(type) * (num))

// In order to have an augmented function of disjoint set to use the superball class, we can just make it a helper function.
// there are other ways such as generic templates or friendship, but this should be easy to implement in my opinion.
class Superball
{
public:
    Superball(int argc, char **argv);
    int r;
    int c;
    int mss;
    int empty;
    vector<int> board;
    vector<int> goals;
    vector<int> colors;

    // Polymorphism to overcome virtual abstract classes. Doing virtuals does not allow object declaration here.
    std::unique_ptr<DisjointSet> Dset;
    friend void Sb_analyze(Superball &s);
};

void usage(const char *s)
{
    fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
    if (s != NULL)
        fprintf(stderr, "%s\n", s);
    exit(1);
};

Superball::Superball(int argc, char **argv)
{
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

    for (i = 0; i < strlen(argv[4]); i++)
    {
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

    for (i = 0; i < r; i++)
    {
        if (!(cin >> s))
        {
            fprintf(stderr, "Bad board: not enough rows on standard input\n");
            exit(1);
        }
        if (s.size() != c)
        {
            fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
            exit(1);
        }
        for (j = 0; j < c; j++)
        {
            if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0)
            {
                fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
                exit(1);
            }
            board[i * c + j] = s[j];
            if (board[i * c + j] == '.')
                empty++;
            if (board[i * c + j] == '*')
                empty++;
            if (isupper(board[i * c + j]) || board[i * c + j] == '*')
            {
                goals[i * c + j] = 1;
                board[i * c + j] = tolower(board[i * c + j]);
            }
        }
    }

    // have to include disjoint set into this function for analyze to work properly
    // using the DisjoointSetByRankWPC, we can create a new disjointSetByRankWPC object of the size of the game baord r*c
    // than we can use this to take advantage of disjoint set header and it's functions.
    Dset = std::unique_ptr<DisjointSetByRankWPC>(new DisjointSetByRankWPC(r * c));
};
void Sb_analyze(Superball &s)
{
    std::unordered_map<int, int> set_size;                               // create a map to keep track of each set by the root
    std::unordered_map<int, std::vector<std::pair<int, int> > > set_cells; // creates a map to track cells belonging to each set


	std::cout << "Starting first traversal where we union together like colors...\n";
    // traverse game board and analyze it for all scoring options:
    for (int i = 0; i < s.r; ++i)
    {
        for (int j = 0; j < s.c; ++j)
        {
            int index = i * s.c * j; // One dimensional index of the game board

            // skip the empty cells or the empty goal cells by reading in the chars as we traverse -- Bounds Checking
            if (s.board[index] == '.' || s.board[index] == '*')
            {
                continue;
            }
            // take a look at the board and traverse and union all possible colors
            // look to the right:
            if (j + 1 < s.c && s.board[index] == s.board[index + 1])
            {
                int neighbor = index + 1;
                s.Dset->Union(s.Dset->Find(index), s.Dset->Find(neighbor));
            }
            // look to our left
            if (j - 1 >= s.c && s.board[index] == s.board[index - 1])
            {
                int neighbor = index - 1;
                s.Dset->Union(s.Dset->Find(index), s.Dset->Find(neighbor));
            }

            // look above
            if (i + 1 < s.r && s.board[index] == s.board[index + s.c])
            {
                int neighbor = index + s.c;
                s.Dset->Union(s.Dset->Find(index), s.Dset->Find(neighbor));
            }

            // look below
            if (i - 1 >= s.r && s.board[index] == s.board[index - s.c])
            {
                int neighbor = index - s.c;
                s.Dset->Union(s.Dset->Find(index), s.Dset->Find(neighbor));
            }
        }
    }

	std::cout << "Start Second Traversal to find all scoring sets...\n";
    // now do another traversal and start storing all the sets
    for (int i = 0; i < s.r; ++i)
    {
        for (int j = 0; j < s.c; ++i)
        {
            int index = i * s.c * j; // One dimensional index of the game board

            // skip the empty cells or the empty goal cells by reading in the chars as we traverse -- Bounds Checking
            if (s.board[index] == '.' || s.board[index] == '*')
            {
                continue;
            }

            // look at adjacent cells if they are the same with find, than union the neighbors together
            // check all directions of a cell, left, right, above, below for grouping

            int root = s.Dset->Find(index);
            set_size[root]++;
            set_cells[root].emplace_back(i, j); // store coordinates as pairs
        }
    }

    // Print out the possible scoring sets
    std::cout << "Scoring Sets: \n";
    for (const auto &pair : set_cells)
    {
        int root = pair.first;                                           // The root of the component
        const std::vector<std::pair<int, int> > &set_cells = pair.second; // The size of the component

        int size = set_cells.size();
        // Check if the size meets your scoring criteria
        if (size >= s.mss)
        {
            auto scoringCell = pair.second[0];                                        // Take the first cell for output
            char scoringChar = s.board[scoringCell.first * s.c + scoringCell.second]; // Get the character

            cout << "  Size: " << size << "  Char: " << scoringChar << "  Scoring Cell: " << scoringCell.first << "," << scoringCell.second << endl;
        }
    }
}

int main(int argc, char **argv)
{
    Superball *s;
    s = new Superball(argc, argv);

    // required memory management
    Sb_analyze(*s);
    delete s;

    return 0;
}