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
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

struct tuple_hash {
    template <class T1, class T2, class T3>
    std::size_t operator () (const tuple<T1, T2, T3>& t) const {
        auto h1 = pair_hash{}(get<0>(t));
        auto h2 = pair_hash{}(get<1>(t));
        auto h3 = hash<bool>{}(get<2>(t));
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

bool inBounds(int r, int c, int aRow, int aCol) {
    return r >= 0 && r < aRow && c >= 0 && c < aCol;
}

unordered_map<tuple<pair<int, int>, pair<int, int>, bool>, pair<int, vector<vector<pair<int, int>>>>, tuple_hash> cache;
pair<int, vector<vector<pair<int, int>>>> dijkstra(pair<int, int> start, pair<int, int> end, vector<vector<char>> grid, bool keypad_type) {
    auto cache_key = make_tuple(start, end, keypad_type);
    if (cache.find(cache_key) != cache.end()) {
        return cache[cache_key]; 
    }

    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    unordered_map<pair<int, int>, int, pair_hash> dist;
    unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> parents;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

    pq.push({0, start});
    dist[start] = 0;
    parents[start] = {start};

    while (!pq.empty()) {
        auto curr = pq.top();
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

    cache[cache_key] = {dist[end], all_paths};
    return {dist[end], all_paths};
}

vector<vector<char>> numeric_keypad = {{'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'}, {'#', '0', 'A'}};
vector<vector<char>> directional_keypad = {{'#', '^', 'A'}, {'<', 'v', '>'}};

unordered_map<char, pair<int, int>> numeric_keypad_table = {{'7', {0, 0}}, {'8', {0, 1}}, {'9', {0, 2}}, {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}}, {'1', {2, 0}}, {'2', {2, 1}}, {'3', {2, 2}}, {'#', {3, 0}}, {'0', {3, 1}}, {'A', {3, 2}}};
unordered_map<char, pair<int, int>> directional_keypad_table = {{'#', {0, 0}}, {'^', {0, 1}}, {'A', {0, 2}}, {'<', {1, 0}}, {'v', {1, 1}}, {'>', {1, 2}}};

map<pair<vector<pair<int, int>>, bool>, string> dfs_cache;
string dfs(vector<pair<int, int>> moves, vector<vector<char>> keypad, bool keypad_type) {
    if (dfs_cache.find(make_pair(moves, keypad_type)) != dfs_cache.end()) {
        return dfs_cache[make_pair(moves, keypad_type)];
    }
    string res;
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
    dfs_cache[make_pair(moves, keypad_type)] = res;
    return res;
}

vector<string> helper(char prev, char curr, vector<vector<char>> keypad, unordered_map<char, pair<int, int>> keypad_table, bool keypad_type) {
    pair<int, int> start = keypad_table[prev];
    pair<int, int> end = keypad_table[curr];
    pair<int, vector<vector<pair<int, int>>>> chres = dijkstra(start, end, keypad, keypad_type);
    vector<string> res;
    for (auto path : chres.second) {
        res.push_back(dfs(path, keypad, keypad_type));
    }
    return res;
}

unordered_map<pair<int, string>, long long, pair_hash> options_cache;
long long get_options(vector<string> codes, vector<vector<char>> keypad, unordered_map<char, pair<int, int>> keypad_table, int depth, bool keypad_type) {
    long long best = LLONG_MAX;
    for (auto code : codes) {
        if (depth == 0) {
            best = min(best, (long long) code.size());
        } else {
            char prev = 'A';
            long long csum = 0;
            for (auto c : code) {
                string str(1, prev);
                str.push_back(c);
                if (options_cache.find({depth, str}) != options_cache.end()) {
                    csum += options_cache[{depth, str}];
                } else {
                    vector<string> res = helper(prev, c, keypad, keypad_table, keypad_type);
                    long long final_options = get_options(res, keypad, keypad_table, depth - 1, keypad_type);
                    options_cache[{depth, str}] = final_options;
                    csum += final_options;
                }
                prev = c;
            }
            best = min(best, csum);
        }
    }

    return best;
}

vector<string> helper2(string code, vector<vector<char>> keypad, unordered_map<char, pair<int, int>> keypad_table, bool keypad_type) {
    pair<int, int> start = keypad_table['A'];
    vector<string> options(1);

    for (auto ch : code) {
        pair<int, int> end = keypad_table[ch];
        pair<int, vector<vector<pair<int, int>>>> chres = dijkstra(start, end, keypad, keypad_type);
        vector<string> new_options;

        for (auto& existing_path : options) {
            for (int i = 0; i < chres.second.size(); i++) {
                string dfsres = dfs(chres.second[i], keypad, keypad_type);

                string combined_path = existing_path;
                combined_path.insert(combined_path.end(), dfsres.begin(), dfsres.end());

                new_options.push_back(combined_path);
            }
        }
        options = new_options;
        start = end;
    }

    vector<string> noptions;
    for (auto& opt : options) {
        if (!opt.empty()) {
            noptions.push_back(opt);
        }
    }

    return noptions;
}

long long part1(vector<string> codes) {
    long long s = 0;
    for (auto code : codes) {
        vector<string> res1 = helper2(code, numeric_keypad, numeric_keypad_table, true);
        long long final_options = get_options(res1, directional_keypad, directional_keypad_table, 2, false);
        s += (final_options * stoll(code));
    }

    return s;
}

long long part2(vector<string> codes) {
    long long s = 0;
    for (auto code : codes) {
        vector<string> res1 = helper2(code, numeric_keypad, numeric_keypad_table, true);
        long long final_options = get_options(res1, directional_keypad, directional_keypad_table, 25, false);
        s += (final_options * stoll(code));
    }

    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<string> codes;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            codes.push_back(line);
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(codes) << endl;
    cout << "Part 2: " << part2(codes) << endl;

    return 0;
}
