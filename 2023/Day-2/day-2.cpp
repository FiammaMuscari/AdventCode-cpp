#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

int main() {

    const int maxRed = 12;
    const int maxGreen = 13;
    const int maxBlue = 14;


    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1; 
    }

    std::string line;
    int validGameSum = 0;


    while (std::getline(inputFile, line)) {
        std::istringstream gameStream(line);
        std::string gameId;
        std::getline(gameStream, gameId, ':');

        bool isValidGame = true;

        std::string sets;
        std::getline(gameStream, sets);

        std::istringstream setStream(sets);
        std::string set;
        
        while (std::getline(setStream, set, ';')) {
            std::istringstream cubeStream(set);
            std::string cubeInfo;
            std::map<std::string, int> cubeCounts;


            while (std::getline(cubeStream, cubeInfo, ',')) {
                int count;
                std::string color;
                std::istringstream infoStream(cubeInfo);
                infoStream >> count >> color;

                cubeCounts[color] += count;
            }

            if (cubeCounts["red"] > maxRed || cubeCounts["green"] > maxGreen || cubeCounts["blue"] > maxBlue) {
                isValidGame = false;
                break;
            }
        }

        if (isValidGame) {
            int id = std::stoi(gameId.substr(5));
            validGameSum += id;
        }
    }

    inputFile.close();

    std::cout << "Sum of valid game IDs: " << validGameSum << std::endl;

    return 0;
}