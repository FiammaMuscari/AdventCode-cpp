#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: No se pudo abrir el archivo 'input.txt'." << endl;
        return 1;
    }

    string line;
    int totalSum = 0;

    while (getline(inputFile, line)) {
        char firstDigit = '0';
        for (char ch : line) {
            if (isdigit(ch)) {
                firstDigit = ch;
                break;
            }
        }

        char lastDigit = '0';
        for (int i = line.size() - 1; i >= 0; --i) {
            if (isdigit(line[i])) {
                lastDigit = line[i];
                break;
            }
        }

        if (isdigit(firstDigit) && isdigit(lastDigit)) {
            int calibrationValue = (firstDigit - '0') * 10 + (lastDigit - '0');
            totalSum += calibrationValue;
        }
    }

    inputFile.close();   

    cout << "The total sum of all calibration values is: " << totalSum << endl;

    return 0;
}
