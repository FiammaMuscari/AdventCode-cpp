#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

bool isValidPosition(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
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
    int sum = 0;

    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (isdigit(schematic[i][j])) {
                int k = j;
                string number = "";

                while (k < cols && isdigit(schematic[i][k])) {
                    number += schematic[i][k];
                    k++;
                }

                int fullNumber = stoi(number);

                bool isPartNumber = false;
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= k; y++) {
                        if (isValidPosition(x, y, rows, cols) && !isdigit(schematic[x][y]) && schematic[x][y] != '.') {
                            isPartNumber = true;
                            break;
                        }
                    }
                    if (isPartNumber) break;
                }

                if (isPartNumber) {
                    sum += fullNumber;
                }

                j = k - 1;
            }
        }
    }

    cout << "La suma de los numeros de pieza es: " << sum << endl;
    return 0;
}
