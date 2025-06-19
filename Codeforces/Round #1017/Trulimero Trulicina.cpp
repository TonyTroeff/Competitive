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
    int n, m, k;
    cin >> n >> m >> k;

    vector grid(n, vector(m, 0));
    for (int i = 0, v = 0; i < n; i++) {
        for (int j = 0; j < m; j++, v = (v + 1) % k)
            grid[i][j] = v + 1;
    }

    if (m % k == 0) {
        for (int i = 1; i < n; i += 2) {
            const int last = grid[i][m - 1];
            for (int j = m - 2; j >= 0; j--) grid[i][j + 1] = grid[i][j];
            grid[i][0] = last;
        }
    }

    for (const vector<int> &row: grid) {
        for (const int &el: row) cout << el << " ";
        cout << endl;
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
