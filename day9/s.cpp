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

long long part1(vector<char>& a) {
    long long s = 0;
    vector<string> p;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i] - '0'; j++) {
            if (i % 2 == 0) {
                p.push_back(to_string((int) (i / 2)));
            } else {
                p.push_back("s");
            }
        }
    }
    int i = 0;
    while (i < p.size()) {
        if (p[i] == "s") {
            if (p[p.size() - 1] != "s") {
                p[i] = p[p.size() - 1];
            } else {
                i--;
            }
            p.erase(p.end());
        }
        i++;
    }
    for (int i = 0; i < p.size(); i++) {
        s += (i * stoi(p[i]));
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<char> d;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            for (auto x : line) {
                d.push_back(x);
            }
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(d) << endl;

    return 0;
}
