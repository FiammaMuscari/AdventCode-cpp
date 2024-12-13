#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cstdint>

struct ClawMachine {
    int64_t ax, ay;   
    int64_t bx, by;   
    int64_t px, py;   
};

 
int64_t extractNumber(const std::string& str) {
    std::regex number_regex("[-+]?\\d+");
    std::smatch match;
    if (std::regex_search(str, match, number_regex)) {
        return std::stoll(match[0]);
    }
    return 0;
}

 
std::pair<bool, int> solveMachine(const ClawMachine& machine) {
    const int MAX_TRIES = 1000;   
    
    for (int a = 0; a <= MAX_TRIES; ++a) {
        for (int b = 0; b <= MAX_TRIES; ++b) {
            int64_t x = a * machine.ax + b * machine.bx;
            int64_t y = a * machine.ay + b * machine.by;
            
            if (x == machine.px && y == machine.py) {
                return {true, 3 * a + b};   
            }
            
 
            if (x > machine.px || y > machine.py) {
                break;
            }
        }
 
        if (a * machine.ax > machine.px || a * machine.ay > machine.py) {
            break;
        }
    }
    return {false, 0};
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening input.txt\n";
        return 1;
    }

    std::vector<ClawMachine> machines;
    std::string line;
    ClawMachine current;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line.find("Button A:") != std::string::npos) {
            current.ax = extractNumber(line.substr(line.find("X")));
            current.ay = extractNumber(line.substr(line.find("Y")));
        }
        else if (line.find("Button B:") != std::string::npos) {
            current.bx = extractNumber(line.substr(line.find("X")));
            current.by = extractNumber(line.substr(line.find("Y")));
        }
        else if (line.find("Prize:") != std::string::npos) {
            current.px = extractNumber(line.substr(line.find("X")));
            current.py = extractNumber(line.substr(line.find("Y")));
            machines.push_back(current);
        }
    }

    int totalPrizes = 0;
    int totalTokens = 0;

    for (size_t i = 0; i < machines.size(); ++i) {
        auto [solvable, tokens] = solveMachine(machines[i]);
        if (solvable) {
            totalPrizes++;
            totalTokens += tokens;
            std::cout << "Machine " << i + 1 << " is solvable with " << tokens << " tokens\n";
        } else {
            std::cout << "Machine " << i + 1 << " is not solvable\n";
        }
    }

    std::cout << "\nTotal prizes possible: " << totalPrizes << "\n";
    std::cout << "Minimum tokens needed: " << totalTokens << "\n";

    return 0;
}