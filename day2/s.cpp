#include <bits/stdc++.h>

using namespace std;

template <typename T>
void printVector(vector<T> a) {
    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
}

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

bool increasing(vector<int> a) {
    int i = 1;
    while (i < a.size()) {
        if (a[i - 1] >= a[i] || abs(a[i - 1] - a[i]) < 1 || abs(a[i - 1] - a[i]) > 3) {
            return false;
        }
        i++;
    }
    return true;
}

bool decreasing(vector<int> a) {
    int i = 1;
    while (i < a.size()) {
        if (a[i - 1] <= a[i] || abs(a[i - 1] - a[i]) < 1 || abs(a[i - 1] - a[i]) > 3) {
            return false;
        }
        i++;
    }
    return true;
}

int part1(vector<vector<int>> r) {
    int s = 0;
    for (auto a : r) {
        if (increasing(a) || decreasing(a)) {
            s++;
        }
    }
    return s;
}

int part2(vector<vector<int>> r) {
    int s = 0;
    for (auto a : r) {
        if (increasing(a) || decreasing(a)) {
            s++;
            continue;
        }
        for (int i = 0; i < a.size(); i++) {
            vector<int> cp(a);
            cp.erase(cp.begin() + i);
            if (increasing(cp) || decreasing(cp)) {
                s++;
                break;
            }
        }
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    vector<vector<int>> d;
    
    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> splt = splitString(line, ' ');
            vector<int> a;
            for (auto x : splt) {
                a.push_back(stoi(x));
            }
            d.push_back(a);
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(d) << endl;
    cout << "Part 2: " << part2(d) << endl;

    return 0;
}
