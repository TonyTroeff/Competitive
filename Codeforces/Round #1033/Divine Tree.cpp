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
    ll n, m;
    cin >> n >> m;

    const ll min_bound = n, max_bound = n * (n + 1) / 2;
    if (m < min_bound || m > max_bound) cout << -1 << endl;
    else {
        vector ans(n, 0ULL);
        vector used(n + 1, false);

        int ans_index = 0;
        ll diff = m - min_bound;
        while (diff > 0) {
            const ull additive = min(diff, n - (ans_index + 1)), next = additive + 1;
            ans[ans_index++] = next;
            used[next] = true;
            diff -= additive;
        }

        ull used_pos = 1;
        while (ans_index < n) {
            while (used[used_pos]) used_pos++;
            ans[ans_index++] = used_pos;
            used[used_pos] = true;
        }

        cout << ans[0] << endl;
        for (int i = 1; i < n; i++)
            cout << ans[i - 1] << ' ' << ans[i] << endl;
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
