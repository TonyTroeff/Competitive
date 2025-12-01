#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll solve_part_one(const string& line) {
    ll ans = 0;
    for (const char& letter : line) {
        if (letter == '(') ans++;
        else if (letter == ')') ans--;
    }

    return ans;
}

ll solve_part_two(const string& line) {
    ll floor = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '(') floor++;
        else if (line[i] == ')') floor--;

        if (floor < 0) return i + 1;
    }

    return -1;
}

int main() {
    ifstream in("Day 1.input.txt");

    string line;
    getline(in, line);

    cout << "Part one: " << solve_part_one(line) << endl;
    cout << "Part two: " << solve_part_two(line) << endl;
}