#include <bits/stdc++.h>

using namespace std;

template <typename T>
void printVector(vector<T> a, string delim) {
    for (auto x : a) {
        cout << x << delim;
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

long long apply_operations(vector<long long>& nums, string ops) {
    long long res = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (ops[i - 1] == '+') {
            res += nums[i];
        } else {
            res *= nums[i];
        }
    }
    return res;
}

long long combinations(long long k, vector<long long>& s) {
    for (int i = 0; i < pow(2, s.size() - 1); i++) {
        string ops = "";
        for (int j = 0; j < s.size() - 1; j++) {
            if ((i >> j) & 1) {
                ops.push_back('+');
            } else {
                ops.push_back('*');
            }
        }
        if (apply_operations(s, ops) == k) {
            return k;
        }
    }
    return 0;
}

long long part1(map<long long, vector<long long>>& m) {
    long long s = 0;
    for (auto& p: m) {
        s += combinations(p.first, p.second);
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    map<long long, vector<long long>> m;
    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
                vector<string> a = splitString(line, ':');
                vector<long long> aa;
                for (auto x : splitString(a[1], ' ')) {
                    aa.push_back(stoll(x));
                }
                m[stoll(a[0])] = aa;
            }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(m) << endl;

    return 0;
}
