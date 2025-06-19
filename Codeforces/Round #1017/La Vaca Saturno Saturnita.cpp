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
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    optimized_unordered_map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) mp[a[i]].push_back(i);

    vector<int> divisors(2);
    for (int i = 0; i < q; i++) {
        int k, l, r;
        cin >> k >> l >> r;

        l--;
        r--;

        map<int, int> sw;
        for (int j = 1; j * j <= k; j++) {
            if (k % j != 0) continue;

            divisors[0] = j;
            divisors[1] = k / j;

            for (const int &divisor: divisors) {
                if (!mp.contains(divisor)) continue;

                const vector<int> &indices = mp[divisor];
                const auto &it = ranges::lower_bound(indices, l);
                if (it != indices.end() && *it <= r) sw[*it] = divisor;
            }
        }

        ll ans = 0;
        int interval_start = l;
        for (const auto &[index, divisor]: sw) {
            ans += 1LL * (index - interval_start) * k;

            while (k % divisor == 0) k /= divisor;
            interval_start = index;
        }

        ans += 1LL * (r - interval_start + 1) * k;
        cout << ans << endl;
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
