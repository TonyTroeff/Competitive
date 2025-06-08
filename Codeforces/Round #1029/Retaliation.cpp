#include <bits/stdc++.h>
using namespace std;

#define ll long long

// #define SINGLE_TEST

void init() {
}

bool can_explode(const int &n, const vector<ll> &a) {
    const ll diff = a[1] - a[0];

    for (int i = 2; i < n; i++) {
        if (a[i] - a[i - 1] != diff) return false;
    }

    const ll min_el = diff < 0 ? a[n - 1] : a[0];
    ll x = (min_el - abs(diff)) / (n + 1), y = x + abs(diff);
    if (x < 0 || y < 0) return false;
    if (diff > 0) swap(x, y);

    for (int i = 0; i < n; i++) {
        if (a[i] != x * (i + 1) + y * (n - i)) return false;
    }

    return true;
}

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (ll &el: a) cin >> el;

    cout << (can_explode(n, a) ? "YES" : "NO") << endl;
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
