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

void solve() {
    int n;
    cin >> n;

    vector seen(n + 1, false);
    vector ans(n, UNKNOWN);
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;

        if (!seen[val]) {
            seen[val] = true;
            ans[i] = val;
        }
    }

    vector<int> free;
    free.reserve(n);
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) free.push_back(i);
    }

    int free_pos = 0;
    for (int i = 0; i < n; i++) {
        if (ans[i] == UNKNOWN)
            ans[i] = free[free_pos++];
    }

    for (const int& el: ans) cout << el << ' ';
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