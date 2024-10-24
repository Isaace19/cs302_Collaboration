// Challenge 08: Repeated DNA sequences

/*
*****************************
Name: Isaac Abella
Netid: iabella
ID: 000641840

Description: Basic Pattern matching of input strings to find DNA copies 

Solution: In order to perform substring matching as fast as possible, we can implement some regex expressions
*****************************
*/

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_set>

using namespace std;

class solution{
    public:
    // only evaluate 9 length long substrings
    std::vector<std::string> Find_Repeats(const std::string& DNA, int length = 9){
        std::map<std::string, int> substring_map;
        std::vector<std::string> repeated_strings;

        // can't apply the sliding window algorithm onto a susbtring that is not the right size
        if(DNA.size() < length){
            return repeated_strings; 
        }

        // apply a sliding window algorithm to map and key all the possible substrings
        for(size_t i = 0; i <= DNA.size() - length; ++i){
            std::string substring = DNA.substr(i, length);
            if(substring_map.find(substring) != substring_map.end()){
                substring_map[substring] = -1; // mark as repeated
            }else{
                // not a repeat
                substring_map[substring] = 1;
            }
        }
    
        for(const auto& entry : substring_map){
            if(entry.second == -1){
                repeated_strings.push_back(entry.first);
            }else{
                continue; // don't add into the substring solution vector
            }
        }
        return repeated_strings;
    }
};

int main(){
    solution solution;
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

    // create a while getline looop
    std::string DNA;
    while(std::getline(std::cin, DNA)){
        // add a check for lines smaller than substring of 9 length. so just output -1 
        //int check = 9;
        //if(DNA.size() < check){
        //    std::cout << "-1\n";
        //}

        std::vector<std::string> repeats = solution.Find_Repeats(DNA);
        if(!repeats.empty()){
            for(const auto& it : repeats){
                std::cout << it << "\n"; // should output the repeats
            }
            std:: cout << "-1\n";
        }else{
            std::cout << "-1\n";
        }
    }
    return 0;
}
