#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    std::cout << "Sorted Left List:   Sorted Right List:   Distance" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    int totalDistance = 0;
    for (size_t i = 0; i < leftList.size(); ++i) {
        int distance = std::abs(leftList[i] - rightList[i]);
        totalDistance += distance;

        std::cout << leftList[i] << "\t\t" << rightList[i] << "\t\t" << distance << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Total distance between the lists: " << totalDistance << std::endl;

    return 0;
}