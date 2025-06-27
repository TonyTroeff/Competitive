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

#define ll long long
#define ull unsigned long long
#define MOD ((ll)(1e9 + 7))

// #define SINGLE_TEST

void init() {
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

    bool requested_repetition = false;

    vector seen(n + 1, false);
    const auto &start = ranges::find_if(graph, [](const vector<int> &el) { return el.size() == 1; });

    stack<pair<int, bool>> s;
    s.emplace(static_cast<int>(distance(graph.begin(), start)), true);

    vector<pair<int, int>> ans;
    ans.reserve(n - 1);

    while (!s.empty()) {
        const auto [node, dir] = s.top();
        s.pop();

        for (const int &next: graph[node]) {
            if (seen[next]) continue;

            int u = node, v = next;
            if (!dir) swap(u, v);

            ans.emplace_back(u, v);

            bool next_dir;
            if (!requested_repetition && graph[next].size() == 2) {
                requested_repetition = true;
                next_dir = dir;
            } else {
                next_dir = !dir;
            }

            s.emplace(next, next_dir);
        }

        seen[node] = true;
    }

    if (!requested_repetition) cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        for (const auto &[u, v]: ans)
            cout << u << ' ' << v << endl;
    }
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
