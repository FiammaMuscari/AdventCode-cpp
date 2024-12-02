#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>

int main() {
    std::vector<int> leftList;
    std::vector<int> rightList;

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int num1, num2;
    while (inputFile >> num1 >> num2) {
        leftList.push_back(num1);
        rightList.push_back(num2);
    }

    inputFile.close();

    std::unordered_map<int, int> countMap;
    for (int num : rightList) {
        countMap[num]++;
    }

    int totalSimilarityScore = 0;
    
    for (int num : leftList) {
        int count = countMap[num]; 
        totalSimilarityScore += num * count;
    }


    std::cout << "Total similarity score: " << totalSimilarityScore << std::endl;

    return 0;
}