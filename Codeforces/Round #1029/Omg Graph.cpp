#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

struct disjoint_set {
    vector<int> group, size, min_weight;

    explicit disjoint_set(const int n) : group(n), size(n, 1), min_weight(n, INT_MAX) {
        for (int i = 0; i < n; i++) group[i] = i;
    }

    int find(const int x) {
        if (group[x] == x) return x;
        return group[x] = find(group[x]);
    }

    void connect(const int a, const int b, const int weight) {
        int g1 = find(a), g2 = find(b);
        if (g1 == g2) min_weight[g1] = min(min_weight[g1], weight);
        else {
            if (size[g1] < size[g2]) swap(g1, g2);

            group[g2] = g1;
            size[g1] += size[g2];
            min_weight[g1] = min(weight, min(min_weight[g1], min_weight[g2]));
        }
    }
};

struct edge {
    int from, to, weight;
};

void init() {
}

void solve() {
    int n, m;
    cin >> n >> m;


    vector<edge> edges(m);
    for (edge &e: edges) cin >> e.from >> e.to >> e.weight;

    ranges::sort(edges, [](const edge &a, const edge &b) { return a.weight < b.weight; });

    int ans = INT_MAX;
    disjoint_set dsu(n + 1);
    for (const edge &e: edges) {
        dsu.connect(e.from, e.to, e.weight);

        int g = dsu.find(1);
        if (g == dsu.find(n))
            ans = min(ans, dsu.min_weight[g] + e.weight);
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
