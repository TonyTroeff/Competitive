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
#define INF 1e9 + 1

// #define SINGLE_TEST

void init() {
}

bool can_reach_end(const int max_cost, const int &n, const vector<int> &batteries, const vector<vector<pair<int, int>>> &passages) {
    vector best(n + 1, UNKNOWN);
    best[1] = 0;

    for (int i = 1; i < n; i++) {
        if (best[i] == UNKNOWN) continue;
        best[i] = min(best[i] + batteries[i - 1], max_cost);

        for (const auto& [next, cost]: passages[i]) {
            if (best[i] < cost) continue;
            best[next] = max(best[next], best[i]);
        }
    }

    return best[n] != UNKNOWN;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> b(n);
    for (int &el: b) cin >> el;

    vector<vector<pair<int, int>>> passages(n + 1);
    for (int i = 0; i < m; i++) {
        int s, t, w;
        cin >> s >> t >> w;

        passages[s].emplace_back(t, w);
    }

    ll low = 0, high = INF;
    while (low <= high) {
        const int mid = low + (high - low) / 2;
        if (can_reach_end(mid, n, b, passages)) high = mid - 1;
        else low = mid + 1;
    }

    if (low > INF) cout << -1 << endl;
    else cout << low << endl;
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
