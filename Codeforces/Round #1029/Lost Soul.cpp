#include <bits/stdc++.h>
using namespace std;

#define ll long long

// #define SINGLE_TEST

void init() {
}

int find_best(const int src, const vector<int>& v, const int pos, unordered_map<int, queue<pair<int, int>>>& prev) {
    int ans = 0;

    const auto it = prev.find(v[pos]);
    if (it == prev.end()) return ans;

    queue<pair<int, int>> &q = it->second;

    for (int i = 0; i < q.size(); i++) {
        const auto &f = q.front();
        q.pop();

        const auto &[idx, arr] = f;
        if (idx != pos - 1 || arr == src) ans = max(ans, idx + 1);

        q.push(f);
    }

    return ans;
}

void add_to_prev(const int src, const vector<int>& v, const int pos, unordered_map<int, queue<pair<int, int>>>& prev) {
    queue<pair<int, int>> &q = prev[v[pos]];

    while (q.size() > 3) q.pop();
    q.emplace(pos, src);
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int &el: a) cin >> el;
    for (int &el: b) cin >> el;

    int ans = 0;
    unordered_map<int, queue<pair<int, int>>> prev;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) ans = i + 1;
        else ans = max(ans, max(find_best(1, a, i, prev), find_best(2, b, i, prev)));

        add_to_prev(1, a, i, prev);
        add_to_prev(2, b, i, prev);
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
