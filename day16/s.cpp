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

unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> dirs = {
    {{1, 0}, {{1, 0}, {0, 1}, {0, -1}}},
    {{0, 1}, {{0, 1}, {1, 0}, {-1, 0}}},
    {{-1, 0}, {{-1, 0}, {0, -1}, {0, 1}}},
    {{0, -1}, {{0, -1}, {-1, 0}, {1, 0}}}
};

long long dijkstra(pair<int, int> start, pair<int, int> end, pair<int, int> odir, vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    priority_queue<tuple<long long, pair<int, int>, pair<int, int>>, vector<tuple<long long, pair<int, int>, pair<int, int>>>, greater<>> pq;

    vector<vector<vector<long long>>> dist(rows, vector<vector<long long>>(cols, vector<long long>(4, LLONG_MAX)));
    
    vector<pair<int, int>> direction_list = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    
    dist[start.first][start.second][0] = 0;
    pq.push({0, start, {0, 1}});

    while (!pq.empty()) {
        auto [current_dist, current, prev_dir] = pq.top();
        pq.pop();

        int r = current.first;
        int c = current.second;
        
        if (current == end) {
            return current_dist;
        }

        for (auto dir : dirs[prev_dir]) {
            int nr = r + dir.first;
            int nc = c + dir.second;

            if (grid[nr][nc] == '#') {
                continue;
            }

            int dir_index = find(direction_list.begin(), direction_list.end(), dir) - direction_list.begin();
            long long new_dist = dir == prev_dir ? current_dist + 1 : current_dist + 1001;

            if (new_dist < dist[nr][nc][dir_index]) {
                dist[nr][nc][dir_index] = new_dist;
                pq.push({new_dist, {nr, nc}, dir});
            }
        }
    }

    return LLONG_MAX;
}

long long part1(vector<vector<char>>& grid) {
    pair<int, int> start;
    pair<int, int> end;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'S') {
                start = {i, j};
            } else if (grid[i][j] == 'E') {
                end = {i, j};
            }
        }
    }

    return dijkstra(start, end, {0, 1}, grid);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<char>> grid;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<char> row(line.begin(), line.end());
            grid.push_back(row);
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(grid) << endl;

    return 0;
}
