#include <bits/stdc++.h>

using namespace std;

vector<string> splitString(string str, char splitter) {
    vector<string> result;
    string current = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == splitter) {
            if (current != "") {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if (current.size() != 0) {
        result.push_back(current);
    }
    return result;
}

int part1(vector<vector<vector<char>>> locks, vector<vector<vector<char>>> keys) {
    int s = 0;
    
    vector<vector<int>> l_heights;
    for (auto lock : locks) {
        vector<int> curr_height;
        int rows = lock.size();
        int cols = lock[0].size();
        for (int c = 0; c < cols; c++) {
            int cnt = 0;
            for (int r = 0; r < rows; r++) {
                if (lock[r][c] == '#') {
                    cnt++;
                }
            }
            curr_height.push_back(cnt - 1);
        }
        l_heights.push_back(curr_height);
    }

    vector<vector<int>> k_heights;
    for (auto key : keys) {
        vector<int> curr_height;
        int rows = key.size();
        int cols = key[0].size();

        for (int c = 0; c < cols; c++) {
            int cnt = 0;
            for (int r = 0; r < rows; r++) {
                if (key[r][c] == '#') {
                    cnt++;
                }
            }
            curr_height.push_back(cnt - 1);
        }
        k_heights.push_back(curr_height);
    }

    for (int i = 0; i < l_heights.size(); i++) {
        for (int j = 0; j < k_heights.size(); j++) {
            bool good = true;
            for (int r = 0; r < l_heights[i].size(); r++) {
                if (l_heights[i][r] + k_heights[j][r] > locks[i][0].size()) {
                    good = false;
                    break;
                }
            }
            if (good) {
                s++;
            }
        }
    }

    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    vector<vector<vector<char>>> locks;
    vector<vector<vector<char>>> keys;
    vector<vector<char>> a;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "") {
                bool l = true;
                for (auto c : a[0]) {
                    if (c != '#') {
                        l = false;
                        keys.push_back(a);
                        break;
                    }
                }
                if (l) {
                    locks.push_back(a);
                }
                a = {};
                continue;
            }
            vector<char> d;
            for (auto c : line) {
                d.push_back(c);
            }
            a.push_back(d);
        }
        bool l = true;
        for (auto c : a[0]) {
            if (c != '#') {
                l = false;
                keys.push_back(a);
                break;
            }
        }
        if (l) {
            locks.push_back(a);
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(locks, keys) << endl;

    return 0;
}
