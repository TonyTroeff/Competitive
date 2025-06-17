#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
}

bool all_occurrences_can_be_covered(const int &el, const vector<vector<int>> &a, const int &n, const int &m) {
    int total_freq = 0;
    vector rows_freq(n, 0), cols_freq(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != el) continue;

            rows_freq[i]++;
            cols_freq[j]++;
            total_freq++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int covered = rows_freq[i] + cols_freq[j];
            if (a[i][j] == el) covered--;

            if (covered == total_freq) return true;
        }
    }

    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector a(n, vector<int>(m));
    for (vector<int> &row: a) {
        for (int &el: row) cin >> el;
    }

    int max_el = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            max_el = max(max_el, a[i][j]);
    }

    int ans = max_el;
    if (all_occurrences_can_be_covered(max_el, a, n, m)) ans--;

    cout << ans << endl;
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
