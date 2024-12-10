#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
using namespace std;

// Directions: right, down, left, up
const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// Function to find hiking trails and count reachable height-9 positions
int calculateTrailheadScore(const vector<vector<int>>& map, int startX, int startY) {
    int rows = map.size();
    int cols = map[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;
    set<pair<int, int>> height9Positions;  
    
    q.push({startX, startY});
    visited[startX][startY] = true;
    
    while (!q.empty()) {
        auto [currentX, currentY] = q.front();
        q.pop();
        
 
        if (map[currentX][currentY] == 9) {
            height9Positions.insert({currentX, currentY});
        }
        
 
        for (const auto& [dx, dy] : directions) {
            int newX = currentX + dx;
            int newY = currentY + dy;
            
 
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && 
                !visited[newX][newY] && 
                map[newX][newY] == map[currentX][currentY] + 1) {  
                
                visited[newX][newY] = true;
                q.push({newX, newY});
            }
        }
    }
    
    return height9Positions.size();
}

 
int calculateTotalScore(const vector<vector<int>>& map) {
    int totalScore = 0;
    int rows = map.size();
    int cols = map[0].size();
    
 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 0) {
                int score = calculateTrailheadScore(map, i, j);
                totalScore += score;
            }
        }
    }
    
    return totalScore;
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
    
    int totalScore = calculateTotalScore(map);
    cout << "Sum of all trailhead scores: " << totalScore << endl;
    
    return 0;
}