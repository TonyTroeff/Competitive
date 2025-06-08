#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

ll mod_exp(ll x, ll y, const ll mod) {
    ll ans = 1;
    while (y > 0) {
        if (y % 2 != 0) ans = ans * x % mod;

        x = x * x % mod;
        y /= 2;
    }

    return ans;
}

void init() {
}

int find_split(const int n, const vector<vector<int>> &children) {
    for (int i = 1; i <= n; i++) {
        if (children[i].size() == 2)
            return i;
    }

    return -1;
}

int calc_branch_height(int x, const vector<vector<int>> &children) {
    int length = 1;
    while (children[x].size() > 0) {
        x = children[x][0];
        length++;
    }

    return length;
}

void solve() {
    int n;
    cin >> n;

    vector graph(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector parent(n + 1, 0);
    vector children(n + 1, vector<int>());
    stack<int> s;
    s.push(1);

    while (!s.empty()) {
        const int node = s.top();
        s.pop();

        for (const int &next: graph[node]) {
            if (next == parent[node]) continue;

            parent[next] = node;
            children[node].push_back(next);
            s.push(next);
        }
    }

    int leaves = 0;
    for (int i = 1; i <= n; i++) {
        if (children[i].empty()) leaves++;
    }

    ll ans = 0;
    if (leaves == 1) ans = mod_exp(2, n, MOD);
    else if (leaves == 2) {
        const int split = find_split(n, children);

        const int h1 = calc_branch_height(children[split][0], children);
        const int h2 = calc_branch_height(children[split][1], children);

        const int diff = abs(h1 - h2), rem = n - h1 - h2;
        ans = mod_exp(2, rem, MOD) * (diff == 0 ? 2 : 3 * mod_exp(2, diff - 1, MOD)) % MOD;
    }

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
