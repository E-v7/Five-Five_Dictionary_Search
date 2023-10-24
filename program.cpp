/*
    Filename    : program.cpp
    By          : E-v7
    Date        : 2023-10-24
    Description : This program reads words from the dictionary stored
                    in a text file then searches for and returns five
                    five letter words that use 25 unique characters
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ALPHABET_MASK 0b1111111111111111111111111

int main(void) {
    std::string str;
    int uniqueCharacters = 0;

    std::vector<std::string> fiveLetterWords;
    std::vector<std::string> badWords;
    std::vector<std::string> result;
    std::ifstream dictionary("./words_alpha.txt");

    if(!dictionary.is_open()) {
        std::cout << "Unable to open file";
        return -1;
    }

    while (std::getline(dictionary, str)) {
        if (str.length() != 5) {
            continue;
        }
        fiveLetterWords.push_back(str);
    }
    dictionary.close();
    std::cout << "Done reading dictionary\n";

    while(1) {
        std::cout << "Trying new combination\n";
        for (auto currentWord : fiveLetterWords) {
            int bitmask = 0;

            for (auto letter : currentWord) {
                int tmp = 0 | 1 << letter -'a'; // tmp used to check for bit being unset
                bitmask ^= 1 << letter - 'a';

                if (!(tmp & bitmask)) { // Word contains 2 or more of the same character
                    bitmask ^= bitmask; // Set bitmask to 0
                    break;
                }
            }

            if (!bitmask || bitmask & uniqueCharacters) { // If result is positive then not unique
                continue;
            }
            uniqueCharacters |= bitmask; // Set some new bits
            result.push_back(currentWord);
        }

        if (result.size() == 5) {
            break;
        } else {
            std::cout << "Combination failed\n";
            badWords.push_back(result[0]);
            result.clear();

            for (auto badWord : badWords) {
                for (auto word = fiveLetterWords.begin(); word != fiveLetterWords.end(); word++) {
                    if (badWord == *word) {
                        fiveLetterWords.erase(word);
                    }
                }
            }
        }
    }

    // Print the words found
    std::cout << "Result:\n";
    for (auto word : result) {
        std::cout << word << "\n";
    }

    return 1;
}