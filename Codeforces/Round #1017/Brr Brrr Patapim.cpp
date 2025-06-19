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

    vector matrix(n, vector<int>(n));
    for (vector<int> &row: matrix) {
        for (int &el: row) cin >> el;
    }

    vector seen(2 * n + 1, false);
    vector ans(2 * n, 0);

    for (int i = 0; i < n; i++) {
        ans[i + 1] = matrix[0][i];
        seen[matrix[0][i]] = true;
    }

    for (int i = 1; i < n; i++) {
        ans[n + i] = matrix[i][n - 1];
        seen[matrix[i][n - 1]] = true;
    }

    for (int i = 1; i <= 2 * n; i++) {
        if (!seen[i]) {
            ans[0] = i;
            break;
        }
    }

    for (const int &el: ans) cout << el << ' ';
    cout << endl;
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
