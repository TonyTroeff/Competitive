#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define UNKNOWN (-1)

int solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);
    for (int& el : a) cin >> el;
    for (int& el : b) cin >> el;

    int fixed_sum = UNKNOWN;
    for (int i = 0; i < n; i++) {
        if (b[i] == UNKNOWN) continue;

        const int candidate_sum = a[i] + b[i];
        if (fixed_sum != UNKNOWN && fixed_sum != candidate_sum) return 0;

        fixed_sum = candidate_sum;
    }

    if (fixed_sum != UNKNOWN) {
        for (int i = 0; i < n; i++) {
            if (b[i] != UNKNOWN) continue;

            const int diff = fixed_sum - a[i];
            if (diff < 0 || diff > k) return 0;
        }

        return 1;
    }

    const int l = *ranges::min_element(a), h = *ranges::max_element(a);
    return k - (h - l) + 1;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}