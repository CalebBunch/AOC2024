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

bool all_z(unordered_map<string, tuple<int, string, string, string, int>> gates) {
    for (auto [k, v] : gates) {
        if (k[0] == 'z' && get<4>(v) == -1) {
            return false;
        }
    }
    return true;
}

unsigned long long part1(unordered_map<string, tuple<int, string, string, string, int>> gates) {
    priority_queue<pair<string, tuple<int, string, string, string, int>>, vector<pair<string, tuple<int, string, string, string, int>>>,
        function<bool(pair<string, tuple<int, string, string, string, int>>, pair<string, tuple<int, string, string, string, int>>)>> pq(
        [](const pair<string, tuple<int, string, string, string, int>>& a,
           const pair<string, tuple<int, string, string, string, int>>& b) {
           return get<0>(a.second) < get<0>(b.second);
        }
    );
    
    for (auto [k, v] : gates) {
        if (get<0>(v) != 2) {
            if (get<0>(gates[get<1>(v)]) == 2 && get<0>(gates[get<3>(v)]) == 2) {
                get<0>(gates[k]) = 2;
            } else if (get<0>(gates[get<1>(v)]) == 2 || get<0>(gates[get<3>(v)]) == 2) {
                get<0>(gates[k]) = 1;
            }
        }
        if (get<2>(v) != "") {
            pq.push({k, gates[k]});
        }
    }
  
    while (!all_z(gates) && !pq.empty()) {
        auto curr = pq.top();
        pq.pop();
        
        if (get<0>(curr.second) >= 2) {
            auto v = curr.second;
            auto first_gate = gates[get<1>(curr.second)];
            auto second_gate = gates[get<3>(curr.second)];
            bool flag = false;
            if (get<4>(first_gate) == -1) {
                flag = true;
                get<0>(gates[get<1>(curr.second)])++;
                pq.push({get<1>(curr.second), gates[get<1>(curr.second)]});
            } 

            if (get<4>(second_gate) == -1) {
                flag = true;
                get<0>(gates[get<3>(curr.second)])++;
                pq.push({get<3>(curr.second), gates[get<3>(curr.second)]});
            }
            if (flag) {
                pq.push(curr);
                continue;
            }

            if (get<2>(curr.second) == "OR") {
                get<4>(gates[curr.first]) = get<4>(gates[get<1>(curr.second)]) | get<4>(gates[get<3>(curr.second)]);
            } else if (get<2>(curr.second) == "AND") {
                get<4>(gates[curr.first]) = get<4>(gates[get<1>(curr.second)]) & get<4>(gates[get<3>(curr.second)]);
            } else if (get<2>(curr.second) == "XOR") {
                get<4>(gates[curr.first]) = get<4>(gates[get<1>(curr.second)]) ^ get<4>(gates[get<3>(curr.second)]);
            } 
        } else {
            if (get<0>(gates[get<1>(curr.second)]) != -1 && get<0>(gates[get<3>(curr.second)]) != -1) {
                get<0>(gates[curr.first]) = 2;
            } else if (get<0>(gates[get<1>(curr.second)]) != -1 || get<0>(gates[get<3>(curr.second)]) != -1) {
                get<0>(gates[curr.first]) = 1;
            } 
            pq.push({curr.first, gates[curr.first]});
        }
    }

    vector<string> zs;
    for (auto [k, v] : gates) {
        if (k[0] == 'z') {
            zs.push_back(k);
        }
    }
    
    sort(zs.begin(), zs.end());
    vector<bool> result(zs.size());

    for (int i = 0; i < zs.size(); i++) {
        result[i] = get<4>(gates[zs[i]]);
    }

    unsigned long long final_result = 0;
    for (int i = 0; i < zs.size(); i++) {
        if (result[i]) {
            final_result |= (1ULL << i);
        }
    }

    return final_result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    unordered_map<string, tuple<int, string, string, string, int>> gates;
    bool flag = false;


    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "") {
                flag = true;
                continue;
            }
            if (!flag) {
                vector<string> split = splitString(line, ':');
                gates[split[0]] = {2, "", "", "", split[1][1] - '0'};
            } else {
                vector<string> split = splitString(line, ' ');
                gates[split[4]] = {0, split[0], split[1], split[2], -1};
            }
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(gates) << endl;
    return 0;
}
