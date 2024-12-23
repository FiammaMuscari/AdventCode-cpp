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

public:
    void addConnection(const std::string& connection) {
        size_t pos = connection.find('-');
        if (pos != std::string::npos) {
            std::string comp1 = connection.substr(0, pos);
            std::string comp2 = connection.substr(pos + 1);
            addEdge(comp1, comp2);
        }
    }

    int findTrianglesWithT() {
        std::vector<std::string> nodesList(nodes.begin(), nodes.end());
        std::vector<std::vector<std::string>> triangles;
        
        for (size_t i = 0; i < nodesList.size(); ++i) {
            for (size_t j = i + 1; j < nodesList.size(); ++j) {
                if (!areConnected(nodesList[i], nodesList[j])) continue;
                
                for (size_t k = j + 1; k < nodesList.size(); ++k) {
                    if (areConnected(nodesList[i], nodesList[k]) && 
                        areConnected(nodesList[j], nodesList[k])) {
                        
                        if (nodesList[i][0] == 't' || 
                            nodesList[j][0] == 't' || 
                            nodesList[k][0] == 't') {
                            
                            std::vector<std::string> triangle = {nodesList[i], nodesList[j], nodesList[k]};
                            std::sort(triangle.begin(), triangle.end());
                            triangles.push_back(triangle);
                            
                            std::cout << triangle[0] << "," << triangle[1] << "," 
                                     << triangle[2] << std::endl;
                        }
                    }
                }
            }
        }
        return triangles.size();
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

    std::cout << "Triangles containing a computer starting with 't':" << std::endl;
    int result = analyzer.findTrianglesWithT();
    std::cout << "\nTotal number of triangles with 't': " << result << std::endl;

    return 0;
}