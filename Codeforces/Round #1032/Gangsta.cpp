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

    string s;
    cin >> s;

    vector balance(n + 1, 0LL);
    for (int i = 0; i < n; i++) {
        balance[i + 1] = balance[i];
        if (s[i] == '1') balance[i + 1]++;
        else if (s[i] == '0') balance[i + 1]--;
    }

    // max_freq - min_freq = balance_diff
    // => min_freq = max_freq - balance_diff

    // max_freq + min_freq = length
    // => max_freq + (max_freq - balance_diff) = length
    // => max_freq = (length + balance_diff) / 2
    ll ans = 0;

    // Sum the length of all subarrays.
    for (int i = 1; i <= n; i++) ans += 1LL * (n - i + 1) * i;

    // Sum the absolute differences between any two values from `balance`.
    ranges::sort(balance);
    for (int i = 0; i <= n; i++) ans += balance[i] * (2 * i - n);

    cout << ans / 2 << endl;
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
