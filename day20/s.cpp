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


int part1(vector<vector<char>> grid) {
    int s = 0;
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

    int original_dist = dijkstra(start, end, grid);
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '#') {
                grid[i][j] = '.';
                int dist = dijkstra(start, end, grid);
                if ((original_dist -  dist) >= 100) {
                    s++;
                }
                grid[i][j] = '#';
            }
        }
    }

    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<char>> grid;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<char> a;
            for (auto c : line) {
                a.push_back(c);
            }
            grid.push_back(a);
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(grid) << endl;

    return 0;
}
