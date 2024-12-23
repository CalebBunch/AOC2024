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

    return 0;
}
