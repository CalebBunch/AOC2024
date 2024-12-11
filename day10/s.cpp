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

bool inBounds(int r, int c, int aRow, int aCol) {
    return r >= 0 && r < aRow && c >= 0 && c < aCol;
}

pair<int, set<pair<int, int>>> dfs1(int r, int c, vector<vector<int>> a, set<pair<int, int>> seen) {
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    if (!inBounds(r, c, a.size(), a[0].size()) || seen.find(make_pair(r, c)) != seen.end()) {
        return make_pair(0, seen);
    }
    seen.insert(make_pair(r, c));
    if (a[r][c] == 9) {
        return make_pair(1, seen);
    }
    int res = 0;
    for (auto d : dirs) {
        int nr = r + d.first;
        int nc = c + d.second;
        if (inBounds(nr, nc, a.size(), a[0].size()) && a[nr][nc] == a[r][c] + 1) {
            pair<int, set<pair<int, int>>> sr = dfs1(nr, nc, a, seen);
            res += sr.first;
            seen = sr.second;
        }
    }
    return make_pair(res, seen);
}

int part1(vector<vector<int>>& a) {
    int s = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] == 0) {
                set<pair<int, int>> seen;
                pair<int, set<pair<int, int>>> res = dfs1(i, j, a, seen);
                s += res.first;
            }
        }
    }
    return s;
}

int dfs2(int r, int c, vector<vector<int>> a) {
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    if (!inBounds(r, c, a.size(), a[0].size())) {
        return 0;
    }
    if (a[r][c] == 9) {
        return 1;
    }
    int res = 0;
    for (auto d : dirs) {
        int nr = r + d.first;
        int nc = c + d.second;
        if (inBounds(nr, nc, a.size(), a[0].size()) && a[nr][nc] == a[r][c] + 1) {
            res += dfs2(nr, nc, a);
        }
    }
    return res;
}

int part2(vector<vector<int>>& a) {
    int s = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] == 0) {
                s += dfs2(i, j, a);
            }
        }
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<int>> d;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
                vector<int> a;
                for (auto x : line) {
                    a.push_back(x - '0');
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
