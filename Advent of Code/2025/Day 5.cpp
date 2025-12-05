#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define UNKNOWN (-1)

// NOTE: Tony Troeff, 05/12/2025 - The solution for "Part #1" can be improved to use binary search after resolving overlapping intervals, but... it seems like overkill.
ll solve_part_one(const vector<pair<ll, ll>> &ranges, const vector<ll> &ids) {
    ll ans = 0;

    for (const ll &id: ids) {
        if (ranges::any_of(ranges, [&id](const pair<ll, ll> &r) { return r.first <= id && id <= r.second; }))
            ans++;
    }

    return ans;
}

ll solve_part_two(const vector<pair<ll, ll>> &ranges) {
    map<ll, int> m;

    for (const auto &[start, end]: ranges) {
        m[start]++;
        m[end + 1]--;
    }

    ll ans = 0, interval_begin = UNKNOWN;
    int acc = 0;
    for (const auto &[key, value]: m) {
        if (interval_begin == UNKNOWN) interval_begin = key;

        acc += value;
        if (acc == 0) {
            ans += key - interval_begin;
            interval_begin = UNKNOWN;
        }
    }

    return ans;
}

int main() {
    ifstream in("Day 5.input.txt");

    vector<pair<ll, ll>> ranges;

    string line;
    while (getline(in, line) && !line.empty()) {
        istringstream iss(line);

        ll start, end;
        iss >> start;
        iss.ignore(1, '-');
        iss >> end;

        ranges.emplace_back(start, end);
    }

    vector<ll> ids;
    while (getline(in, line)) {
        istringstream iss(line);

        ll current_id;
        iss >> current_id;
        ids.push_back(current_id);
    }

    cout << "Part one: " << solve_part_one(ranges, ids) << endl;
    cout << "Part two: " << solve_part_two(ranges) << endl;
}
