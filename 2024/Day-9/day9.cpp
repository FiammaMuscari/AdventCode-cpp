#include <iostream>
#include <vector>
#include <fstream> // Include for file handling
#include <math.h>
#include <limits.h>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

// Function to read input from a file
vector<int> scanInput(const string& filename) {
    vector<int> res;
    string s;
    ifstream infile(filename);  

    if (infile.is_open()) {
        infile >> s;  
        for (auto c : s) res.push_back(c - '0');  
        infile.close();  
    } else {
        cerr << "Unable to open file: " << filename << endl;  
    }

    return res;
}

vector<int> getBlocks(vector<int>& input, int& limit) {
    vector<int> res;
    int sum = 0;
    int i = 0;
    while (sum + input[i] <= limit) {
        res.push_back(input[i]);
        sum += input[i];
        i++;
    }
    res.push_back(limit - sum);
    return res;
}

 
vector<vector<int>> getAssignment(vector<int>& blks, vector<int> files) {
    bool isFile = true;
    vector<vector<int>> res;
    int i = 0, j = files.size() - 1;

    for (auto b : blks) {
        if (isFile) {
            res.push_back({b, i});
            i++;
        } else {
            while (b >= files[j]) {
                res.push_back({files[j], j});
                b -= files[j];
                j--;
            }
            if (b > 0) res.push_back({b, j});
            files[j] -= b;
        }
        isFile = !isFile;
    }
    return res;
}

ll getAPSUM(int a, int n) {
    return (2 * a + n - 1) * n / 2; 
}

ll getCheckSum(vector<vector<int>>& assignment) {
    int i = 0;
    ll sum = 0;
    for (auto a : assignment) {
        sum += (a[1] * getAPSUM(i, a[0]));
        i += a[0];
    }
    return sum;  
}

void solve() {
    vector<int> input = scanInput("input.txt");  
    
    vector<int> files;
    bool isFile = true;
    int usedBlocks = 0;

    for (auto b : input) {
        if (isFile) {
            files.push_back(b);
            usedBlocks += b; 
        }
        isFile = !isFile; 
    }

    vector<int> blocks = getBlocks(input, usedBlocks);  
    vector<vector<int>> assignment = getAssignment(blocks, files);  

    cout << getCheckSum(assignment);  
}

int main() {
    
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
	int t = 1;  
 

	while (t != 0) {
		solve();  
		t--;
	}
}