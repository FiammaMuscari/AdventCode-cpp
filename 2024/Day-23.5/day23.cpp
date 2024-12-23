#include <fstream>      
#include <iostream>     
#include <string>       
#include <vector>       
#include <set>         
#include <map>         
#include <sstream>     
#include <algorithm>   

class NetworkAnalyzer {
private:
    std::map<std::string, std::set<std::string>> graph;
    std::set<std::string> nodes;

    void addEdge(const std::string& a, const std::string& b) {
        graph[a].insert(b);
        graph[b].insert(a);
        nodes.insert(a);
        nodes.insert(b);
    }

    bool areConnected(const std::string& a, const std::string& b) const {
        return graph.at(a).find(b) != graph.at(a).end();
    }

    bool isClique(const std::vector<std::string>& nodeSet) {
        for (size_t i = 0; i < nodeSet.size(); ++i) {
            for (size_t j = i + 1; j < nodeSet.size(); ++j) {
                if (!areConnected(nodeSet[i], nodeSet[j])) {
                    return false;
                }
            }
        }
        return true;
    }

    void findMaxCliqueRecursive(std::vector<std::string>& currentClique, 
                               std::vector<std::string>& candidates,
                               std::vector<std::string>& maxClique) {
        if (candidates.empty()) {
            if (currentClique.size() > maxClique.size()) {
                maxClique = currentClique;
            }
            return;
        }

        while (!candidates.empty()) {
            std::string v = candidates.back();
            candidates.pop_back();

            bool canAdd = true;
            for (const auto& u : currentClique) {
                if (!areConnected(u, v)) {
                    canAdd = false;
                    break;
                }
            }

            if (canAdd) {
                currentClique.push_back(v);
                
                std::vector<std::string> newCandidates;
                for (const auto& u : candidates) {
                    bool connected = true;
                    for (const auto& w : currentClique) {
                        if (!areConnected(u, w)) {
                            connected = false;
                            break;
                        }
                    }
                    if (connected) {
                        newCandidates.push_back(u);
                    }
                }

                findMaxCliqueRecursive(currentClique, newCandidates, maxClique);
                currentClique.pop_back();
            }
        }
    }

public:
    void addConnection(const std::string& connection) {
        size_t pos = connection.find('-');
        if (pos != std::string::npos) {
            std::string comp1 = connection.substr(0, pos);
            std::string comp2 = connection.substr(pos + 1);
            addEdge(comp1, comp2);
        }
    }

    std::string findLANPartyPassword() {
        std::vector<std::string> nodesList(nodes.begin(), nodes.end());
        std::vector<std::string> currentClique;
        std::vector<std::string> maxClique;
        
        findMaxCliqueRecursive(currentClique, nodesList, maxClique);
        
        std::sort(maxClique.begin(), maxClique.end());
        
        std::string password;
        for (size_t i = 0; i < maxClique.size(); ++i) {
            if (i > 0) password += ",";
            password += maxClique[i];
        }
        
        return password;
    }

};

int main() {
    NetworkAnalyzer analyzer;
    std::ifstream inputFile("input.txt");
    std::string line;

    if (!inputFile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            analyzer.addConnection(line);
        }
    }

    inputFile.close();

    std::cout << "\nPart 2 - Finding LAN Party Password:" << std::endl;
    std::string password = analyzer.findLANPartyPassword();
    std::cout << "Password: " << password << std::endl;

    return 0;
}