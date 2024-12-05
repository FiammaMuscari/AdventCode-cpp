#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

bool isValid(const vector<string>& grid, int x, int y) {
    return x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size();
}

bool checkMAS(const vector<string>& grid, int x, int y, int dx, int dy) {
    string forward = "MAS";
    string backward = "SAM";
    
 
    if (!isValid(grid, x, y) || !isValid(grid, x + 2*dx, y + 2*dy)) {
        return false;
    }
    
 
    bool isForward = true;
    for (int i = 0; i < 3; i++) {
        if (grid[x + i*dx][y + i*dy] != forward[i]) {
            isForward = false;
            break;
        }
    }
    
 
    bool isBackward = true;
    for (int i = 0; i < 3; i++) {
        if (grid[x + i*dx][y + i*dy] != backward[i]) {
            isBackward = false;
            break;
        }
    }
    
    return isForward || isBackward;
}

int countXMASPatterns(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;
    
 
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
 
            if (grid[i][j] != 'A') continue;
             
            if ((checkMAS(grid, i-1, j-1, 1, 1) && checkMAS(grid, i-1, j+1, 1, -1)) ||    // ↘↙
                (checkMAS(grid, i-1, j-1, 1, 1) && checkMAS(grid, i+1, j-1, -1, 1)) ||    // ↘↗
                (checkMAS(grid, i-1, j+1, 1, -1) && checkMAS(grid, i+1, j+1, -1, -1)) ||  // ↙↖
                (checkMAS(grid, i+1, j-1, -1, 1) && checkMAS(grid, i+1, j+1, -1, -1))) {  // ↗↖
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    ifstream inputFile("input.txt");
    vector<string> grid;
    string line;
    
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo input.txt" << endl;
        return 1;
    }
    
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();
    
    int result = countXMASPatterns(grid);
    cout << "El patrón X-MAS aparece " << result << " veces en el tablero." << endl;
    
    return 0;
}