#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <queue>
#include <array>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <climits>
#include <algorithm>


typedef std::vector<std::string> Keypad;
typedef std::vector<std::vector<uint64_t>> NumKeypad;

const Keypad NUMERIC_KEYPAD = {
    "#####",
    "#789#",
    "#456#",
    "#123#",
    "##0A#",
    "#####"
};

constexpr int NUMERIC_KEYPAD_HEIGHT = 6;
constexpr int NUMERIC_KEYPAD_WIDTH = 5;

const Keypad DIRECTIONAL_KEYPAD = {
    "#####",
    "##^A#",
    "#<v>#",
    "#####"
};

constexpr int DIRECTIONAL_KEYPAD_HEIGHT = 4;
constexpr int DIRECTIONAL_KEYPAD_WIDTH = 5;

typedef long long num;

struct Point {
    num i = 0, j = 0;

    bool operator==(const Point &other) const {
        return i == other.i && j == other.j;
    }

    struct Hash {
        std::size_t operator()(const Point &point) const {
            return point.i * NUMERIC_KEYPAD_WIDTH + point.j;
        }
    };
};

const Point DELTA[] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
const char MOVE[] = { '^', '>', 'v', '<' };

struct Data {
    using Code = std::string;
    std::vector<Code> codes;
};

constexpr num MAX_SIZE = 'z';

using NumericCache = std::array<std::array<std::string, MAX_SIZE>, MAX_SIZE>;
NumericCache precomputed_cache;

void processInput(Data& input);
void preprocess(NumericCache &cache, int depth);
void bfs(const Keypad &keys, const char startChar, const char targetChar,
         std::function<void(const std::string &, const Point &)> callback);
void bfs(const Keypad &keys, const Point &start, const Point &target,
         std::function<void(const std::string &, const Point &)> callback);
bool findInKeypad(const Keypad &keys, const char targetChar, Point &position);
num scorePath(const std::string &path);
void iterateAndGetBestPath(const std::string &path, 
                            const std::function<void(const std::string &, num)> &callback);
std::string resolveLine(const Data &input, const NumericCache &cache, const Data::Code &code);
void part1(Data input);

int main() {
    Data input;
    processInput(input);
    part1(input);
    
    return 0;
}

void processInput(Data& input) {
    std::string line;
    std::ifstream fin("input.txt");
    while (std::getline(fin, line)) {
        input.codes.emplace_back(line);
    }
}

bool findInKeypad(const Keypad &keys, const char targetChar, Point &position) {
    for (num i = 1; i < keys.size() - 1; i++) {
        for (num j = 1; j < keys[i].size() - 1; j++) {
            if (keys[i][j] == targetChar) {
                position = { i, j };
                return true;
            }
        }
    }
    return false;
}

void bfs(const Keypad &keys, const Point &start, const Point &target,
         std::function<void(const std::string &, const Point &)> callback) {
    
    struct Node {
        std::string path;
        Point pos;
        num dist;
        uint64_t idx;

        Node(const std::string& p, const Point& po, num d, uint64_t i)
            : path(p), pos(po), dist(d), idx(i) {}
    };

    if (start == target) {
        callback("A", start);
        return;
    }

    uint64_t global_idx = 1;
    std::vector<std::vector<uint64_t>> visited(10, std::vector<uint64_t>(10, 0));
    
    num maxDist = std::abs(start.i - target.i) + std::abs(start.j - target.j);
    
    std::queue<Node> queue;
    queue.push(Node("", start, 0, global_idx++));
    visited[start.i][start.j] = 1;

    while (!queue.empty()) {
        Node currentNode = queue.front();
        queue.pop();

        if (currentNode.dist > maxDist) continue;

        if (currentNode.pos == target) {
            callback(currentNode.path + "A", currentNode.pos);
            continue;
        }

        for (int dir = 0; dir < 4; dir++) {
            Point next = { currentNode.pos.i + DELTA[dir].i, currentNode.pos.j + DELTA[dir].j };
            if (keys[next.i][next.j] == '#' || (visited[next.i][next.j] & currentNode.idx)) continue;

            for (auto &row : visited) {
                for (auto &cell : row) {
                    if (cell & currentNode.idx) cell |= global_idx;
                }
            }
            queue.push(Node(currentNode.path + MOVE[dir], next, currentNode.dist + 1, global_idx++));
        }
    }
}

void bfs(const Keypad &keys, const char startChar, const char targetChar,
         std::function<void(const std::string &, const Point &)> callback) {
    
    Point startPoint, endPoint;
    
    if (!findInKeypad(keys, startChar, startPoint) || !findInKeypad(keys, targetChar, endPoint)) return;

    bfs(keys, startPoint, endPoint, callback);
}

num scorePath(const std::string &path) {
    num score = 0;
    
    for (num i = 1; i < path.size(); i++) {
        score += (path[i] != path[i - 1]);
    }
    
    return score;
}

void iterateAndGetBestPath(const std::string &path,
                            const std::function<void(const std::string &, num)> &callback) {

    for (num i = 0; i < path.size(); i++) {
        char previous = (i == 0) ? 'A' : path[i - 1];
        char current = path[i];

        num bestScore = LLONG_MAX;
        std::string bestPath;

        bfs(DIRECTIONAL_KEYPAD, previous, current,
            [&](const std::string &newPath, const Point &) {
                num score = scorePath(newPath);
                if (score < bestScore) {
                    bestScore = score;
                    bestPath = newPath;
                }
            });

        if (bestScore != LLONG_MAX) {
            callback(bestPath, bestScore);
        }
    }
}

void preprocessRecursive(std::string &result, const std::string &path,
                         int depthRemaining) {

    iterateAndGetBestPath(path,
                           [&](const std::string &bestPath, num) {
                               if (depthRemaining == 0) {
                                   result += bestPath;
                               } else {
                                   preprocessRecursive(result, bestPath, depthRemaining - 1);
                               }
                           });
}

void preprocess(NumericCache &cache, int depth) {
    
    const std::string keys = "A0123456789";

    for (const char start : keys) {
        for (const char end : keys) {

            bfs(NUMERIC_KEYPAD, start, end,
                [&](const std::string &path, const Point &) {

                    std::string result;
                    preprocessRecursive(result, path, depth);

                    auto& previousResult = cache[start][end];
                    if (previousResult.empty() || previousResult.length() > result.length()) {
                        previousResult = result;
                    }
                });
        }
    }
}

std::string resolveLine(const Data &input,
                        const NumericCache &cache,
                        const Data::Code &code) {

    std::string result = cache['A'][code[0]];
    
    for (num i = 1; i < code.size(); i++) {
        result += cache[code[i - 1]][code[i]];
    }

    return result;
}

void part1(Data input) {

    num resultValue = 0;
    
    preprocess(precomputed_cache, 1);

    for (const auto &code : input.codes) {
        num value = std::stoll(code);
        
        std::string resolvedLine = resolveLine(input, precomputed_cache, code);

        num length = resolvedLine.length();
        resultValue += length * value;
    }

   std::cout << "part 1: " << resultValue << '\n';
}
