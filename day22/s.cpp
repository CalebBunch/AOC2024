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

long long helper(long long start, long long iters) {
    while (iters--) {
        start ^= (start * 64);
        start %= 16777216;
        start ^= (start / 32);
        start %= 16777216;
        start ^= (start * 2048);
        start %= 16777216;
    }
    return start;
}

long long part1(vector<long long> a) {
    long long s = 0;
    for (auto x : a) {
        s += helper(x, 2000);
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<long long> a;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            a.push_back(stoll(line)); 
        }

    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(a) << endl;

    return 0;
}
