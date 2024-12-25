#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>


void parseInput(const std::string& fileName,
               std::set<std::vector<int>>& locks,
               std::set<std::vector<int>>& keys) {
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> temp;

    while (std::getline(file, line)) {
        if (line.empty()) {
            std::vector<int> heights;
            for (int col = 0; col < temp[0].size(); col++) {
                int count = 0;
                for (int row = 0; row < temp.size(); row++) {
                    if (temp[row][col] == '#') {
                        count++;
                    }
                }
                heights.push_back(count - 1);
            }

            if (temp[0][0] == '.') {
                keys.insert(heights);
            } else {
                locks.insert(heights);
            }

            temp.clear();
            continue;
        }
        temp.push_back(line);
    }

    if (!temp.empty()) {
        std::vector<int> heights;
        for (int col = 0; col < temp[0].size(); col++) {
            int count = 0;
            for (int row = 0; row < temp.size(); row++) {
                if (temp[row][col] == '#') {
                    count++;
                }
            }
            heights.push_back(count - 1);
        }

        if (temp[0][0] == '.') {
            keys.insert(heights);
        } else {
            locks.insert(heights);
        }
    }

    file.close();
}

int main() {
    const std::string INPUT_PATH = "input.txt";
    std::set<std::vector<int>> locks;
    std::set<std::vector<int>> keys;

    parseInput(INPUT_PATH, locks, keys);

    int matches = 0;
    for (const auto& lock : locks) {
        for (const auto& key : keys) {
            bool fits = true;
            for (size_t i = 0; i < key.size(); i++) {
                if (key[i] + lock[i] > 5) {
                    fits = false;
                    break;
                }
            }
            if (fits) {
                matches++;
            }
        }
    }

    std::cout << "Number of unique lock/key pairs that fit: " << matches << std::endl;

    return 0;
}