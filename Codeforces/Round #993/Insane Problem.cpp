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
    int k;
    ll l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    ll target = 1, total_count = 0;
    while (r2 / target >= l1) {
        total_count += max(0LL, min(r1, r2 / target) - max(l1, (l2 - 1) / target + 1) + 1);
        target *= k;
    }

    cout << total_count << endl;
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