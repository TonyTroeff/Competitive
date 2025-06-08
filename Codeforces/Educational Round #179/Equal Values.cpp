#include <algorithm>
#include <iostream>
#include <vector>
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

    int index = 0;
    long long ans = LONG_LONG_MAX;
    while (index < n) {
        const int start = index;
        while (index + 1 < n && a[start] == a[index + 1]) index++;

        const int length = index - start + 1;
        ans = min(ans, static_cast<long long>(n - length) * a[index]);

        index++;
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
