// Challenge 09: sequence alignment

/*
*****************************
Name: Isaac Abella
Netid: iabella
ID: 000641840

Description: Dynamic Programming Problem to solve a path finding problem

Solution: Use a recursive algorithm that traverses the path based on a criteria. 
*****************************
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

class solution{
    private:
        // implement scoring metrics
        const int INF = std::numeric_limits<int>::max();
        int match = 1;
        int mismatch = -1;  
        int gap = -1;

    public:
        int edit_distance(char a, char b){  
            if(a == b) return match;
            return mismatch;
        }

        int solve(const std::string input1, const std::string input2){
            int n = input1.size();
            int m = input2.size();

            std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
            // initialize table
            for(int i = 0; i <=n; ++i){
                dp[i][0] = i * gap;
            }
            for(int j = 0; j <=m; ++j){
                dp[0][j] = j * gap;
            }
            // fill in the table

            for(int i = 1; i <=n; ++i){
                for(int j = 1; j <=m; ++j){
                    if(input1[i - 1] == input2[j - 1]){
                        // base case: characters match
                        dp[i][j] = dp[i - 1][j - 1] + match;
                    }else{
                        // recursive solution: assign mismatch and gaps as you traverse the table
                        dp[i][j] = std::max({
                            dp[i - 1][j - 1] + mismatch, dp[i - 1][j] + gap, dp[i][j - 1] + gap
                        });
                    }
                }
            }
            return dp[n][m];
        }
};

int main(int argc, char *argv[]) {
    std::string input1, input2;
    std::cin >> input1 >> input2;

    solution sol;
    int score = sol.solve(input1, input2);
    std::cout << score << '\n';
    return 0;
}


