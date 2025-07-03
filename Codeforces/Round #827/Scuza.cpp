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

    int max_seen = 0;
    ll sum = 0LL;

    map<int, ll> mp;
    mp[max_seen] = sum;

    for (int i = 0; i < n; i++) {
        sum += a[i];
        max_seen = max(max_seen, a[i]);

        mp[max_seen] = sum;
    }

    for (int i = 0; i < q; i++) {
        int h;
        cin >> h;

        const auto& it = mp.upper_bound(h);
        cout << prev(it)->second << ' ';
    }

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
