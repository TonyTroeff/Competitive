#include <bits/stdc++.h>
using namespace std;

#define ll long long

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m);
    for (int &el: a) cin >> el;

    ranges::sort(a);

    for (int i = 0; i < n; i++) {
        int r1 = i / 2, r2 = m - (r1 + 1);
        if (i % 2 != 0) swap(r1, r2);

        cout << a[r1] << ' ' << a[r2] << ' ' << a[r1] << ' ' << a[r2] << ' ' << a[r1] << ' ' << a[r2] << endl;
    }
}

int main() {
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