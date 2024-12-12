#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;


const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void dfs(int x, int y, char plant, vector<vector<char>>& grid, vector<vector<bool>>& visited, int& area, int& perimeter) {
    visited[x][y] = true;
    area++;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size() || grid[nx][ny] != plant) {
            perimeter++;
        } else if (!visited[nx][ny]) {
            dfs(nx, ny, plant, grid, visited, area, perimeter);
        }
    }
}

int main() {
    ifstream input("input.txt");
    string line;
    vector<vector<char>> grid;

    while (getline(input, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }

    int rows = grid.size();
    int cols = grid[0].size();
    
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    int totalCost = 0;


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!visited[i][j]) {
                char plant = grid[i][j];
                int area = 0;
                int perimeter = 0;

                dfs(i, j, plant, grid, visited, area, perimeter);

                totalCost += area * perimeter;
            }
        }
    }

    cout << "El precio total de las cercas es: " << totalCost << endl;

    return 0;
}
