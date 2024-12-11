#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int calculatePoints(const vector<int>& winningNumbers, const vector<int>& yourNumbers) {
    set<int> winningSet(winningNumbers.begin(), winningNumbers.end());
    int matchCount = 0;
    
    for (int num : yourNumbers) {
        if (winningSet.count(num)) {
            matchCount++;
        }
    }
    
    if (matchCount == 0) return 0;
    return 1 << (matchCount - 1);
}

int main() {
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo input.txt" << endl;
        return 1;
    }
    
    string line;
    int totalPoints = 0;
    
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        
        size_t cardPrefixEnd = line.find(':');
        if (cardPrefixEnd != string::npos) {
            line = line.substr(cardPrefixEnd + 1);
        }
        
        size_t separator = line.find('|');
        if (separator == string::npos) continue;
        
        string winningPart = line.substr(0, separator);
        string yourPart = line.substr(separator + 1);
        
        vector<int> winningNumbers;
        stringstream winningStream(winningPart);
        int number;
        while (winningStream >> number) {
            winningNumbers.push_back(number);
        }
        
        vector<int> yourNumbers;
        stringstream yourStream(yourPart);
        while (yourStream >> number) {
            yourNumbers.push_back(number);
        }
        
        int points = calculatePoints(winningNumbers, yourNumbers);
        totalPoints += points;
        
        cout << "Card numbers: " << winningPart << " | " << yourPart << endl;
        cout << "Points for this card: " << points << endl;
    }
    
    cout << "Total Points: " << totalPoints << endl;
    inputFile.close();
    return 0;
}