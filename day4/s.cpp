#include <bits/stdc++.h>

using namespace std;

template <typename T>
void printVector(vector<T> a) {
    for (auto x : a) {
        cout << x << " ";
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

int helper1(int row, int col, vector<vector<char>> a) {
    int res = 0;

    pair<int, int> dirs[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (auto& dir : dirs) {
        bool f = true;
        int i = 0;
        int newRow = row;
        int newCol = col;
        while (i < 3) {
            newRow += dir.first;
            newCol += dir.second;
            if (inBounds(newRow, newCol, a.size(), a[0].size())) {
                if (i == 0 && a[newRow][newCol] != 'M') {
                    f = false;
                    break;
                }
                if (i == 1 && a[newRow][newCol] != 'A') {
                    f = false;
                    break;
                }
                if (i == 2 && a[newRow][newCol] != 'S') {
                    f = false;
                    break;
                }
            } else {
                f = false;
                break;
            }
            i++;
        }
        if (f) {
            res++; 
        }
    }
    return res;
}

int part1(vector<vector<char>> a) {
    int s = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] == 'X') {
                s += helper1(i, j, a);
            }
        }
    }  

    return s;
}

int helper2(int row, int col, vector<vector<char>> &a) {
    int res = 0;
    char tl, br, tr, bl;
    
    if (inBounds(row - 1, col - 1, a.size(), a[0].size())) {
        tl = a[row - 1][col - 1];
    } else {
        return 0;
    }
    if (inBounds(row + 1, col + 1, a.size(), a[0].size())) {
        br = a[row + 1][col + 1];
    } else {
        return 0;
    }
    if (inBounds(row - 1, col + 1, a.size(), a[0].size())) {
        tr = a[row - 1][col + 1]; 
    } else {
        return 0;
    }
    if (inBounds(row + 1, col - 1, a.size(), a[0].size())) {
        bl = a[row + 1][col - 1];
    } else {
        return 0;
    }

    bool cond1 = ((tl == 'M' || tl == 'S') && (br == 'M' || br == 'S') && tl != br);
    bool cond2 = ((tr == 'M' || tr == 'S') && (bl == 'M' || bl == 'S') && tr != bl);
    
    if (cond1 && cond2) {
        return 1; 
    }

    return 0;
}

int part2(vector<vector<char>> a) {
    int s = 0;
    for (int i = 1; i < a.size() - 1; i++) { 
        for (int j = 1; j < a[i].size() - 1; j++) {
            if (a[i][j] == 'A') {
                s += helper2(i, j, a);
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
