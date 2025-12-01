#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 100

ll solve_part_one(const vector<pair<char, ll>>& rotations) {
    ll ans = 0, pos = 50;
    for (const auto&[direction, amount]: rotations) {
        if (direction == 'L') pos = (MOD + pos - amount % MOD) % MOD;
        else pos = (pos + amount) % MOD;

        if (pos == 0) ans++;
    }

    return ans;
}

ll solve_part_two(const vector<pair<char, ll>>& rotations) {
    ll ans = 0, pos = 50;
    for (auto [direction, amount]: rotations) {
        ans += amount / MOD;
        amount %= MOD;

        const ll original_pos = pos;
        if (direction == 'L') pos = pos - amount;
        else pos = pos + amount;

        if (pos >= MOD) {
            ans++;
            pos -= MOD;
        } else if (pos <= 0) {
            if (original_pos > 0) ans++;
            if (pos < 0) pos += MOD;
        }
    }

    return ans;
}

int main() {
    ifstream in("Day 1.input.txt");

    vector<pair<char, ll>> rotations;

    char direction;
    ll amount;
    while (in >> direction >> amount) rotations.emplace_back(direction, amount);

    cout << "Part one: " << solve_part_one(rotations) << endl;
    cout << "Part two: " << solve_part_two(rotations) << endl;
}