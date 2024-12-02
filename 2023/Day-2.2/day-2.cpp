#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    long long totalPower = 0; 

    while (std::getline(inputFile, line)) {
        std::istringstream gameStream(line);
        std::string gameId;
        std::getline(gameStream, gameId, ':');

        int minRed = 0, minGreen = 0, minBlue = 0;

        std::string sets;
        std::getline(gameStream, sets);


        std::istringstream setStream(sets);
        std::string set;

        while (std::getline(setStream, set, ';')) {
            std::istringstream cubeStream(set);
            std::string cubeInfo;
            int redCount = 0, greenCount = 0, blueCount = 0;


            while (std::getline(cubeStream, cubeInfo, ',')) {
                int count;
                std::string color;
                std::istringstream infoStream(cubeInfo);
                infoStream >> count >> color;


                if (color == "red") {
                    redCount += count;
                } else if (color == "green") {
                    greenCount += count;
                } else if (color == "blue") {
                    blueCount += count;
                }
            }


            minRed = std::max(minRed, redCount);
            minGreen = std::max(minGreen, greenCount);
            minBlue = std::max(minBlue, blueCount);
        }


        long long power = static_cast<long long>(minRed) * minGreen * minBlue;
        totalPower += power;
    }

    inputFile.close();

    std::cout << "Total power of all games: " << totalPower << std::endl;

    return 0;
}