#include <bits/stdc++.h>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

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

int part1(vector<vector<pair<int, int>>> a) {
    int rows = 103;
    int cols = 101;
    int i = 0;
    
    while (i < 100) {
        for (auto& v : a) {
            v[0].first = (v[0].first + v[1].first + cols) % cols;
            v[0].second = (v[0].second + v[1].second + rows) % rows;
        }
        i++;
    }

    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (auto v : a) {
        if (v[0].first < cols / 2 && v[0].second < rows / 2) {
            q1++;
        } else if (v[0].first > cols / 2 && v[0].second < rows / 2) {
            q2++;
        } else if (v[0].first < cols / 2 && v[0].second > rows / 2) {
            q3++;
        } else if (v[0].first > cols / 2 && v[0].second > rows / 2) {
            q4++;
        }
    }

    return q1 * q2 * q3 * q4;
}

bool inBounds(int r, int c, int aRow, int aCol) {
    return r >= 0 && r < aRow && c >= 0 && c < aCol;
}

int dfs(int r, int c, vector<vector<char>> grid, unordered_set<pair<int, int>, pair_hash>& seen) {
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    if (seen.find(make_pair(r, c)) != seen.end() || !inBounds(r, c, grid.size(), grid[0].size())) {
        return 0;
    }
    if (grid[r][c] != '#') {
        return 0;
    }
    int res = 0;
    seen.insert(make_pair(r, c));
    res++;
    for (auto dir : dirs) {
        int nr = r + dir.first;
        int nc = c + dir.second;
        
        res += dfs(nr, nc, grid, seen);
    }
    return res;
}

int part2(vector<vector<pair<int, int>>> a) {
    int rows = 103;
    int cols = 101;
    int i = 1;
    int threshold = 100;
    while (i <= 10000) {
        for (auto& v : a) {
            v[0].first = (v[0].first + v[1].first + cols) % cols;
            v[0].second = (v[0].second + v[1].second + rows) % rows;
        }

        vector<vector<char>> grid(rows, vector<char>(cols, '.'));
        for (auto& v : a) {
            int x = v[0].first;
            int y = v[0].second;
            grid[y][x] = '#';
        }

        int best = INT_MIN;
        for (auto& v : a) {
            unordered_set<pair<int, int>, pair_hash> seen;
            int res = dfs(v[0].second, v[0].first, grid, seen);
            best = max(best, res);
        }

        if (best > threshold) {
            return i;
        }
        i++;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<pair<int, int>>> d;  

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<pair<int, int>> a;
            vector<string> split = splitString(line, ' ');
            for (auto x : split) {
                vector<string> xsplit = splitString(x, '=');
                vector<string> y = splitString(xsplit[1], ',');
                a.push_back(make_pair(stoi(y[0]), stoi(y[1])));
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
