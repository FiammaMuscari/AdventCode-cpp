#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const vector<pair<int, int>> directions = {
    {0, 1}, 
    {0, -1}, 
    {1, 0}, 
    {-1, 0}, 
    {1, 1},   
    {1, -1},  
    {-1, 1}, 
    {-1, -1} 
};

bool isValid(const vector<string>& grid, int x, int y) {
    return x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size();
}

int countWordOccurrences(const vector<string>& grid, const string& word) {
    int rows = grid.size();
    int cols = grid[0].size();
    int wordLen = word.length();
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == word[0]) {
                for (const auto& dir : directions) {
                    int x = i, y = j, k = 0;

                    while (k < wordLen && isValid(grid, x, y) && grid[x][y] == word[k]) {
                        x += dir.first;
                        y += dir.second;
                        k++;
                    }

                    if (k == wordLen) {
                        count++;
                    }
                }
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
        cerr << "No se pudo abrir el archivo input-example.txt" << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();

    string word = "XMAS";
    int result = countWordOccurrences(grid, word);

    cout << "La palabra '" << word << "' aparece " << result << " veces en el tablero." << endl;
    return 0;
}
