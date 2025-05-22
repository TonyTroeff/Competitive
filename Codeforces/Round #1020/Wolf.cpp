#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int solve(const int n, int l, int r, const int k, const int pos, const vector<int> &p) {
    if (pos < l || pos > r) return -1;

    const int total_greater = n - k, total_lower = k - 1;
    int used_greater = 0, used_lower = 0;
    int diff_greater = 0, diff_lower = 0;
    while (l <= r) {
        const int m = l + (r - l) / 2;
        if (m == pos) return max(diff_greater, diff_lower) * 2;

        if (m < pos) {
            if (used_lower == total_lower) return -1;
            if (p[m - 1] > k) diff_lower++;
            used_lower++;

            l = m + 1;
        } else {
            if (used_greater == total_greater) return -1;
            if (p[m - 1] < k) diff_greater++;
            used_greater++;

            r = m - 1;
        }
    }

    return -1;
}

vector<int> solve() {
    int n, q;
    cin >> n >> q;

    vector<int> p(n);
    for (int &el: p) cin >> el;

    unordered_map<int, int> pos_by_value;
    for (int i = 0; i < n; i++)
        pos_by_value[p[i]] = i + 1;

    vector<int> res(q);
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;

        res[i] = solve(n, l, r, k, pos_by_value[k], p);
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        vector<int> res = solve();
        for (const int &el: res) cout << el << ' ';
        cout << endl;
    }
}
