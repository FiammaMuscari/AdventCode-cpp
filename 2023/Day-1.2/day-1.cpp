#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> digits = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int findDigit(const string& s, bool fromStart) {
    if (fromStart) {
        for (int i = 0; i < s.length(); i++) {
            if (isdigit(s[i])) return s[i] - '0';
            for (int d = 0; d < digits.size(); d++) {
                if (s.substr(i).find(digits[d]) == 0) return d;
            }
        }
    } else {
        for (int i = s.length() - 1; i >= 0; i--) {
            if (isdigit(s[i])) return s[i] - '0';
            for (int d = 0; d < digits.size(); d++) {
                if (i >= digits[d].length() - 1 && s.substr(i - digits[d].length() + 1, digits[d].length()) == digits[d]) 
                    return d;
            }
        }
    }
    return -1;
}

int main() {
    ifstream file("input.txt");
    string line;
    int sum = 0;

    while (getline(file, line)) {
        int first = findDigit(line, true);
        int last = findDigit(line, false);
        if (first != -1 && last != -1) {
            sum += first * 10 + last;
        }
    }

    cout << "La suma total de todos los valores de calibración es: " << sum << endl;
    return 0;
}