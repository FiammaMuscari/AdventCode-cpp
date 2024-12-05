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

 
    std::regex mulPattern(R"(mul\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*\))");
    std::smatch matches;
 
    while (std::getline(inputFile, line)) {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), mulPattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            matches = *i;
            int x = std::stoi(matches[1].str()); 
            int y = std::stoi(matches[2].str());  
            totalSum += x * y;  
        }
    }

    inputFile.close(); 

    std::cout << "Total sum of multiplications: " << totalSum << std::endl;

    return 0;
}