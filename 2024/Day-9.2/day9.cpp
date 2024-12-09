#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <list>
#include <fstream>

using namespace std;
typedef long long ll;

vector<int> scanInput() {
    vector<int> res;
    ifstream infile("input.txt"); 
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return res; 
    }

    string s;
    infile >> s;
    for (auto c : s) res.push_back(c - '0');
    infile.close(); 
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
            cout << "Assigned block size " << b << " to file index " << i << endl; 
            i++;
        } else {
            while (b >= files[j]) {
                res.push_back({files[j], j});
                cout << "Assigned remaining space " << files[j] << " to block index " << j << endl; 
                b -= files[j];
                j--;
            }
            if (b > 0) {
                res.push_back({b, j});
                cout << "Assigned remaining space " << b << " to block index " << j << endl; 
            }
            files[j] -= b;
        }
        isFile = !isFile;
    }
    return res;
}

ll getAPSUM(int a, int n) {
    return (2 * a + n - 1) * n / 2;
}

ll getCheckSum(list<vector<int>>& assignment) {
    int i = 0;
    ll sum = 0;

    for (auto a : assignment) {
        if (a[1]) 
            sum += (a[2] * getAPSUM(i, a[0]));
        i += a[0];
    }

    cout << "Checksum calculated: " << sum << endl; 
    return sum;
}

void compaction(list<vector<int>>& blks, vector<int> files) {
    int n = files.size();

    for (int i = n - 1; i >= 0; i--) {
        auto itr = blks.begin();
        bool isfound = true;

        while (itr != blks.end() && ((*itr)[0] < files[i] || (*itr)[1])) {
            if ((*itr)[2] == i) {
                isfound = false;
                break;
            }
            itr++;
        }

        if (isfound) {
            if ((*itr)[0] == files[i]) {
                (*itr)[1] = 1; 
                (*itr)[2] = i; 
                cout << "Compacted: Block of size " << files[i] << " directly assigned." << endl; // Debug statement
            } else {
                int r = (*itr)[0] - files[i];
                (*itr)[0] = files[i];
                (*itr)[1] = 1; 
                (*itr)[2] = i;

                itr++;
                blks.insert(itr, {r, 0, -1}); 
                cout << "Compacted: Block of size " << r << " created after assignment." << endl; // Debug statement
            }
        }
    }
}

void garbageCollect(list<vector<int>>& blks) {
    unordered_set<int> h;

    for (auto itr = blks.begin(); itr != blks.end(); itr++) {
        if (h.count((*itr)[2]) && (*itr)[1]) {
            (*itr)[1] = 0; 
            (*itr)[2] = -1; 
            cout << "Garbage collected from block index: " << distance(blks.begin(), itr) << endl; 
        }
        h.insert((*itr)[2]);
    }
}

void solve() {
    vector<int> input = scanInput();

    vector<int> files;
    bool isFile = true;
    list<vector<int>> blks;

    for (auto b : input) {
        if (isFile) {
            blks.push_back({b, 1, static_cast<int>(files.size())}); 
            files.push_back(b);
        } else {
            blks.push_back({b, 0, -1});
        }
        isFile = !isFile;
    }

    cout << "Initial blocks: ";
    for (const auto& blk : blks)
        cout << "[" << blk[0] << ", " << blk[1] << ", " << blk[2] << "] ";
    
    cout << endl;

    compaction(blks, files);
    
    garbageCollect(blks);
    
    cout << "Final checksum: " << getCheckSum(blks) << endl; 
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