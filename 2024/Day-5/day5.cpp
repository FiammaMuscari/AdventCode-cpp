#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// Function to check if an update is in correct order based on rules
bool isOrdered(const vector<int>& update, const unordered_map<int, set<int>>& rules) {
    unordered_map<int, int> position;
    for (int i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }
    
    for (const auto& rule : rules) {
        int x = rule.first;
        for (int y : rule.second) {
            // If both x and y are in the update, check their positions
            if (position.count(x) && position.count(y)) {
                if (position[x] > position[y]) {
                    return false; // x is after y, which is incorrect
                }
            }
        }
    }
    return true;
}

// Function to find the middle page number from a correctly ordered update
int middlePage(const vector<int>& update) {
    return update[update.size() / 2]; // Middle element for odd-sized updates
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Parse rules into a graph structure
    unordered_map<int, set<int>> rules;
    string line;

    // Read ordering rules until an empty line is encountered
    while (getline(inputFile, line) && !line.empty()) {
        int x = stoi(line.substr(0, line.find('|')));
        int y = stoi(line.substr(line.find('|') + 1));
        rules[x].insert(y);
    }

    // Read updates
    vector<vector<int>> updatesInput;
    while (getline(inputFile, line)) {
        vector<int> update;
        stringstream ss(line);
        string token;

        while (getline(ss, token, ',')) {
            update.push_back(stoi(token));
        }

        updatesInput.push_back(update);
    }

    inputFile.close(); // Close the file

    int sumMiddlePages = 0;

    // Check each update for correct order and calculate middle pages
    for (const auto& update : updatesInput) {
        if (isOrdered(update, rules)) {
            sumMiddlePages += middlePage(update);
        }
    }

    cout << "Sum of middle page numbers from correctly ordered updates: " << sumMiddlePages << endl;

    return 0;
}