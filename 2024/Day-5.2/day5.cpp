#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <queue>

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

// Function to find the middle page number from an update
int middlePage(const vector<int>& update) {
    return update[update.size() / 2]; // Middle element for odd-sized updates
}

// Function to perform topological sort on an incorrectly ordered update
vector<int> topologicalSort(const vector<int>& update, const unordered_map<int, set<int>>& rules) {
    unordered_map<int, int> inDegree;
    unordered_map<int, set<int>> adjList;

    // Initialize in-degree and adjacency list
    for (int page : update) {
        inDegree[page] = 0; // Initialize in-degree for each page
    }

    // Build graph and calculate in-degrees
    for (const auto& rule : rules) {
        int x = rule.first;
        for (int y : rule.second) {
            if (inDegree.count(x) && inDegree.count(y)) {
                adjList[x].insert(y);
                inDegree[y]++;
            }
        }
    }

    // Queue for processing nodes with in-degree of 0
    queue<int> zeroInDegreeQueue;
    for (const auto& entry : inDegree) {
        if (entry.second == 0) {
            zeroInDegreeQueue.push(entry.first);
        }
    }

    vector<int> sortedOrder;
    
    // Process nodes with zero in-degree
    while (!zeroInDegreeQueue.empty()) {
        int current = zeroInDegreeQueue.front();
        zeroInDegreeQueue.pop();
        sortedOrder.push_back(current);

        // Decrease the in-degree of neighbors
        for (int neighbor : adjList[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                zeroInDegreeQueue.push(neighbor);
            }
        }
    }

    return sortedOrder;
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
        if (!isOrdered(update, rules)) { // If it's not ordered
            vector<int> correctedOrder = topologicalSort(update, rules);
            sumMiddlePages += middlePage(correctedOrder);
        }
    }

    cout << "Sum of middle page numbers from correctly ordered updates: " << sumMiddlePages << endl;

    return 0;
}