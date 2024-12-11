#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

struct Range {
    long long start;
    long long length;
};

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

// Function to convert a single range through a conversion map
vector<Range> convertRange(Range inputRange, const vector<ConversionMap>& map) {
    vector<Range> unconverted = {inputRange};
    vector<Range> converted;
    
    for (const auto& cm : map) {
        vector<Range> remaining;
        
        for (const auto& range : unconverted) {
            long long rangeEnd = range.start + range.length;
            long long mapEnd = cm.sourceStart + cm.length;
            
            // Before mapping
            if (range.start < cm.sourceStart && range.start + range.length > cm.sourceStart) {
                remaining.push_back({range.start, cm.sourceStart - range.start});
            }
            
            // Overlap
            if (range.start < mapEnd && rangeEnd > cm.sourceStart) {
                long long overlapStart = max(range.start, cm.sourceStart);
                long long overlapEnd = min(rangeEnd, mapEnd);
                long long offset = cm.destinationStart - cm.sourceStart;
                
                converted.push_back({
                    overlapStart + offset,
                    overlapEnd - overlapStart
                });
            }
            
            // After mapping
            if (rangeEnd > mapEnd && range.start < mapEnd) {
                remaining.push_back({mapEnd, rangeEnd - mapEnd});
            }
            
            // Completely outside
            if (rangeEnd <= cm.sourceStart || range.start >= mapEnd) {
                remaining.push_back(range);
            }
        }
        
        unconverted = remaining;
    }
    
    // Add any remaining unconverted ranges
    converted.insert(converted.end(), unconverted.begin(), unconverted.end());
    
    return converted;
}

int main() {
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo input.txt" << endl;
        return 1;
    }
    
    // Read seed ranges
    string line;
    getline(inputFile, line);
    vector<Range> seedRanges;
    stringstream ss(line.substr(line.find(":") + 1));
    long long start, length;
    while (ss >> start >> length) {
        seedRanges.push_back({start, length});
    }
    
    getline(inputFile, line);  // Skip empty line
    
    // Read all conversion maps
    vector<ConversionMap> seedToSoil = readConversionMap(inputFile);
    vector<ConversionMap> soilToFertilizer = readConversionMap(inputFile);
    vector<ConversionMap> fertilizerToWater = readConversionMap(inputFile);
    vector<ConversionMap> waterToLight = readConversionMap(inputFile);
    vector<ConversionMap> lightToTemperature = readConversionMap(inputFile);
    vector<ConversionMap> temperatureToHumidity = readConversionMap(inputFile);
    vector<ConversionMap> humidityToLocation = readConversionMap(inputFile);
    
    // Process each initial range through all conversions
    long long lowestLocation = numeric_limits<long long>::max();
    
    for (const auto& seedRange : seedRanges) {
        vector<Range> currentRanges = {seedRange};
        
        // Convert through each map
        currentRanges = convertRange(seedRange, seedToSoil);
        for (auto& range : currentRanges) {
            vector<Range> temp = convertRange(range, soilToFertilizer);
            for (auto& r : temp) {
                vector<Range> temp2 = convertRange(r, fertilizerToWater);
                for (auto& r2 : temp2) {
                    vector<Range> temp3 = convertRange(r2, waterToLight);
                    for (auto& r3 : temp3) {
                        vector<Range> temp4 = convertRange(r3, lightToTemperature);
                        for (auto& r4 : temp4) {
                            vector<Range> temp5 = convertRange(r4, temperatureToHumidity);
                            for (auto& r5 : temp5) {
                                vector<Range> locationRanges = convertRange(r5, humidityToLocation);
                                for (const auto& loc : locationRanges) {
                                    lowestLocation = min(lowestLocation, loc.start);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    cout << "La ubicacion mas baja es: " << lowestLocation << endl;
    
    inputFile.close();
    return 0;
}