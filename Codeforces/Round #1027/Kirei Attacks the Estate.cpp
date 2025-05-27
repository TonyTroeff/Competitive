#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

void solve(const int prev, const int node, const int depth, const pair<long long, long long> &aggregates,
           const vector<int> &a,
           const unordered_map<int, vector<int>> &graph, vector<long long> &res) {
    const int index = node - 1;
    const long long val = a[index];

    if (depth % 2 == 0) res[index] = val + max(aggregates.first, 0LL);
    else res[index] = val + max(aggregates.second, 0LL);

    const auto next_it = graph.find(node);
    if (next_it == graph.end()) return;

    for (const int next_node: next_it->second) {
        if (next_node == prev) continue;

        pair<long long, long long> next_aggregates = depth % 2 == 0
                                                         ? make_pair(res[index], aggregates.second - val)
                                                         : make_pair(aggregates.first - val, res[index]);

        solve(node, next_node, depth + 1, next_aggregates, a, graph, res);
    }
}

vector<long long> solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    unordered_map<int, vector<int>> graph;

    for (int i = 0; i < n - 1; i++) {
        int v, u;
        cin >> v >> u;

        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    vector<long long> res(n);
    solve(0, 1, 1, make_pair(0LL, 0LL), a, graph, res);
    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        const vector<long long> res = solve();
        for (const long long &el: res) cout << el << ' ';
        cout << endl;
    }
}
