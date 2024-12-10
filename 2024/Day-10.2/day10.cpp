#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
using namespace std;

const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void findDistinctPaths(const vector<vector<int>>& map, int x, int y, 
                      vector<vector<bool>>& visited,
                      set<string>& uniquePaths, string currentPath) {
    int rows = map.size();
    int cols = map[0].size();
    
    if (map[x][y] == 9) {
        uniquePaths.insert(currentPath);
        return;
    }
    
    for (const auto& [dx, dy] : directions) {
        int newX = x + dx;
        int newY = y + dy;
        
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && 
            !visited[newX][newY] && 
            map[newX][newY] == map[x][y] + 1) {

            visited[newX][newY] = true;
            
            string newPath = currentPath + to_string(newX) + "," + to_string(newY) + ";";
            findDistinctPaths(map, newX, newY, visited, uniquePaths, newPath);

            visited[newX][newY] = false;
        }
    }
}

int calculateTrailheadRating(const vector<vector<int>>& map, int startX, int startY) {
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    set<string> uniquePaths;
    string initialPath = to_string(startX) + "," + to_string(startY) + ";";
    
    visited[startX][startY] = true;
    findDistinctPaths(map, startX, startY, visited, uniquePaths, initialPath);
    
    return uniquePaths.size();
}

int calculateTotalRating(const vector<vector<int>>& map) {
    int totalRating = 0;
    int rows = map.size();
    int cols = map[0].size();
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 0) {
                int rating = calculateTrailheadRating(map, i, j);
                totalRating += rating;
            }
        }
    }
    
    return totalRating;
}

vector<vector<int>> readMapFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> map;
    
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return map;
    }
    
    string line;
    while (getline(file, line)) {
        vector<int> row;
        for (char c : line) {
            if (isdigit(c)) {
                row.push_back(c - '0');
            }
        }
        if (!row.empty()) {
            map.push_back(row);
        }
    }
    
    file.close();
    return map;
}

int main() {
    string filename = "input.txt";
    vector<vector<int>> map = readMapFromFile(filename);
    
    if (map.empty()) {
        cout << "Failed to read map." << endl;
        return 1;
    }
    
    int totalRating = calculateTotalRating(map);
    cout << "Sum of all trailhead ratings: " << totalRating << endl;
    
    return 0;
}