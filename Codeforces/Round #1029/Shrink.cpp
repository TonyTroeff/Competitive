#include <bits/stdc++.h>
using namespace std;

#define ll long long

// #define SINGLE_TEST

void init() {
}

void solve() {
    int n;
    cin >> n;

    cout << 1 << ' ';

    for (int i = n; i > 2; i--)
        cout << i << ' ';

    cout << 2 << endl;
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