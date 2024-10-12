// Challenge 06: Palindrome Permutation

/*

    Name: Isaac Abella
    Netid: iabella

    Description: taking in input of strings, remove all whitespaces and special characters.
    Then, using an unordered map, check of the string can be a palindrone or not by evaluating characters in an array.
*/

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <cctype>
#include <unordered_map>

bool is_palindrone(std::string &input)
{
    // parse out all non alphanumeric stuff in the input if any -- kinda of an overkill but we want to add this in case someone put in a capital and we want to get it into lower
    std::unordered_map<char, int> char_count;

    for (std::string::const_iterator it = input.begin(); it != input.end(); ++it)
    {
        char c = *it;
        if (std::isalpha(c))
        {                                   // Consider only alphabetic characters
            char lower_c = std::tolower(c); // Convert to lowercase
            char_count[lower_c]++;
        }
    }

    /*
    For palindrones, we can discern if the input string is one if we can find only one unique odd in the center of the string.
    Example: racecar is a palindrone because we have e as a unique in the center.
    Therefore, our logic of checking the key value of an unordered map should be if only one it->second is odd in frequencey,
    than we delcare the valid as true that it is a palindrone.

    If there is multiple odd frequencies of key values, than it is not a palindrone permutation.
    */
    bool valid = false;
    for (std::unordered_map<char, int>::const_iterator it = char_count.begin(); it != char_count.end(); ++it)
    {
        if (it->second % 2 != 0)
        {
            if (valid)
            {
                return false;
            }
            valid = true;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        // check for palindrone
        if (is_palindrone(input))
        {
            std::cout << "\"" << input << "\" is a palindrone permutation\n";
        }
        else
        {
            std::cout << "\"" << input << "\" is not a palindrone permutation\n";
        }
    }

    return (0);
}
