#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n;
    cin >> n;

    const int k = 2 * n - 3;
    cout << k << endl;
    cout << 1 << ' ' << 1 << ' ' << n << endl;
    cout << 2 << ' ' << 2 << ' ' << n << endl;

    for (int i = 3; i < n; i++) {
        cout << i << ' ' << 1 << ' ' << i - 1 << endl;
        cout << i << ' ' << i << ' ' << n << endl;
    }

    cout << n << ' ' << 1 << ' ' << n - 1 << endl;
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
