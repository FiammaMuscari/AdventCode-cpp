#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

struct Position {
    int x, y;
    Position(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    bool operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

struct Robot {
    Position pos;
    Position vel;

    Robot(int px, int py, int vx, int vy) 
        : pos(px, py), vel(vx, vy) {}

    void move(int width, int height) {
        pos.x = (pos.x + vel.x) % width;
        pos.y = (pos.y + vel.y) % height;

        if (pos.x < 0) pos.x += width;
        if (pos.y < 0) pos.y += height;
    }
};

void parseInput(const std::string& line, std::vector<Robot>& robots) {
    int px, py, vx, vy;
    sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
    robots.emplace_back(px, py, vx, vy);
}

void scanInput(std::vector<Robot>& robots) {
    std::ifstream inputFile("input.txt");
    std::string line;

    while (getline(inputFile, line)) {
        parseInput(line, robots);
    }
}

int calculateQuadrantCount(const std::vector<Robot>& robots, int quadrant, int width, int height) {
    int count = 0;
    int midX = width / 2;
    int midY = height / 2;

    for (const auto& robot : robots) {
        // Skip robots in the middle lines
        if (robot.pos.x == midX || robot.pos.y == midY) continue;

        bool rightHalf = robot.pos.x > midX;
        bool bottomHalf = robot.pos.y > midY;

        int robotQuadrant = (rightHalf ? 1 : 0) + (bottomHalf ? 2 : 0);

        if (robotQuadrant == quadrant) count++;
    }

    return count;
}

void printGrid(const std::vector<Robot>& robots, int width, int height) {
    std::map<Position, int> robotCount;

    // Count robots in each position
    for (const auto& robot : robots) {
        robotCount[robot.pos]++;
    }

    // Print the grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Position pos(x, y);
            if (robotCount.count(pos) > 0) {
                std::cout << robotCount[pos];
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<Robot> robots;

    // Read input from file
    scanInput(robots);

    const int WIDTH = 101;   // Width of the space
    const int HEIGHT = 103;  // Height of the space
    const int SECONDS = 100;

    std::cout << "Initial state:" << std::endl;
    printGrid(robots, WIDTH, HEIGHT);

    // Simulate movement for SECONDS
    for (int t = 0; t < SECONDS; t++) {
        for (auto& robot : robots) {
            robot.move(WIDTH, HEIGHT);
        }
    }

    std::cout << "After " << SECONDS << " seconds:" << std::endl;
    printGrid(robots, WIDTH, HEIGHT);

    // Calculate robots in each quadrant
    std::vector<int> quadrantCounts(4);
    
    for (int q = 0; q < 4; q++) {
        quadrantCounts[q] = calculateQuadrantCount(robots, q, WIDTH, HEIGHT);
        std::cout << "Quadrant " << q << ": " << quadrantCounts[q] << " robots" << std::endl;
    }

    // Calculate safety factor
    int safetyFactor = 1;
    
    for (int count : quadrantCounts) {
        safetyFactor *= count;
    }

    std::cout << "Safety factor: " << safetyFactor << std::endl;

    return 0;
}
