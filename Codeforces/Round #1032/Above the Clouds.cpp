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

    vector<char> s(n);
    for (char &el: s) cin >> el;

    unordered_map<char, int> freq;
    for (int i = 0; i < n; i++) freq[s[i]]++;

    bool ans = false;
    for (const auto &[el, freq]: freq) {
        if (freq >= 3 || (freq == 2 && (s[0] != el || s[n - 1] != el))) {
            ans = true;
            break;
        }
    }

    cout << (ans ? "YES" : "NO") << endl;
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
