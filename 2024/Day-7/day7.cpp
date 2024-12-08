#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <fstream>
#include <cstdint>


using ull = uint64_t;


ull evaluate(const std::vector<ull>& numbers, const std::vector<char>& operators) {
    ull result = numbers[0];
    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        }
    }
    return result;
}


bool analyzeValue(const std::vector<ull>& numbers, ull target, bool verbose = false) {
    int spaces = numbers.size() - 1;
    
    if (verbose) {
        std::cout << "Analizando " << target << " con numeros:";
        for (ull num : numbers) std::cout << " " << num;
        std::cout << "\n";
    }


    for (int mask = 0; mask < (1 << spaces); mask++) {
        std::vector<char> operators;
        for (int i = 0; i < spaces; i++) {
            operators.push_back((mask & (1 << i)) ? '*' : '+');
        }
        
        ull result = evaluate(numbers, operators);
        
        if (verbose) {
            std::cout << "Probando combinacion: ";
            for (size_t i = 0; i < operators.size(); i++) {
                std::cout << numbers[i] << " " << operators[i] << " ";
            }
            std::cout << numbers.back() << " = " << result << "\n";
        }
        
        if (result == target) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    std::string line;
    ull sum = 0;
    int lineCount = 0;
    bool verbose = false;

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        lineCount++;
        
        if (lineCount % 100 == 0) {
            std::cout << "Procesando linea " << lineCount << "...\n";
        }

        std::istringstream iss(line);
        std::string part;
        std::getline(iss, part, ':');

        try {
            ull target = std::stoull(part);
            std::vector<ull> numbers;
            
            while (iss >> part) {
                try {
                    numbers.push_back(std::stoull(part));
                } catch (const std::exception& e) {
                    continue;
                }
            }

            if (!numbers.empty()) {
                if (analyzeValue(numbers, target, verbose)) {
                    sum += target;
                    if (verbose) {
                        std::cout << "Encontrada solucion para " << target << "\n";
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error procesando linea " << lineCount << ": " << e.what() << std::endl;
            continue;
        }
    }

    inputFile.close();
    std::cout << "Procesamiento completado.\n";
    std::cout << "Suma total de valores validos: " << sum << std::endl;

    return 0;
}