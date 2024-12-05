#include <bits/stdc++.h>

using namespace std;

template <typename T>
void printVector(vector<T> a) {
    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
}

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

int part1(vector<map<int, int>>& a, map<int, vector<int>>& b) {
    int s = 0;
    for (auto& x : a) {
        bool good = true;
        int mid = 0;
        int tIdx = x.size() / 2;
        for (auto& p : x) {
            if (p.second == tIdx) {
                mid = p.first;
            }
            if (b.find(p.first) != b.end()) {
                for (auto z : b[p.first]) {
                    if (x.find(z) != x.end() && x[z] < p.second) {
                        good = false;
                        break;
                    }
                }
            }
            if (!good) {
                break;
            }
        }
        if (good) {
            s += mid;
        }
    }
    return s;
}

int part2(vector<map<int, int>>& a, map<int, vector<int>>& b) {
    int s = 0;
    for (auto& x : a) {
        bool counted = false;
        for (auto& p : x) {
            if (b.find(p.first) != b.end()) {
                for (auto z : b[p.first]) {
                    if (x.find(z) != x.end() && x[z] < p.second) {
                        vector<int> y(x.size());
                        for (auto& pp : x) {
                            y[pp.second] = pp.first;
                        }
                        for (int i = 1; i < y.size(); i++) {
                            for (int j = i; j > 0; j--) {
                                if (b.find(y[j]) != b.end()) {
                                    for (auto zz : b[y[j]]) {
                                        if (y[j - 1] == zz) {
                                            int temp = y[j - 1];
                                            y[j - 1] = y[j];
                                            y[j] = temp;
                                        }
                                    }
                                }
                            }
                        }
                        s += y[(int)(y.size() / 2)];
                        counted = true;
                        break;
                    }
                }
            }
            if (counted) {
                break;
            }
        }
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<map<int, int>> d;
    map<int, vector<int>> e;
    bool update = false;
    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "") {
                update = true;
            }
            if (!update) {
                vector<string> a = splitString(line, '|');
                e[stoi(a[0])].push_back(stoi(a[1]));
            } else {
                vector<string> a = splitString(line, ',');
                map<int, int> m;
                for (int i = 0; i < a.size(); i++) {
                    m[stoi(a[i])] = i;
                }
                d.push_back(m);
            }
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(d, e) << endl;
    cout << "Part 2: " << part2(d, e) << endl;

    return 0;
}
