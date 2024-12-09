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
                p.push_back(to_string(i / 2)); 
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

long long part2(vector<char>& a) {
    long long s = 0;
    vector<pair<string, bool>> p;
    for (int i = 0; i < a.size(); i++) {
        bool isFile = false;
        string curr;
        for (int j = 0; j < a[i] - '0'; j++) {
            if (i % 2 == 0) {
                isFile = true;
                curr += to_string(i / 2);
            } else {
                string str(1, a[i]);
                p.push_back(make_pair("s" + str, false));
            }
        }
        if (isFile) {
            p.push_back(make_pair(curr, false));
        }
    }

    int i = p.size() - 1;
    while (i >= 0) {
        if (p[i].first[0] != 's') {
            for (int j = 0; j < i; j++) {
                int spaceSize = p[j].first[1] - '0';
                if (p[j].first[0] == 's' && spaceSize >= p[i].first.size() && !p[i].second) {
                    vector<string> src;
                    src.push_back(p[i].first);

                    string r;
                    int cnt = 0;
                    
                    for (int k = 0; k < p[i].first.size(); k++) {
                        p[j + k] = make_pair(p[i].first[0], true);
                        cnt++;                        
                        for (int l = k + 1; l < spaceSize; l++) {
                            p[j + l].first[1] = (spaceSize - cnt) + '0'; 
                        }

                    }

                    for (int k = 0; k < p[i].first.size(); k++) {
                        r += ("s" + to_string(p[i].first.size()));
                    }

                    p[i] = make_pair(r, false);
                
                    break;
                }
            }
        }
        i--;
    }
    /*
    cout << endl;
    for (auto c : p) {
        cout << c.first << " ";
    }
    cout << endl;
    */
    int cnt = 0;
    for (int i = 0; i < p.size(); i++) {
        if (p[i].first[0] != 's') {
            for (auto c : p[i].first) {
                // cout << c << " " << cnt << " " << (c - '0') * cnt<< endl;
                s += ((c - '0') * cnt);
                cnt++;
            }
        } else {
            cnt += count(p[i].first.begin(), p[i].first.end(), 's');
        }
    } 
    // cout << endl;
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
    cout << "Part 2: " << part2(d) << endl;

    return 0;
}

