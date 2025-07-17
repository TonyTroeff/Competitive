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

bool solve(const int&n,const int&k, vector<int>&h) {
    const int lim = h[k - 1];
    ranges::sort(h);

    int pos = static_cast<int>(distance(h.begin(), ranges::upper_bound(h, lim)));
    while (pos < n) {
        if (h[pos] - h[pos - 1] > lim) return false;
        pos++;
    }

    return true;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> h(n);
    for (int &el: h) cin >> el;

    cout << (solve(n, k, h) ? "YES" : "NO") << endl;
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