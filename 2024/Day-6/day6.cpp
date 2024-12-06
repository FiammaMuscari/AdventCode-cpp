#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>

using namespace std;

const vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // (dy, dx)
const char OBSTACLE = '#';

int main() {

    vector<string> map;
    string line;

    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error al abrir el archivo input.txt" << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        map.push_back(line);
    }
    inputFile.close();

    int rows = map.size();
    if (rows == 0) {
        cout << "No se ha introducido ningún mapa." << endl;
        return 0;
    }

    int cols = map[0].size();
    

    int guardX = 0, guardY = 0;
    bool foundGuard = false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == '^') {
                guardX = j;
                guardY = i;
                map[i][j] = '.'; 
                foundGuard = true;
                break;
            }
        }
        if (foundGuard) break;
    }

    if (!foundGuard) {
        cout << "No se encontro al guardia en el mapa." << endl;
        return 0;
    }


    int direction = 0; 
    set<pair<int, int>> visited;
    visited.insert({guardY, guardX});

    while (true) {
        int nextY = guardY + DIRECTIONS[direction].first;
        int nextX = guardX + DIRECTIONS[direction].second;


        if (nextY < 0 || nextY >= rows || nextX < 0 || nextX >= cols) {
            break;
        }

        if (map[nextY][nextX] == OBSTACLE) {
            direction = (direction + 1) % 4; 
            continue; 
        }

        guardY = nextY;
        guardX = nextX;

        visited.insert({guardY, guardX}); 
    }

    cout << "El guardia visito " << visited.size() << " posiciones distintas." << endl;

    return 0;
}