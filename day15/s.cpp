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

void helper1(int r, int c, vector<vector<char>>& grid, vector<char> instructions) {
    int currInstruction = 0;
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    while (currInstruction < instructions.size()) {
        pair<int, int> dir;
        if (instructions[currInstruction] == '^') {
            dir = dirs[0];
        } else if (instructions[currInstruction] == '>') {
            dir = dirs[1];
        } else if (instructions[currInstruction] == 'v') {
            dir = dirs[2];
        } else {
            dir = dirs[3];
        }

        int nr = r + dir.first;
        int nc = c + dir.second;
        if (!inBounds(nr, nc, grid.size(), grid[0].size())) {
            currInstruction++;
            continue;
        }
        if (grid[nr][nc] == '.') {
            grid[r][c] = '.';
            r = nr;
            c = nc;
            grid[r][c] = '@';
        } else if (grid[nr][nc] == 'O') {
            int gr = nr;
            int gc = nc;
            while (inBounds(nr, nc, grid.size(), grid[0].size()) && grid[nr][nc] != '.' && grid[nr][nc] != '#') {
                nr += dir.first;
                nc += dir.second;
            }
            if (!inBounds(nr, nc, grid.size(), grid[0].size())) {
                currInstruction++;
                continue;
            } else if (grid[nr][nc] == '#') {
                currInstruction++;
                continue;
            } else {
                grid[nr][nc] = 'O';
                grid[r][c] = '.';
                r = gr;
                c = gc;
                grid[r][c] = '@';
            }
        }
        currInstruction++;
    }
}

long long part1(vector<vector<char>> grid, vector<char> instructions) {
    long long s = 0;
    bool found = false;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                helper1(i, j, grid, instructions);
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'O') {
                s += (100 * i + j);
            }
        }
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<char>> grid;
    vector<char> instructions;
    bool flag = false;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "") {
                flag = true;
            }
            if (!flag) {
                vector<char> a;
                for (auto c : line) {
                    a.push_back(c);
                }
                grid.push_back(a);
            } else {
                for (auto c : line) {
                    instructions.push_back(c);
                }
            }
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(grid, instructions) << endl;

    return 0;
}
