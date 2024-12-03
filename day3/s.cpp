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

vector<string> combineNumbers(vector<char> d) {
    vector<string> b;
    string currentNumber = "";

    for (auto c : d) {
        if (isdigit(c)) {
            currentNumber += c;
        } else {
            if (!currentNumber.empty()) {
                b.push_back(currentNumber);
                currentNumber = "";
            }
            string s(1, c);
            b.push_back(s);
        }
    }

    if (!currentNumber.empty()) {
        b.push_back(currentNumber);
    }

    return b;
}

bool isnumber(string& s) {
    return (strspn(s.c_str(), "-.0123456789" ) == s.size());
}

int part1(vector<string> a) {
    int i = 0;
    int s = 0;
    while (i < a.size() - 7) {
        bool flag = true;
        if (a[i] == "m") {
            for (int j = 1; j < 8; j++) {
                if (j == 1 && a[i + j] != "u") {
                    flag = false;
                    break;
                }
                if (j == 2 && a[i + j] != "l") {
                    flag = false;
                    break;
                }
                if (j == 3 && a[i + j] != "(") {
                    flag = false;
                    break;
                }
                if (j == 4 && !isnumber(a[i + j])) {
                    flag = false;
                    break;
                }
                if (j == 5 && a[i + j] != ",") {
                    flag = false;
                    break;
                }
                if (j == 6 && !isnumber(a[i + j])) {
                    flag = false;
                    break;
                }
                if (j == 7 && a[i + j] != ")") {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                s += (stoi(a[i + 4]) * stoi(a[i + 6]));
            }
        }
        i++;
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
            for (auto c : line) {
                d.push_back(c);
            }
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << part1(combineNumbers(d)) << endl;

    return 0;
}
