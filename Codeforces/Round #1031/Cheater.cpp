#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

int simulate(const vector<int> &a, const vector<int> &b, const int &n) {
    int ai = 0, bi = 0;
    for (int i = 0; i < n; i++) {
        if (a[ai] > b[bi]) ai++;
        else bi++;
    }

    return ai;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    vector<int> b(n);
    for (int &el: b) cin >> el;

    vector<int> left_min(n);
    left_min[0] = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[left_min[i - 1]]) left_min[i] = i;
        else left_min[i] = left_min[i - 1];
    }

    vector<int> right_max(n);
    right_max[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] > a[right_max[i + 1]]) right_max[i] = i;
        else right_max[i] = right_max[i + 1];
    }

    int l = simulate(a, b, n), h = n;
    while (l < h - 1) {
        const int m = l + (h - l) / 2;

        swap(a[left_min[m - 1]], a[right_max[m]]);

        if (simulate(a, b, n) >= m) l = m;
        else h = m;

        swap(a[left_min[m - 1]], a[right_max[m]]);
    }

    cout << l << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();

#ifdef SINGLE_TEST
    int t = 1;
#else
    int t;
    cin >> t;
#endif

    while (t--)
        solve();
}
