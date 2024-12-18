#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};


struct State {
    Point pos;
    int steps;
    State(Point p, int s) : pos(p), steps(s) {}
};

class MemoryPathFinder {
private:
    static const int GRID_SIZE = 71;
    std::vector<std::vector<bool>> corrupted;
    std::vector<Point> fallingBytes;

    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};

    bool isValid(int x, int y) {
        return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && !corrupted[y][x];
    }

public:
    MemoryPathFinder() {
        corrupted.resize(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
    }

    void readInput(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::stringstream ss(line);
            std::string x_str, y_str;
            
            std::getline(ss, x_str, ',');
            std::getline(ss, y_str);
            
            fallingBytes.push_back(Point(std::stoi(x_str), std::stoi(y_str)));
        }
    }

    void simulateBytes(int numBytes) {
        for (auto& row : corrupted) {
            std::fill(row.begin(), row.end(), false);
        }
        
        for (int i = 0; i < numBytes && i < fallingBytes.size(); i++) {
            corrupted[fallingBytes[i].y][fallingBytes[i].x] = true;
        }
    }

    int findShortestPath() {
        std::queue<State> q;
        std::vector<std::vector<bool>> visited(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
        
        q.push(State(Point(0, 0), 0));
        visited[0][0] = true;
        
        while (!q.empty()) {
            State current = q.front();
            q.pop();
            
            if (current.pos.x == GRID_SIZE-1 && current.pos.y == GRID_SIZE-1) {
                return current.steps;
            }

            for (int i = 0; i < 4; i++) {
                int newX = current.pos.x + dx[i];
                int newY = current.pos.y + dy[i];
                
                if (isValid(newX, newY) && !visited[newY][newX]) {
                    visited[newY][newX] = true;
                    q.push(State(Point(newX, newY), current.steps + 1));
                }
            }
        }
        
        return -1;
    }

    void printGrid() {
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int x = 0; x < GRID_SIZE; x++) {
                std::cout << (corrupted[y][x] ? '#' : '.');
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    MemoryPathFinder pathFinder;

    pathFinder.readInput("input.txt");

    pathFinder.simulateBytes(1024);
    int result = pathFinder.findShortestPath();
    
    if (result != -1) {
        std::cout << "Shortest path length: " << result << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }
    
    return 0;
}