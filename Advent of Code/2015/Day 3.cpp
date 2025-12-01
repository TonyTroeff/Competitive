#include <bits/stdc++.h>
using namespace std;

#define ll long long

void move(const char direction, pair<ll, ll>& pos) {
    if (direction == '^') pos.first++;
    else if (direction == '>') pos.second++;
    else if (direction == 'v') pos.first--;
    else if (direction == '<') pos.second--;
}

ll solve_part_one(const string &line) {
    pair<ll,ll> pos{0, 0};
    set<pair<ll, ll>> positions;
    positions.insert(pos);

    for (const char &s: line) {
        move(s, pos);
        positions.insert(pos);
    }

    return static_cast<ll>(positions.size());
}

ll solve_part_two(const string &line) {
    pair<ll,ll> pos{0, 0};
    set<pair<ll, ll>> positions;
    positions.insert(pos);

    for (int i = 0; i < line.length(); i += 2) {
        move(line[i], pos);
        positions.insert(pos);
    }

    pos = {0,0};
    for (int i = 1; i < line.length(); i += 2) {
        move(line[i], pos);
        positions.insert(pos);
    }

    return static_cast<ll>(positions.size());
}

int main() {
    ifstream in("Day 3.input.txt");

    string line;
    getline(in, line);

    cout << "Part one: " << solve_part_one(line) << endl;
    cout << "Part two: " << solve_part_two(line) << endl;
}
