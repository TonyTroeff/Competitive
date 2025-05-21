#include <iostream>
#include <vector>
using namespace std;

int solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int &el: a) cin >> el;
    for (int &el: b) cin >> el;

    vector<int> prefix(n);
    int next_pos = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= b[next_pos]) {
            if (++next_pos == m) return 0;
        }

        prefix[i] = next_pos;
    }

    int rev_pos = m - 1, min_res = INT_MAX;
    for (int i = n - 1; i >= 0; i--) {
        if (prefix[i] == rev_pos)
            min_res = min(min_res, b[rev_pos]);

        if (a[i] >= b[rev_pos])
            rev_pos--;
    }

    if (rev_pos == 0) min_res = min(min_res, b[0]);

    if (min_res == INT_MAX) return -1;
    return min_res;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
