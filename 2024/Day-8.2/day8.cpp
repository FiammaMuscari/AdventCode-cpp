#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

bool isCollinear(int x1, int y1, int x2, int y2, int ax, int ay) {
    return (x2 - x1) * (ay - y1) - (y2 - y1) * (ax - x1) == 0;
}

int main() {
    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Could not open input.txt" << endl;
        return 1;
    }

    vector<string> grid;
    string line;
    while (getline(inFile, line)) {
        grid.push_back(line);
    }
    inFile.close();

    unordered_map<char, vector<pair<int, int>>> antennas;
    unordered_set<string> antinodes;

    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            char at = grid[y][x];
            if (at != '.') {
                antennas[at].emplace_back(x, y);
            }
        }
    }

    for (const auto& entry : antennas) {
        const vector<pair<int, int>>& positions = entry.second;
        
        if (positions.size() >= 2) {
            for (const auto& pos : positions) {
                antinodes.insert(to_string(pos.first) + "," + to_string(pos.second));
            }
        }
        
        for (int i = 0; i < positions.size(); ++i) {
            for (int j = i + 1; j < positions.size(); ++j) {
                for (int ay = 0; ay < grid.size(); ++ay) {
                    for (int ax = 0; ax < grid[0].size(); ++ax) {
                        if (isCollinear(positions[i].first, positions[i].second,
                                      positions[j].first, positions[j].second,
                                      ax, ay)) {
                            antinodes.insert(to_string(ax) + "," + to_string(ay));
                        }
                    }
                }
            }
        }
    }

    cout << "Total unique locations containing an antinode: " << antinodes.size() << endl;

    return 0;
}