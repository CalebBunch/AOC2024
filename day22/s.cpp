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

long long helper1(long long start, long long iters) {
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
        s += helper1(x, 2000);
    }
    return s;
}

pair<vector<long long>, vector<long long>> helper2(long long start, long long iters) {
    vector<long long> res1;
    vector<long long> res2;
    long long prev = start;
    long long curr = start;
    while (iters--) {
        curr ^= (curr * 64);
        curr %= 16777216;
        curr ^= (curr / 32);
        curr %= 16777216;
        curr ^= (curr * 2048);
        curr %= 16777216;
        res1.push_back((curr % 10) - (prev % 10));
        res2.push_back(curr % 10);
        prev = curr;
    }
    res1.push_back((curr % 10) - (prev % 10));
    res2.push_back(curr % 10);
    return {res1, res2};
}

long long part2(vector<long long> a) {
    long long s = LLONG_MIN;
    vector<vector<long long>> diff;
    vector<vector<long long>> seq;
    for (auto x : a) {
        pair<vector<long long>, vector<long long>> result = helper2(x, 2000);
        diff.push_back(result.first);
        seq.push_back(result.second);
    }

    map<tuple<int, int, int, int>, long long> rewards;
    unordered_map<int, set<tuple<int, int, int, int>>> seen;
    for (int i = 0; i < diff.size(); i++) {
        for (int j = 0; j < diff[i].size() - 4; j++) {
            tuple<int, int, int, int> cseq = make_tuple(diff[i][j], diff[i][j + 1], diff[i][j + 2], diff[i][j + 3]);
            if (seen[i].find(cseq) == seen[i].end()) {
                rewards[cseq] += seq[i][j + 3];
                seen[i].insert(cseq);
            }
        }
    }
    
    for (auto [k, v] : rewards) {
        s = max(v, s);
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
    cout << "Part 2: " << part2(a) << endl;

    return 0;
}
