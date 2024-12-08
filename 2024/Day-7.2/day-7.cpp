#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdint>

using ull = uint64_t;

 
ull concatenate(ull a, ull b) {
    std::string s_a = std::to_string(a);
    std::string s_b = std::to_string(b);
    return std::stoull(s_a + s_b);
}

 
ull evaluate(const std::vector<ull>& numbers, const std::vector<char>& operators) {
    ull result = numbers[0];
    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        } else if (operators[i] == '|') { 
            result = concatenate(result, numbers[i + 1]);
        }
    }
    return result;
}

 
bool analyzeValue(const std::vector<ull>& numbers, ull target, bool verbose = false) {
    int spaces = numbers.size() - 1;
    const int NUM_OPERATORS = 3; 
    
    if (verbose) {
        std::cout << "Analizando " << target << " con numeros:";
        for (ull num : numbers) std::cout << " " << num;
        std::cout << "\n";
    }

 
    int total_combinations = 1;
    for (int i = 0; i < spaces; i++) {
        total_combinations *= NUM_OPERATORS;
    }

    for (int comb = 0; comb < total_combinations; comb++) {
        std::vector<char> operators;
        int temp_comb = comb;
        
 
        for (int i = 0; i < spaces; i++) {
            int op = temp_comb % NUM_OPERATORS;
            temp_comb /= NUM_OPERATORS;
            
            if (op == 0) operators.push_back('+');
            else if (op == 1) operators.push_back('*');
            else operators.push_back('|');
        }
        
        ull result = evaluate(numbers, operators);
        
        if (verbose) {
            for (size_t i = 0; i < operators.size(); i++) {
                std::cout << numbers[i] << " " << 
                    (operators[i] == '|' ? "||" : std::string(1, operators[i])) << " ";
            }
            std::cout << numbers.back() << " = " << result << "\n";
        }
        
        if (result == target) {
            if (verbose) {
                std::cout << "¡Encontrada solucion!\n";
            }
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