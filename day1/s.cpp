#include <bits/stdc++.h>

using namespace std;

vector<string> splitString(string str, char splitter){
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

int part1(vector<int> a, vector<int> b) {
    int s = 0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < a.size(); i++) {
        s += (abs(a[i] - b[i]));
    }
    return s;
}

int part2(vector<int> a, vector<int> b) {
    int s = 0;
    for (auto x : a) {
        s += count(b.begin(), b.end(), x) * x;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ifstream file("input.txt");
    vector<int> a;
    vector<int> b;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> splt = splitString(line, ' ');
            a.push_back(stoi(splt[0]));
            b.push_back(stoi(splt[1]));
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(a, b) << endl;
    cout << "Part 2: " << part2(a, b) << endl;

    return 0;
}
