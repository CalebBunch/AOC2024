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

void print_gate(string curr, unordered_map<string, tuple<int, string, string, string, int>> gates, int depth, int mdepth) {
    if (depth > mdepth) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        cout << " ";
    }
    string gate1 = get<1>(gates[curr]);
    string gate2 = get<3>(gates[curr]);
    cout << curr << " = " << gate1 << " " << get<2>(gates[curr]) << " " << gate2 << endl;
    if (gate1[0] != 'x' && gate1[0] != 'y') {
        print_gate(gate1, gates, depth + 1, mdepth);
    }
    if (gate2[0] != 'x' && gate2[0] != 'y') {
        print_gate(gate2, gates, depth + 1, mdepth);
    }
}

vector<string> part2(unordered_map<string, tuple<int, string, string, string, int>> gates) {
    // solved by inspection
    vector<string> result = {"z09", "cwt", "jmv", "css", "gdd", "z05", "z37", "pqt"};
    sort(result.begin(), result.end());
    return result;
}

void debug(unordered_map<string, tuple<int, string, string, string, int>> gates) {
    /*
    auto temp = gates["z09"];
    gates["z09"] = gates["cwt"];
    gates["cwt"] = temp;

    auto temp2 = gates["jmv"];
    gates["jmv"] = gates["css"];
    gates["css"] = temp2;

    auto temp3 = gates["gdd"];
    gates["gdd"] = gates["z05"];
    gates["z05"] = temp3;

    auto temp4 = gates["z37"];
    gates["z37"] = gates["pqt"];
    gates["pqt"] = temp4;
    */

    for (unsigned long long x = 0; x < 45; x++) {
        for (unsigned long long y = 0; y < 45; y++) {
            unsigned long long num1 = (1ULL << x);
            unsigned long long num2 = (1ULL << y);
            bitset x_bits = bitset<45>(num1);
            bitset y_bits = bitset<45>(num2);
            bitset x_y_bits = bitset<45>(num1 + num2);
            for (int i = 0; i < x_bits.size(); i++) {
                if (i < 10) {
                    get<4>(gates["x0" + to_string(i)]) = x_bits[i];
                } else {
                    get<4>(gates["x" + to_string(i)]) = x_bits[i];
                }
            }
            for (int i = 0; i < y_bits.size(); i++) {
                if (i < 10) {
                    get<4>(gates["y0" + to_string(i)]) = y_bits[i];
                } else {
                    get<4>(gates["y" + to_string(i)]) = y_bits[i];
                }
            }
            unsigned long long res = part1(gates);
            if (res != (num1 + num2)) {
                cout << "\ncircuit failed: got " << res << " but expected " << num1 + num2 << endl;
                cout << "circuit failed at bit x = " << x << " and bit y = " << y << endl;
                cout << "The following are relevant gates: \n\n";
                string z_gate = "z";
                if (y < 10) {
                    z_gate += "0";
                }
                z_gate += to_string(y);
                print_gate(z_gate, gates, 0, 5);
            }
        }
    }
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
    vector<string> res = part2(gates);
    cout << "Part 2: ";
    for (int i = 0; i < res.size(); i++) {
        if (i == res.size() - 1) {
            cout << res[i] << endl;
        } else {
            cout << res[i] << ",";
        }
    }

    return 0;
}
