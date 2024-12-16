#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <climits>

enum Direction { EAST = 0, SOUTH = 1, WEST = 2, NORTH = 3 };

struct State {
    int x, y;
    Direction dir;
    long long score;

    State(int x, int y, Direction dir, long long score) 
        : x(x), y(y), dir(dir), score(score) {}

    bool operator>(const State& other) const {
        return score > other.score;
    }
};

struct StateKey {
    int x, y;
    Direction dir;

    bool operator==(const StateKey& other) const {
        return x == other.x && y == other.y && dir == other.dir;
    }
};

struct StateKeyHash {
    std::size_t operator()(const StateKey& key) const {
        return std::hash<int>()(key.x) ^ 
               (std::hash<int>()(key.y) << 1) ^
               (std::hash<int>()(static_cast<int>(key.dir)) << 2);
    }
};

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int getTurns(Direction current, Direction target) {
    int diff = abs(static_cast<int>(current) - static_cast<int>(target));
    return std::min(diff, 4 - diff);
}

long long solveMaze(const std::vector<std::string>& maze) {
    int rows = maze.size();
    int cols = maze[0].size();
    
    // Find start position
    int startX = -1, startY = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1) break;
    }

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    
    std::unordered_map<StateKey, long long, StateKeyHash> minScores;

    pq.push(State(startX, startY, EAST, 0));

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (maze[current.x][current.y] == 'E') {
            return current.score;
        }

        StateKey currentKey = {current.x, current.y, current.dir};
        
        if (minScores.count(currentKey) && minScores[currentKey] < current.score) {
            continue;
        }

        for (int dir = 0; dir < 4; dir++) {
            Direction newDir = static_cast<Direction>(dir);
            int newX = current.x + dx[dir];
            int newY = current.y + dy[dir];

            if (newX < 0 || newX >= rows || newY < 0 || newY >= cols || 
                maze[newX][newY] == '#') {
                continue;
            }

            long long newScore = current.score;
            newScore += getTurns(current.dir, newDir) * 1000;
            newScore += 1;

            StateKey newKey = {newX, newY, newDir};

            if (!minScores.count(newKey) || newScore < minScores[newKey]) {
                minScores[newKey] = newScore;
                pq.push(State(newX, newY, newDir, newScore));
            }
        }
    }

    return -1; 
}

int main() {
    std::ifstream file("input.txt");
    std::vector<std::string> maze;
    std::string line;

    while (std::getline(file, line)) {
        maze.push_back(line);
    }

    long long result = solveMaze(maze);
    std::cout << "Lowest possible score: " << result << std::endl;

    return 0;
}