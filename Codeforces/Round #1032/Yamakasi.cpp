#include <bits/stdc++.h>
using namespace std;

template <typename... T>
class optimized_unordered_map : public unordered_map<T...> {
public:
    template <typename ...Args>
    explicit optimized_unordered_map(Args&&... args) : unordered_map<T...>(forward<Args>(args)...) {
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

ll count(const vector<ll> &a, const ll &target_sum, const ll &limit) {
    ll ans = 0;

    optimized_unordered_map<ll, int> freq;

    int index = 0;
    while (index < a.size()) {
        ll accumulated_sum = 0;

        freq.clear();
        freq[0] = 1;

        while (index < a.size() && a[index] <= limit) {
            accumulated_sum += a[index];

            ll additive = accumulated_sum - target_sum;
            if (freq.contains(additive)) ans += freq[additive];

            freq[accumulated_sum]++;

            index++;
        }

        index++;
    }

    return ans;
}

void solve() {
    int n;
    ll s, x;
    cin >> n >> s >> x;

    vector<ll> a(n);
    for (ll &el: a) cin >> el;

    const ll ans = count(a, s, x) - count(a, s, x - 1);
    cout << ans << endl;
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
