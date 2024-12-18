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

int dijkstra(pair<int, int> start, pair<int, int> end, vector<vector<char>> grid) {
    pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    unordered_map<pair<int, int>, int, pair_hash> dist;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    pq.push({0, start});
    dist[start] = 0;
    while (!pq.empty()) {
        pair<int, pair<int, int>> curr = pq.top();
        int current_dist = curr.first;
        pair<int, int> vertex = curr.second;
        pq.pop();

        if (vertex == end) {
            return current_dist;
        }
        for (auto d : dirs) {
            int nr = vertex.first + d.first;
            int nc = vertex.second + d.second;
            if (!inBounds(nr, nc, grid.size(), grid[0].size()) || grid[nr][nc] == '#') {
                continue;
            }
            if (dist.find({nr, nc}) == dist.end() || current_dist + 1 < dist[{nr, nc}]) {
                dist[{nr, nc}] = current_dist + 1;
                pq.push({current_dist + 1, {nr, nc}});
            }
        }
    }

    return -1;
}

int part1(vector<pair<int, int>> blocks) {
    pair<int, int> start = {0, 0};
    pair<int, int> end = {70, 70};
    vector<vector<char>> grid(71, vector<char>(71, '.')); 
    for (int i = 0; i < 1024; i++) {
        pair<int, int> b = blocks[i];
        grid[b.second][b.first] = '#';
    }
    
    return dijkstra(start, end, grid);
}

pair<int, int> part2(vector<pair<int, int>> blocks) {
    pair<int, int> start = {0, 0};
    pair<int, int> end = {70, 70};
    vector<vector<vector<char>>> grid_options;
    vector<vector<char>> prev(71, vector<char>(71, '.'));
    
    for (auto b : blocks) {
        vector<vector<char>> curr = prev;
        curr[b.second][b.first] = '#';
        grid_options.push_back(curr);
        prev = curr;
    }

    int low = 1;
    int high = grid_options.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int r1 = dijkstra(start, end, grid_options[mid - 1]);
        int r2 = dijkstra(start, end, grid_options[mid]);
        if (r1 != -1 && r2 == -1) {
            return {blocks[mid]};
        } else if (r1 == -1 && r2 == -1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return {-1, -1};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<pair<int, int>> blocks;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> a = splitString(line, ',');
            blocks.push_back(make_pair(stoi(a[0]), stoi(a[1])));
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(blocks) << endl;
    pair<int, int> res2 = part2(blocks);
    cout << "Part 2: " << res2.first << "," << res2.second << endl;
    return 0;
}
