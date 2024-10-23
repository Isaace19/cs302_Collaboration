// Challenge 08: Repeated DNA sequences

/*
*****************************
Name: Isaac Abella
Netid: iabella
ID: 000641840

Description: Basic Pattern matching of input strings to find DNA copies 

Solution: Create a suffix tree to find the substring matches as fast as possible
*****************************
*/

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main(){
    std::string DNA;
    std::getline(std::cin, DNA);

    std::unordered_set<std::string> substring;
    for(size_t i = 0; i + 9 <= DNA.size(); ++i){
        substring.insert(DNA.substr(i, 9)); // insert 9 length long substring into unordered map
    }

    for(const auto& sub : substring){
        cout << sub << endl;
    }

    return 0;
}
