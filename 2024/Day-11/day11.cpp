#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Función para contar cuántas nuevas piedras genera una piedra
long long calculateStoneGrowth(long long stone, int blinks) {
    if (blinks == 0) return 1; // Si no hay blinks, la piedra permanece igual

    if (stone == 0) {
        // La piedra 0 siempre genera 1 piedra
        return pow(1, blinks);
    }

    string strStone = to_string(stone);
    int len = strStone.length();

    if (len % 2 == 0) {
        // Si el número tiene dígitos pares, genera 2 piedras
        return pow(2, blinks);
    } else {
        // Si el número tiene dígitos impares, genera 1 piedra
        return 1;
    }
}

// Función para calcular directamente el número total de piedras después de un número de blinks
long long calculateTotalStones(const vector<long long>& initialStones, int blinks) {
    long long totalStones = 0;

    for (long long stone : initialStones) {
        totalStones += calculateStoneGrowth(stone, blinks);
    }

    return totalStones;
}

int main() {
    // Configuración inicial de piedras
    vector<long long> stones = {8793800, 1629, 65, 5, 960, 0, 138983, 85629};

    cout << "Initial stones: ";
    for (long long stone : stones) {
        cout << stone << " ";
    }
    cout << "\nInitial count: " << stones.size() << " stones\n\n";

    // Número total de blinks
    int blinks = 75;

    // Calcular el número total de piedras tras 75 blinks
    long long totalStones = calculateTotalStones(stones, blinks);

    cout << "Number of stones after " << blinks << " blinks: " << totalStones << endl;

    return 0;
}
