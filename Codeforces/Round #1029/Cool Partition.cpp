#include <bits/stdc++.h>
using namespace std;

#define ll long long

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    unordered_set<int> needed;
    unordered_set<int> seen;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        seen.insert(a[i]);
        needed.erase(a[i]);

        if (needed.empty()) {
            swap(seen, needed);
            ans++;
        }
    }

    cout << ans << endl;
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