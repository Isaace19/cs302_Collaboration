// Challenge 02: Closest Numbers
// Name:  Isaac Abella
// NETID: iabella
// Email: iabella@vols.utk.edu

// Sort the pair of elements with the smallest difference between them if there are multiple, print all of them out. 
// Output in ascending order if there are multiple pairs that meet the sorting criteria.

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>


using namespace std;

// Function to find and print pairs with the smallest difference
void find_pair(const std::vector<int>& arr) {
    std::vector<int> result = arr;
    std::sort(result.begin(), result.end());

    int min_diff = INT_MAX; // set the difference calculation to an arbitrary high num so the new diff is always assigned
							// std::infinity could also work
    for (size_t i = 1; i < result.size(); ++i) { // Start from 1 to avoid out-of-bounds access
        int diff = result[i] - result[i - 1];
        if (diff < min_diff) {
            min_diff = diff; 
        }
    }

    bool first_pair = true; // Track if it's the first pair to manage spacing

    for (size_t i = 1; i < result.size(); ++i) {
        if (result[i] - result[i - 1] == min_diff) {
            if (!first_pair) {
                std::cout << " "; // places a space between every pair instead of doing << arri << space << arri-1 << space
            }
            std::cout << result[i - 1] << " " << result[i];
            first_pair = false;
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    int N;
    while (std::cin >> N) {
        std::vector<int> arr(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> arr[i];
        }
        find_pair(arr);
    }
    return EXIT_SUCCESS;
}
