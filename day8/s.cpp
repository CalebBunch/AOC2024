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

pair<int, set<pair<int, int>>> helper1(pair<int, int> p1, pair<int, int> p2, vector<vector<char>>& a, set<pair<int, int>>& seen) {
    // section formula (external only)
    pair<int, int> opt1 = make_pair((2 * p2.first - 1 * p1.first) / (2 - 1), (2 * p2.second - 1 * p1.second) / (2 - 1));
    pair<int, int> opt2 = make_pair((1 * p2.first - 2 * p1.first) / (1 - 2), (1 * p2.second - 2 * p1.second) / (1 - 2));
    
    vector<pair<int, int>> options = {opt1, opt2};
    int count = 0;
    for (auto& opt : options) {
        bool valid = inBounds(opt.first, opt.second, a.size(), a[0].size()) && seen.find(opt) == seen.end();
        if (valid) {
            seen.insert(opt);
            count++;
        }
    }

    return make_pair(count, seen);
}

int part1(vector<vector<char>>& a) {
    int s = 0;
    map<char, vector<pair<int, int>>> m;
    set<pair<int, int>> seen;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] != '.') {
                m[a[i][j]].push_back(make_pair(i, j));
            }
        }
    }
    for (auto& p : m) {
        for (int i = 0; i < p.second.size() - 1; i++) {
            for (int j = i + 1; j < p.second.size(); j++) {
                pair<int, set<pair<int, int>>> res = helper1(p.second[i], p.second[j], a, seen);
                s += res.first;
                seen = res.second;
            }
        }
    }
    return s;
}

pair<int, set<pair<int, int>>> helper2(pair<int, int> p1, pair<int, int> p2, vector<vector<char>>& a, set<pair<int, int>>& seen) {
    int dx = p2.first - p1.first;
    int dy = p2.second - p1.second;
    pair<int, int> s1 = p1;
    pair<int, int> s2 = p1;
    int count = 0;
    while (inBounds(s1.first, s1.second, a.size(), a[0].size()) || inBounds(s2.first, s2.second, a.size(), a[0].size())) {
        if (inBounds(s1.first, s1.second, a.size(), a[0].size()) && seen.insert(s1).second) {
            count++;
        }
        if (inBounds(s2.first, s2.second, a.size(), a[0].size()) && seen.insert(s2).second) {
            count++;
        }
        s1.first += dx;
        s1.second += dy;
        s2.first -= dx;
        s2.second -= dy;
    }
    return make_pair(count, seen);
}

int part2(vector<vector<char>>& a) {
    int s = 0;
    map<char, vector<pair<int, int>>> m;
    set<pair<int, int>> seen;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] != '.') {
                m[a[i][j]].push_back(make_pair(i, j));
            }
        }
    }
    for (auto& p : m) {
        for (int i = 0; i < p.second.size() - 1; i++) {
            for (int j = i + 1; j < p.second.size(); j++) {
                pair<int, set<pair<int, int>>> res = helper2(p.second[i], p.second[j], a, seen);
                s += res.first;
                seen = res.second;
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
                for (auto x : line) {
                    a.push_back(x);
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
