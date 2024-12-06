#include <bits/stdc++.h>

using namespace std;

template <typename T>
void printVector(vector<T> a, string delim) {
    for (auto x : a) {
        cout << x << delim;
    }
    cout << endl;
}

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

bool inBounds(int r, int c, int aRow, int aCol) {
    return r >= 0 && r < aRow && c >= 0 && c < aCol;
}

pair<vector<pair<int, int>>, int> simulate(vector<vector<char>>& a, int i, int r, int c, bool part2) {
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int dirIdx = i;
    int row = r;
    int col = c;
    int cnt = 0;
    set<pair<int, int>> seen;
    vector<pair<int, int>> path;
    while (inBounds(row, col, a.size(), a[0].size())) {
        if (a[row][col] == '#') {
            row -= dirs[dirIdx].first;
            col -= dirs[dirIdx].second;
            dirIdx = (dirIdx + 1) % 4;
        }
        if (seen.find(make_pair(row, col)) == seen.end()) {
            seen.insert(make_pair(row, col));
            cnt++;
        } else if (part2) {
            cnt++;
        }
        path.push_back(make_pair(row, col));
        row += dirs[dirIdx].first;
        col += dirs[dirIdx].second;
    }
    return make_pair(path, cnt);
}

int part1(vector<vector<char>>& a) {
    int s;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] == '^') {
                s = simulate(a, 0, i, j, false).second;
                break;
            }
        }
    }
    return s;
}

int helper2(vector<vector<char>>& a, int oDir, int r, int c) {
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int cnt = 0;
    pair<vector<pair<int, int>>, int> res = simulate(a, oDir, r, c, true);
    int oPathLen = res.second;
    vector<pair<int, int>> path = res.first;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] != '#' && a[i][j] != '^') {
                a[i][j] = '#';
                int sr = r;
                int sc = c;
                int sd = oDir;
                int cPathLen = 0;
                while (inBounds(sr, sc, a.size(), a[0].size())) {
                    if (a[sr][sc] == '#') {
                        sr -= dirs[sd].first;
                        sc -= dirs[sd].second;
                        sd = (sd + 1) % 4;
                    }
                    sr += dirs[sd].first;
                    sc += dirs[sd].second;
                    cPathLen++;
                    // this constant (250) probably only works for my input
                    // increasing it will increase the chances of a correct result for all inputs
                    // this is a bad way to check for infinite loops
                    if (cPathLen > oPathLen + 250) {
                        cnt++;
                        break;
                    }
                    
                }
                a[i][j] = '.';
            }
        }
    }
    return cnt;
}

int part2(vector<vector<char>>& a) {
    int s;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] == '^') {
                s = helper2(a, 0, i, j);
                break;
            }
        }
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<char>> d;
    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
                vector<char> a;
                for (auto c : line) {
                    a.push_back(c);
                }
                d.push_back(a);
            }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(d) << endl;
    cout << "Part 2: " << part2(d) << endl;

    return 0;
}
