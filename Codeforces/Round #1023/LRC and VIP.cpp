#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    const int max = *ranges::max_element(a);
    bool has_other = false;
    for (int i = 0; i < n; i++) {
        if (a[i] != max) {
            has_other = true;
            break;
        }
    }

    if (!has_other) cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        for (const int &el: a) {
            if (el == max) cout << 2 << ' ';
            else cout << 1 << ' ';
        }

        cout << endl;
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) solve();
}
