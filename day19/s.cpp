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

bool helper1(string design, vector<string> patterns) {
    int n = design.size();
    vector<bool> m(n + 1, false);
    m[0] = true;
    for (int i = 0; i < n; i++) {
        if (m[i]) {
            for (auto p : patterns) {
                if (i + p.size() <= n && design.substr(i, p.size()) == p) {
                    m[i + p.size()] = true;
                }
            }
        }
    }
    return m[n];
}

int part1(vector<string> patterns, vector<string> designs) {
    int s = 0;
    for (auto d : designs) {
        if (helper1(d, patterns)) {
            s++;
        }
    }
    return s;
}

long long helper2(string design, vector<string> patterns) {
    int n = design.size();
    vector<long long> m(n + 1, 0);
    m[0] = 1;
    for (int i = 0; i < n; i++) {
        if (m[i] > 0) {
            for (auto p : patterns) {
                if (i + p.size() <= n && design.substr(i, p.size()) == p) {
                    m[i + p.size()] += m[i];
                }
            }
        }
    }
    return m[n];
}

long long part2(vector<string> patterns, vector<string> designs) {
    long long s = 0;
    for (auto d : designs) {
        s += helper2(d, patterns);
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<string> patterns;
    vector<string> designs;
    bool flag = false;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "") {
                flag = true;
            }
            if (!flag) {
                vector<string> split = splitString(line, ',');
                for (auto x : split) {
                    x.erase(remove_if(x.begin(), x.end(), [](unsigned char c) { return isspace(c); }), x.end());
                    patterns.push_back(x);
                }
            } else if (line != "") {
                designs.push_back(line);
            }
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(patterns, designs) << endl;
    cout << "Part 2: " << part2(patterns, designs) << endl;

    return 0;
}
