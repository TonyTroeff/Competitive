#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct box {
    ll a, b, c;
};

ll solve_part_one(const vector<box>& boxes) {
    ll ans = 0;
    for (const auto&[a, b, c] : boxes) {
        ll s1 = a * b, s2 = b * c, s3 = a * c;
        ans += 2 * (s1 + s2 + s3) + min(s1, min(s2, s3));
    }

    return ans;
}

ll solve_part_two(const vector<box>& boxes) {
    ll ans = 0;

    for (const auto&[a, b, c] : boxes) {
        ll hp1 = a + b, hp2 = b + c, hp3 = a + c;
        ans += 2 * min(hp1, min(hp2, hp3)) + a * b * c;
    }

    return ans;
}

int main() {
    ifstream in("Day 2.input.txt");

    string line;
    vector<box> boxes;
    while (getline(in, line)) {
        istringstream iss(line);

        ll a, b, c;
        iss >> a;
        iss.ignore(1, 'x');
        iss >> b;
        iss.ignore(1, 'x');
        iss >> c;

        boxes.push_back({a, b, c});
    }

    cout << "Part one: " << solve_part_one(boxes) << endl;
    cout << "Part one: " << solve_part_two(boxes) << endl;
}