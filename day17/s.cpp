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

vector<int> part1(vector<int> instructions, long long regA, long long regB, long long regC) {
    vector<int> res;
    int ptr = 0;
    while (ptr < instructions.size()) {
        int opcode = instructions[ptr];
        int operand = instructions[ptr + 1];

        if (opcode != 1 && opcode != 3) {
            if (operand == 4) {
                operand = regA;
            } else if (operand == 5) {
                operand = regB;
            } else if (operand == 6) {
                operand = regC;
            }
        }
        
        bool jump = false;
        if (opcode == 0) {
            regA /= pow(2, operand);
        } else if (opcode == 1) {
            regB ^= operand; 
        } else if (opcode == 2) {
            regB = operand % 8;
        } else if (opcode == 3) {
            if (regA != 0) {
                ptr = operand;
                jump = true;
            }
        } else if (opcode == 4) {
            regB ^= regC;
        } else if (opcode == 5) {
            res.push_back(operand % 8);
        } else if (opcode == 6) {
            regB = regA / pow(2, operand);
        } else if (opcode == 7) {
            regC = regA / pow(2, operand);
        }

        if (!jump) {
            ptr += 2;
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<int> instructions;
    long long a, b, c;
    bool flag = false;
    int count = 0;

    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "") {
                flag = true;
            }
            if (!flag) {
                long long r = stoll(splitString(line, ' ')[2]);
                if (count == 0) {
                    a = r;
                } else if (count == 1) {
                    b = r;
                } else {
                    c = r;
                }
            } else if (line != "") {
                vector<string> split = splitString(splitString(line, ' ')[1], ',');
                for (auto x : split) {
                    instructions.push_back(stoi(x));
                }
            }
            count++;
        }
    } else {
        cout << "Unable to read from input file\n";
        return 1;
    }

    cout << "Part 1: " << endl;
    vector<int> result = part1(instructions, a, b, c);
    for (auto it = result.begin(); it != result.end(); ++it) {
        cout << *it;
        if (it != result.end() - 1) {
            cout << ",";
        }
    }
    cout << endl;

    return 0;
}
