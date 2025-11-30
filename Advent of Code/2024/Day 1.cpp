#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll solve_part_one(vector<ll>& a, vector<ll>& b) {
    ranges::sort(a);
    ranges::sort(b);

    ll ans = 0;
    for (int i = 0; i < a.size(); i++)
        ans += abs(a[i] - b[i]);

    return ans;
}

ll solve_part_two(const vector<ll>& a, const vector<ll>& b) {
    unordered_map<ll, int> freq;
    for (const ll& el : b) freq[el]++;

    ll ans = 0;
    for (const ll& el : a)
        ans += freq[el] * el;

    return ans;
}

int main() {
    ifstream in("Day 1.input.txt");

    vector<ll> a, b;

    ll el1, el2;
    while (in >> el1 >> el2) {
        a.push_back(el1);
        b.push_back(el2);
    }

    cout << "Part one: " << solve_part_one(a, b) << endl;
    cout << "Part two: " << solve_part_two(a, b) << endl;
}