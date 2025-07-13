#include <bits/stdc++.h>
using namespace std;

template<typename... T>
class optimized_unordered_map : public unordered_map<T...> {
public:
    template<typename... Args>
    explicit optimized_unordered_map(Args &&... args) : unordered_map<T...>(forward<Args>(args)...) {
        this->reserve(1024);
        this->max_load_factor(0.25);
    }
};

#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))
#define UNKNOWN (-1)

// #define SINGLE_TEST

void init() {
}

void dfs(const int node, const int parent, optimized_unordered_map<int, vector<int>> &tree, optimized_unordered_map<int, pair<int, int>> &dp) {
    const int children_count = static_cast<int>(tree[node].size());
    dp[node] = make_pair(children_count, UNKNOWN);

    int best = UNKNOWN, second_best = UNKNOWN;
    for (const int child: tree[node]) {
        if (child == parent) continue;

        dfs(child, node, tree, dp);
        dp[node].first = max(dp[node].first, dp[child].first + children_count - 2);

        if (best == UNKNOWN || dp[child].first > best) {
            second_best = best;
            best = dp[child].first;
        } else if (second_best == UNKNOWN || dp[child].first > second_best) {
            second_best = dp[child].first;
        }
    }

    if (best != UNKNOWN && second_best != UNKNOWN) dp[node].second = best + second_best - 2 + children_count - 2;
}

void solve() {
    int n;
    cin >> n;

    optimized_unordered_map<int, vector<int>> tree;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    optimized_unordered_map<int, pair<int, int>> dp;
    dfs(1, UNKNOWN, tree, dp);

    int ans = 0;
    for (const auto &el: views::values(dp)) ans = max(ans, max(el.first, el.second));

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
