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

int part1(unordered_map<string, unordered_set<string>> graph) {
    int s = 0;
    unordered_set<string> seen;
    for (auto [vertex, adj] : graph) {
        if (vertex[0] == 't') {
            vector<string> adjList(adj.begin(), adj.end());
            for (int i = 0; i < adjList.size(); i++) {
                for (int j = i + 1; j < adjList.size(); j++) {
                    vector<string> curr = {vertex};
                    curr.push_back(adjList[i]);
                    curr.push_back(adjList[j]);
                    sort(curr.begin(), curr.end());
                    string curr_group = curr[0];
                    curr_group += curr[1];
                    curr_group += curr[2];
                    if (graph[adjList[i]].find(adjList[j]) != graph[adjList[i]].end() && 
                        graph[adjList[j]].find(adjList[i]) != graph[adjList[j]].end() &&
                        seen.find(curr_group) == seen.end()) {
                        seen.insert(curr_group);
                        s++;
                    }
                }
            }
        }
    }
    return s;
}

vector<string> part2(unordered_map<string, unordered_set<string>> graph) {
    vector<pair<string, unordered_set<string>>> g;
    for (auto [vertex, adj] : graph) {
        g.push_back({vertex, adj});
    }
    int best = INT_MIN;
    vector<string> best_res; 
    srand(time(0));
    int i = 1000;
    while (i--) {
        int random_idx = rand() % g.size();
        vector<string> res;
        vector<pair<string, unordered_set<string>>> cp = g;
        pair<string, unordered_set<string>> current = cp[random_idx];
        while (!cp.empty()) {
            bool good = true;
            for (auto vertex : res) {
                if (current.second.find(vertex) == current.second.end()) {
                    good = false;
                    break;
                }
            }
            if (good) {
                res.push_back(current.first);
            }
            cp.erase(cp.begin());
            if (!cp.empty()) {
                current = cp[0];
            }
        }

        if ((int) res.size() > best) {
            best = res.size();
            best_res = res;
        }
    }
    sort(best_res.begin(), best_res.end()); 
    return best_res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    unordered_map<string, unordered_set<string>> graph;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> a = splitString(line, '-');
            graph[a[0]].insert(a[1]);
            graph[a[1]].insert(a[0]);
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(graph) << endl;
    vector<string> result = part2(graph);
    cout << "Part 2: ";
    for (int i = 0; i < result.size(); i++) {
        if (i == result.size() - 1) {
            cout << result[i] << endl;
        } else {
            cout << result[i] << ",";
        }
    }

    return 0;
}
