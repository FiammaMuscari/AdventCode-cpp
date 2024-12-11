#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <map>

using namespace std;

int countMatches(const vector<int>& winningNumbers, const vector<int>& yourNumbers) {
    set<int> winningSet(winningNumbers.begin(), winningNumbers.end());
    int matchCount = 0;
    
    for (int num : yourNumbers) {
        if (winningSet.count(num)) {
            matchCount++;
        }
    }
    
    return matchCount;
}

struct Card {
    vector<int> winningNumbers;
    vector<int> yourNumbers;
    int matches;
};

int main() {
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo input.txt" << endl;
        return 1;
    }
    
    vector<Card> cards;
    vector<int> cardInstances;
    
    string line;
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
        
        Card card;
        
        stringstream winningStream(winningPart);
        int number;
        while (winningStream >> number) {
            card.winningNumbers.push_back(number);
        }
        
        stringstream yourStream(yourPart);
        while (yourStream >> number) {
            card.yourNumbers.push_back(number);
        }
        
        card.matches = countMatches(card.winningNumbers, card.yourNumbers);
        cards.push_back(card);
        cardInstances.push_back(1);
    }
    
    for (size_t i = 0; i < cards.size(); i++) {
        int matches = cards[i].matches;
        int currentInstances = cardInstances[i];
        
        for (int j = 1; j <= matches && i + j < cards.size(); j++) {
            cardInstances[i + j] += currentInstances;
        }
        
        cout << "Card " << (i + 1) << ": " << matches << " matches, " 
             << currentInstances << " instances, adds to next " 
             << matches << " cards" << endl;
    }
    
    int totalCards = 0;
    for (int instances : cardInstances) {
        totalCards += instances;
    }
    
    cout << "\nTotal scratchcards: " << totalCards << endl;
    
    for (size_t i = 0; i < cardInstances.size(); i++) {
        cout << "Card " << (i + 1) << ": " << cardInstances[i] << " instances" << endl;
    }
    
    inputFile.close();
    return 0;
}