#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

bool isSafeReport(const vector<int>& report) {
    bool isIncreasing = true, isDecreasing = true;

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
        if (diff > 0) {
            isDecreasing = false;
        } else if (diff < 0) {
            isIncreasing = false; 
        }
    }
    return isIncreasing || isDecreasing;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: No se pudo abrir el archivo 'input.txt'." << endl;
        return 1;
    }

    vector<vector<int>> reports;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<int> report;
        int level;

        while (ss >> level) {
            report.push_back(level);
        }
        reports.push_back(report);
    }

    inputFile.close();

    int safeCount = 0;

    for (const auto& report : reports) {
        if (isSafeReport(report)) {
            ++safeCount;
        }
    }

    cout << "Cantidad de informes seguros: " << safeCount << endl;

    return 0;
}
