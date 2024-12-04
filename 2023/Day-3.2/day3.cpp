#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <set>
using namespace std;

bool isValidPosition(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}


int findNumberStart(const string& line, int pos) {
    while (pos >= 0 && isdigit(line[pos])) {
        pos--;
    }
    return pos + 1;
}


int extractNumber(const string& line, int& pos) {
    string number = "";

    int start = findNumberStart(line, pos);

    while (start < line.length() && isdigit(line[start])) {
        number += line[start];
        start++;
    }
    
    return stoi(number);
}

int main() {
    vector<string> schematic;
    string fileName = "input.txt";

    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo: " << fileName << endl;
        return 1;
    }
    
    string line;
    while (getline(inputFile, line)) {
        schematic.push_back(line);
    }
    inputFile.close();
    
    int rows = schematic.size();
    int cols = rows > 0 ? schematic[0].size() : 0;
    int gearSum = 0;

    vector<pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (schematic[i][j] == '*') {
                set<pair<int, int>> numberPositions; 
                
                for (const auto& dir : directions) {
                    int x = i + dir.first;
                    int y = j + dir.second;
                    
                    if (isValidPosition(x, y, rows, cols) && isdigit(schematic[x][y])) {
                        int start = findNumberStart(schematic[x], y);
                        numberPositions.insert({x, start});
                    }
                }
                

                if (numberPositions.size() == 2) {
                    vector<int> numbers;
                    for (const auto& pos : numberPositions) {
                        int y = pos.second;
                        numbers.push_back(extractNumber(schematic[pos.first], y));
                    }
                    
                    int gearRatio = numbers[0] * numbers[1];
                    gearSum += gearRatio;
                }
            }
        }
    }
    
    cout << "La suma de las relaciones de engranaje es: " << gearSum << endl;
    return 0;
}