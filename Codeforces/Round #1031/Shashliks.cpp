#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

void solve() {
    int k, a, b, x, y;
    cin >> k >> a >> b >> x >> y;

    if (x > y) {
        swap(a, b);
        swap(x, y);
    }

    int ans = 0;

    const int d1 = k - a;
    if (d1 >= 0) ans += d1 / x + 1;

    const int d2 = k - ans * x - b;
    if (d2 >= 0) ans += d2 / y + 1;

    cout << ans << endl;
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
