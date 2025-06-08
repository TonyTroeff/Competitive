#include <bits/stdc++.h>
using namespace std;

#define ll long long

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    int w = -1;
    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (a[i] != 1) continue;

        if (w == -1) {
            w = i + x - 1;
        } else if (i > w) {
            ans = false;
            break;
        }
    }

    cout << (ans ? "YES" : "NO") << endl;
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
