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
        switch (instructions[currInstruction]) {
            case '^': dir = dirs[0]; break;
            case '>': dir = dirs[1]; break;
            case 'v': dir = dirs[2]; break;
            case '<': dir = dirs[3]; break;
        }

        int nr = r + dir.first;
        int nc = c + dir.second;

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

void helper2(int r, int c, vector<vector<char>>& grid, vector<char> instructions) {
    int currInstruction = 0;
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    while (currInstruction < instructions.size()) {
        pair<int, int> dir;
        switch (instructions[currInstruction]) {
            case '^': dir = dirs[0]; break;
            case '>': dir = dirs[1]; break;
            case 'v': dir = dirs[2]; break;
            case '<': dir = dirs[3]; break;
        }

        int nr = r + dir.first;
        int nc = c + dir.second;

        if (grid[nr][nc] == '.') {
            grid[r][c] = '.';
            r = nr;
            c = nc;
            grid[r][c] = '@';
        } 
        else if (grid[nr][nc] == '[' || grid[nr][nc] == ']') {
            vector<pair<pair<int, int>, char>> move;
            queue<pair<int, int>> q;
            set<pair<int, int>> seen; 

            q.push(make_pair(nr, nc));
            move.push_back(make_pair(make_pair(nr, nc), grid[nr][nc]));
            seen.insert(make_pair(nr, nc));

            if (grid[nr][nc] == '[') {
                q.push(make_pair(nr, nc + 1));
                move.push_back(make_pair(make_pair(nr, nc + 1), grid[nr][nc + 1]));
                seen.insert(make_pair(nr, nc + 1));
            } 
            else if (grid[nr][nc] == ']') {
                q.push(make_pair(nr, nc - 1));
                move.push_back(make_pair(make_pair(nr, nc - 1), grid[nr][nc - 1]));
                seen.insert(make_pair(nr, nc - 1));
            }

            while (!q.empty()) {
                pair<int, int> curr = q.front();
                q.pop();

                int gr = curr.first + dir.first;
                int gc = curr.second + dir.second;

                if (grid[gr][gc] == '#') {
                    break;
                }

                if (seen.find(make_pair(gr, gc)) != seen.end()) {
                    continue;
                }

                if (grid[gr][gc] == '[' || grid[gr][gc] == ']') {
                    q.push(make_pair(gr, gc));
                    seen.insert(make_pair(gr, gc));
                    move.push_back(make_pair(make_pair(gr, gc), grid[gr][gc]));

                    if (grid[gr][gc] == '[') {
                        if (seen.find(make_pair(gr, gc + 1)) == seen.end()) {
                            q.push(make_pair(gr, gc + 1));
                            seen.insert(make_pair(gr, gc + 1));
                            move.push_back(make_pair(make_pair(gr, gc + 1), grid[gr][gc + 1]));
                        }
                    } 
                    else if (grid[gr][gc] == ']') {
                        if (seen.find(make_pair(gr, gc - 1)) == seen.end()) {
                            q.push(make_pair(gr, gc - 1));
                            seen.insert(make_pair(gr, gc - 1));
                            move.push_back(make_pair(make_pair(gr, gc - 1), grid[gr][gc - 1]));
                        }
                    }
                }
            }

            bool canMove = true;
            for (auto p : move) {
                if (grid[p.first.first + dir.first][p.first.second + dir.second] == '#') {
                    canMove = false;
                    break;
                }
            }
            if (canMove) {
                for (auto p : move) {
                    grid[p.first.first][p.first.second] = '.';
                }
                for (auto p : move) {
                    grid[p.first.first + dir.first][p.first.second + dir.second] = p.second;
                }
                grid[r][c] = '.';
                r = nr;
                c = nc;
                grid[r][c] = '@';
            } 
        }

        currInstruction++;
    }
}


long long part2(vector<vector<char>> grid, vector<char> instructions) {
    long long s = 0;
    vector<vector<char>> ngrid;
    for (auto v : grid) {
        vector<char> nrow;
        for (auto c : v) {
            if (c == '.') {
                nrow.push_back('.');
                nrow.push_back('.');
            } else if (c == 'O') {
                nrow.push_back('[');
                nrow.push_back(']');
            } else if (c == '#') {
                nrow.push_back('#');
                nrow.push_back('#');
            } else if (c == '@') {
                nrow.push_back('@');
                nrow.push_back('.');
            }
        }
        ngrid.push_back(nrow);
    }
    
    grid = ngrid;

    bool found = false;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                helper2(i, j, grid, instructions);
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
            if (grid[i][j] == '[') {
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
    cout << "Part 2: " << part2(grid, instructions) << endl;

    return 0;
}
