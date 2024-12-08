#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
#include <algorithm>
#include <fstream>

using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};  
const char OBSTACLE = '#';

struct GuardState {
    int y, x, dir;
    bool operator<(const GuardState& other) const {
        return tie(y, x, dir) < tie(other.y, other.x, other.dir);
    }
};

bool createsValidLoop(vector<string>& map, int obsY, int obsX, int guardY, int guardX) {
 
    map[obsY][obsX] = OBSTACLE;

 
    GuardState current{guardY, guardX, 0}; 

    set<GuardState> visited;

    while (true) {
        int nextY = current.y + DIRECTIONS[current.dir].first;
        int nextX = current.x + DIRECTIONS[current.dir].second;

 
        if (nextY < 0 || nextY >= map.size() || nextX < 0 || nextX >= map[0].size()) {
            map[obsY][obsX] = '.'; 
            return false; 
        }

        // Check for obstacles
        if (map[nextY][nextX] == OBSTACLE) {
            current.dir = (current.dir + 1) % 4; 
            continue; 
        }

 
        current.y = nextY;
        current.x = nextX;
 
        if (!visited.insert(current).second) {
            map[obsY][obsX] = '.';  
            return true;  
        }
    }
}

int findValidObstructions(const vector<string>& originalMap) {
    vector<string> map = originalMap;
    int rows = map.size();
    int cols = map[0].size();
    
    int guardY = -1, guardX = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == '^') {
                guardY = i;
                guardX = j;
                map[i][j] = '.';  
                break;
            }
        }
        if (guardY != -1) break;
    }
    
    int validPositions = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == '.' && !(i == guardY && j == guardX)) {  
                if (createsValidLoop(map, i, j, guardY, guardX)) {
                    validPositions++;
                    cout << "Found position at: (" << i << ", " << j << ")" << endl; 
                }
            }
        }
    }
    
    return validPositions;
}

int main() {
    vector<string> map;

    // Load the map from input.txt
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error opening input.txt" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        map.push_back(line);
    }
    
    inputFile.close();

    int result = findValidObstructions(map);
    
    cout << "Total valid positions: " << result << endl;
    
    return 0;
}