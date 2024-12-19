#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

bool canMakeDesign(const std::string& design, const std::vector<std::string>& patterns, int startPos = 0) {
    if (startPos == design.length()) {
        return true;
    }
    
    for (const std::string& pattern : patterns) {
        if (startPos + pattern.length() <= design.length()) {
            bool matches = true;
            for (size_t i = 0; i < pattern.length(); i++) {
                if (design[startPos + i] != pattern[i]) {
                    matches = false;
                    break;
                }
            }
            
            if (matches) {
                if (canMakeDesign(design, patterns, startPos + pattern.length())) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> patterns;
    std::vector<std::string> designs;
    bool readingPatterns = true;
    
    while (std::getline(file, line)) {
        if (line.empty()) {
            readingPatterns = false;
            continue;
        }
        
        if (readingPatterns) {
            auto tokens = split(line, ',');
            patterns.insert(patterns.end(), tokens.begin(), tokens.end());
        } else {
            designs.push_back(line);
        }
    }

    int possibleDesigns = 0;
    for (const auto& design : designs) {
        if (canMakeDesign(design, patterns)) {
            possibleDesigns++;
            std::cout << design << " is possible\n";
        } else {
            std::cout << design << " is impossible\n";
        }
    }
    
    std::cout << "\nTotal possible designs: " << possibleDesigns << std::endl;
    
    return 0;
}