#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

struct ConversionMap {
    long long destinationStart;
    long long sourceStart;
    long long length;
};


vector<ConversionMap> readConversionMap(ifstream& file) {
    vector<ConversionMap> map;
    string line;
    
    getline(file, line);

    while (getline(file, line) && !line.empty()) {
        stringstream ss(line);
        ConversionMap cm;
        ss >> cm.destinationStart >> cm.sourceStart >> cm.length;
        map.push_back(cm);
    }
    
    return map;
}

long long convertNumber(long long number, const vector<ConversionMap>& map) {
    for (const auto& cm : map) {
        if (number >= cm.sourceStart && number < cm.sourceStart + cm.length) {
            return cm.destinationStart + (number - cm.sourceStart);
        }
    }
    return number; 
}

int main() {
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo input.txt" << endl;
        return 1;
    }
    
    string line;
    getline(inputFile, line);
    vector<long long> seeds;
    stringstream seedStream(line.substr(line.find(":") + 1));
    long long seed;
    while (seedStream >> seed) {
        seeds.push_back(seed);
    }
    
    getline(inputFile, line);
    
    vector<ConversionMap> seedToSoil = readConversionMap(inputFile);
    vector<ConversionMap> soilToFertilizer = readConversionMap(inputFile);
    vector<ConversionMap> fertilizerToWater = readConversionMap(inputFile);
    vector<ConversionMap> waterToLight = readConversionMap(inputFile);
    vector<ConversionMap> lightToTemperature = readConversionMap(inputFile);
    vector<ConversionMap> temperatureToHumidity = readConversionMap(inputFile);
    vector<ConversionMap> humidityToLocation = readConversionMap(inputFile);
    
    long long lowestLocation = numeric_limits<long long>::max();
    
    for (long long seed : seeds) {
        long long soil = convertNumber(seed, seedToSoil);
        long long fertilizer = convertNumber(soil, soilToFertilizer);
        long long water = convertNumber(fertilizer, fertilizerToWater);
        long long light = convertNumber(water, waterToLight);
        long long temperature = convertNumber(light, lightToTemperature);
        long long humidity = convertNumber(temperature, temperatureToHumidity);
        long long location = convertNumber(humidity, humidityToLocation);
        
        cout << "Seed " << seed << " -> Soil " << soil 
             << " -> Fertilizer " << fertilizer 
             << " -> Water " << water 
             << " -> Light " << light 
             << " -> Temperature " << temperature 
             << " -> Humidity " << humidity 
             << " -> Location " << location << endl;

        lowestLocation = min(lowestLocation, location);
    }
    
    cout << "La ubicacion mas baja es: " << lowestLocation << endl;
    
    inputFile.close();
    return 0;
}