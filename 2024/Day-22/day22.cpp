#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long long calculateNextSecret(long long secret) {
    long long result = secret * 64;
    secret ^= result;
    secret %= 16777216;
    

    result = secret / 32;
    secret ^= result;
    secret %= 16777216; 
    
    result = secret * 2048;
    secret ^= result;
    secret %= 16777216; 
    
    return secret;
}

long long generateNthSecret(long long initialSecret, int n) {
    long long secret = initialSecret;
    for (int i = 0; i < n; i++) {
        secret = calculateNextSecret(secret);
    }
    return secret;
}

int main() {
    ifstream inputFile("input.txt");
    vector<long long> initialSecrets;
    long long secret;
    
    if (!inputFile.is_open()) {
        cout << "Error al abrir input.txt" << endl;
        return 1;
    }
    

    while (inputFile >> secret) {
        initialSecrets.push_back(secret);
    }
    
    inputFile.close();

    long long sum = 0;
    for (long long initialSecret : initialSecrets) {
        long long secret2000 = generateNthSecret(initialSecret, 2000);
        sum += secret2000;
    }
    
    cout << "La suma de los secretos numero 2000 es: " << sum << endl;
    
    return 0;
}