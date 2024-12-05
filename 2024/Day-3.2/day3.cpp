#include <iostream>
#include <string>
#include <regex>
#include <fstream>

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    std::string line;
    int totalSum = 0;
    bool mulEnabled = true;
    
    std::regex mulPattern(R"(mul\((\d+),(\d+)\))");
    std::regex dontPattern(R"(don't\(\))");
    std::regex doPattern(R"(do\(\))");
    
    while (std::getline(inputFile, line)) {
        std::cout << "Reading line: " << line << std::endl;
        
        size_t pos = 0;
        while (pos < line.length()) {
            std::string remaining = line.substr(pos);

            std::smatch dontMatch;
            if (std::regex_search(remaining, dontMatch, dontPattern)) {
                if (dontMatch.position() == 0) {
                    mulEnabled = false;
                    std::cout << "Found don't() - Disabling multiplication" << std::endl;
                    pos += dontMatch.length();
                    continue;
                }
            }
            
            std::smatch doMatch;
            if (std::regex_search(remaining, doMatch, doPattern)) {
                if (doMatch.position() == 0) {
                    mulEnabled = true;
                    std::cout << "Found do() - Enabling multiplication" << std::endl;
                    pos += doMatch.length();
                    continue;
                }
            }

            std::smatch mulMatch;
            if (std::regex_search(remaining, mulMatch, mulPattern)) {
                if (mulMatch.position() == 0) {
                    int x = std::stoi(mulMatch[1].str());
                    int y = std::stoi(mulMatch[2].str());
                    
                    if (mulEnabled) {
                        std::cout << "Multiplying " << x << " * " << y << " = " << (x * y) << std::endl;
                        totalSum += x * y;
                        std::cout << "Running total: " << totalSum << std::endl;
                    } else {
                        std::cout << "Skipping multiplication of " << x << " * " << y << " (disabled)" << std::endl;
                    }
                    pos += mulMatch.length();
                    continue;
                }
            }
            
            pos++; 
        }
    }
    
    inputFile.close();
    std::cout << "Total sum of multiplications: " << totalSum << std::endl;
    return 0;
}