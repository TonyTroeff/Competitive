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

    ll px, py, qx, qy;
    cin >> px >> py >> qx >> qy;

    const ll x_diff = px - qx, y_diff = py - qy;
    const ll dist_sq = x_diff * x_diff + y_diff * y_diff;

    ll sum = 0, max_len = 0;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;

        sum += a;
        max_len = max(max_len, a);
    }

    const ll min_dist = max(0LL, 2 * max_len - sum);
    const ll min_dist_sq = min_dist * min_dist, max_dist_sq = sum * sum;

    cout << (min_dist_sq <= dist_sq && dist_sq <= max_dist_sq ? "YES" : "NO") << endl;
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
