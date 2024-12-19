#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

long long findArrangements(const std::string& design, 
                         size_t pos,
                         const std::vector<std::string>& patterns,
                         std::map<std::string, long long>& memo) {
    if (pos >= design.length()) return 1;
    
    std::string key = design.substr(pos);
    if (memo.count(key)) return memo[key];
    
    long long total = 0;
    
    for (const std::string& pattern : patterns) {
        if (pos + pattern.length() > design.length()) continue;
        
        bool matches = true;
        for (size_t i = 0; i < pattern.length(); i++) {
            if (design[pos + i] != pattern[i]) {
                matches = false;
                break;
            }
        }

        if (matches) {
            total += findArrangements(design, pos + pattern.length(), patterns, memo);
        }
    }
    
    memo[key] = total;
    return total;
}

std::vector<std::string> splitPatterns(const std::string& line) {
    std::vector<std::string> patterns;
    std::stringstream ss(line);
    std::string pattern;
    
    while (std::getline(ss, pattern, ',')) {
        pattern.erase(0, pattern.find_first_not_of(" "));
        pattern.erase(pattern.find_last_not_of(" ") + 1);
        if (!pattern.empty()) {
            patterns.push_back(pattern);
        }
    }
    
    return patterns;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line);
    std::vector<std::string> patterns = splitPatterns(line);
    std::getline(file, line);

    long long totalArrangements = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::map<std::string, long long> memo;
        long long arrangements = findArrangements(line, 0, patterns, memo);
        totalArrangements += arrangements;
        
        std::cout << "-" << line << ": " << arrangements << " formas posibles" << std::endl;
    }

    std::cout << "\nTotal de arreglos posibles: " << totalArrangements << std::endl;

    return 0;
}