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

struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

bool inBounds(int r, int c, int aRow, int aCol) {
    return r >= 0 && r < aRow && c >= 0 && c < aCol;
}

pair<int, vector<vector<pair<int, int>>>> dijkstra(pair<int, int> start, pair<int, int> end, vector<vector<char>> grid) {
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    unordered_map<pair<int, int>, int, pair_hash> dist;
    unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> parents;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

    pq.push({0, start});
    dist[start] = 0;
    parents[start] = {start};

    while (!pq.empty()) {
        pair<int, pair<int, int>> curr = pq.top();
        int current_dist = curr.first;
        pair<int, int> vertex = curr.second;
        pq.pop();

        if (vertex == end) {
            break;
        }

        for (auto d : dirs) {
            int nr = vertex.first + d.first;
            int nc = vertex.second + d.second;
            if (!inBounds(nr, nc, grid.size(), grid[0].size()) || grid[nr][nc] == '#') {
                continue;
            }

            int new_dist = current_dist + 1;
            if (dist.find({nr, nc}) == dist.end() || new_dist < dist[{nr, nc}]) {
                dist[{nr, nc}] = new_dist;
                parents[{nr, nc}] = {vertex};
                pq.push({new_dist, {nr, nc}});
            } else if (new_dist == dist[{nr, nc}]) {
                parents[{nr, nc}].push_back(vertex);
            }
        }
    }

    vector<vector<pair<int, int>>> all_paths;

    if (dist.find(end) == dist.end()) {
        return {-1, {}};
    }

    function<void(pair<int, int>, vector<pair<int, int>>)> backtrack = [&](pair<int, int> node, vector<pair<int, int>> path) {
        path.push_back(node);
        if (node == start) {
            reverse(path.begin(), path.end());
            all_paths.push_back(path);
            return;
        }
        for (auto& parent : parents[node]) {
            backtrack(parent, path);
        }
    };

    backtrack(end, {});

    return {dist[end], all_paths};
}

vector<vector<char>> numeric_keypad = {{'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'}, {'#', '0', 'A'}};
vector<vector<char>> directional_keypad = {{'#', '^', 'A'}, {'<', 'v', '>'}};

unordered_map<char, pair<int, int>> numeric_keypad_table = {{'7', {0, 0}}, {'8', {0, 1}}, {'9', {0, 2}}, {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}}, {'1', {2, 0}}, {'2', {2, 1}}, {'3', {2, 2}}, {'#', {3, 0}}, {'0', {3, 1}}, {'A', {3, 2}}};
unordered_map<char, pair<int, int>> directional_keypad_table = {{'#', {0, 0}}, {'^', {0, 1}}, {'A', {0, 2}}, {'<', {1, 0}}, {'v', {1, 1}}, {'>', {1, 2}}};


vector<char> dfs(vector<pair<int, int>> moves, vector<vector<char>> keypad) {
    vector<char> res;
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    pair<int, int> curr = moves[0];
    int idx = 0;
    while (idx < moves.size() - 1) {
        for (auto dir : dirs) {
            int nr = curr.first + dir.first;
            int nc = curr.second + dir.second;
            if (inBounds(nr, nc, keypad.size(), keypad[0].size()) && keypad[nr][nc] == keypad[moves[idx + 1].first][moves[idx + 1].second]) {
                if (dir == make_pair(-1, 0)) {
                    res.push_back('^');
                } else if (dir == make_pair(0, 1)) {
                    res.push_back('>');
                } else if (dir == make_pair(1, 0)) {
                    res.push_back('v');
                } else if (dir == make_pair(0, -1)) {
                    res.push_back('<');
                }
                idx++;
                curr = moves[idx];
                break;
            }
        }
    }
    res.push_back('A');
    return res;
}

vector<vector<char>> helper(vector<char> code, vector<vector<char>> keypad, unordered_map<char, pair<int, int>> keypad_table) {
    pair<int, int> start = keypad_table['A'];
    vector<vector<char>> options(1);

    for (auto ch : code) {
        pair<int, int> end = keypad_table[ch];
        pair<int, vector<vector<pair<int, int>>>> chres = dijkstra(start, end, keypad);
        vector<vector<char>> new_options;

        for (auto& existing_path : options) {
            for (int i = 0; i < chres.second.size(); i++) {
                vector<char> dfsres = dfs(chres.second[i], keypad);

                vector<char> combined_path = existing_path;
                combined_path.insert(combined_path.end(), dfsres.begin(), dfsres.end());

                new_options.push_back(combined_path);
            }
        }
        options = new_options;
        start = end;
    }

    vector<vector<char>> noptions;
    for (auto& opt : options) {
        if (!opt.empty()) {
            noptions.push_back(opt);
        }
    }

    return noptions;
}

long long part1(vector<vector<char>> codes) {
    long long s = 0;
    for (auto code : codes) {
        vector<vector<char>> options;
        vector<vector<char>> res1 = helper(code, numeric_keypad, numeric_keypad_table);
        for (auto opt1 : res1) {
            vector<vector<char>> res2 = helper(opt1, directional_keypad, directional_keypad_table);
            for (auto opt2 : res2) {
                vector<vector<char>> res3 = helper(opt2, directional_keypad, directional_keypad_table);
                for (auto opt3 : res3) {
                    options.push_back(opt3);
                }
            }
        }
        vector<char> smallest = options[0];
        for (auto o : options) {
            if (o.size() < smallest.size() && o.size() != 0) {
                smallest = o;
            }
        }
        string str(code.begin(), code.end() - 1);
        s += (((long long) smallest.size()) * stoll(str));
    }

    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<char>> codes;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<char> a;
            for (auto c : line) {
                a.push_back(c);
            }
            codes.push_back(a);
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(codes) << endl;

    return 0;
}
