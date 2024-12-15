#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <fstream>

using namespace std;

bool moveBoxes(vector<string>& warehouse, int x, int y, const pair<int, int>& dir) {
    if (warehouse[y][x] == '#') {
        return false;
    } else {
        if (warehouse[y][x] == 'O') {
            return moveBoxes(warehouse, x + dir.first, y + dir.second, dir);
        } else {
            warehouse[y][x] = 'O';
            return true;
        }
    }
}

pair<vector<string>, string> getData(const string& filePath) {
    vector<string> warehouse;
    string movements;
    ifstream inputFile(filePath);
    
    if (!inputFile.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return {warehouse, movements};
    }

    string line;
 
    while (getline(inputFile, line)) {
        if (line.empty()) break;  
        warehouse.push_back(line);
    }

  
    while (getline(inputFile, line)) {
        movements += line; 
    }

    inputFile.close();
    return {warehouse, movements};
}

int part1(const pair<vector<string>, string>& input) {
    int sum = 0;
    vector<string> warehouse = input.first;  
    string sequence = input.second;  
    pair<int, int> robot;

    const unordered_map<char, pair<int, int>> directions{
        {'^', {0, -1}},
        {'v', {0, 1}},
        {'<', {-1, 0}},
        {'>', {1, 0}}
    };
 
    for (int i = 0; i < warehouse.size(); ++i) {
        int pos = warehouse[i].find('@');
        if (pos != string::npos) {
            robot = {i, pos};
            break;
        }
    }

    const int maxY = warehouse.size();
    const int maxX = warehouse[0].size();

    for (const char& cmd : sequence) {
        const auto& direction = directions.at(cmd);
        int nextY = robot.first + direction.second;
        int nextX = robot.second + direction.first;

        char& next = warehouse[nextY][nextX];
        char& current = warehouse[robot.first][robot.second];

        if (next == '#') {
            continue; // Wall encountered
        } else if (next == '.') {
            next = '@'; // Move to empty space
            current = '.';
        } else if (next == 'O') {
            if (moveBoxes(warehouse, nextX, nextY, direction)) {
                warehouse[nextY][nextX] = '@';  
                current = '.';
            } else {
                continue; 
            }
        }
        
        robot.first += direction.second;
        robot.second += direction.first;
    }

    for (int i = 1; i < maxY - 1; ++i) {
        for (int j = 1; j < maxX - 1; ++j) {
            if (warehouse[i][j] == 'O') {
                sum += i * 100 + j; 
            }
        }
    }

    return sum;
}

int part2(const pair<vector<string>, string>& input) {
    int sum = 0;
 

    return sum;
}

int main(int argc, char* argv[]) {
    string filepath = argc == 2 ? argv[1] : "input.txt";  

    auto inputData = getData(filepath); 

    cout << "Result:" << part1(inputData) << endl; 

    return 0;
}
