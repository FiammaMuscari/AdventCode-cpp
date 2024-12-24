#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

struct Gate {
    std::string type;   
    std::string input1; 
    std::string input2; 
    std::string output; 
};

bool evaluateGate(const std::string& type, bool in1, bool in2) {
    if (type == "AND") return in1 && in2;
    if (type == "OR") return in1 || in2;
    if (type == "XOR") return in1 != in2;
    return false;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::map<std::string, bool> wires;        
    std::vector<Gate> gates;                  
    std::map<std::string, bool> wireHasValue; 

    std::string line;
    while (std::getline(file, line) && !line.empty()) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string wireName = line.substr(0, colonPos);
            int value = std::stoi(line.substr(colonPos + 1));
            wires[wireName] = value;
            wireHasValue[wireName] = true;
        }
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string in1, op, in2, arrow, out;
        iss >> in1 >> op >> in2 >> arrow >> out;
        
        Gate gate;
        gate.type = op;
        gate.input1 = in1;
        gate.input2 = in2;
        gate.output = out;
        gates.push_back(gate);
        
        wireHasValue[out] = false;
    }

    bool changed;
    do {
        changed = false;
        for (const Gate& gate : gates) {
            if (!wireHasValue[gate.output] && 
                wireHasValue[gate.input1] && 
                wireHasValue[gate.input2]) {
                
                wires[gate.output] = evaluateGate(gate.type, 
                                                wires[gate.input1], 
                                                wires[gate.input2]);
                wireHasValue[gate.output] = true;
                changed = true;
            }
        }
    } while (changed);

    std::vector<std::string> zWires;
    for (const auto& wire : wires) {
        if (wire.first[0] == 'z') {
            zWires.push_back(wire.first);
        }
    }
    std::sort(zWires.begin(), zWires.end());

    unsigned long long result = 0;
    for (int i = zWires.size() - 1; i >= 0; i--) {
        result = (result << 1) | (wires[zWires[i]] ? 1 : 0);
    }

    std::cout << "Final decimal number: " << result << std::endl;

    return 0;
}