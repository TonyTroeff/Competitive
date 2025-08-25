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

void minimize(vector<int> &v, const int &k) {
    for (int &el: v) {
        const int rem = el % k;
        el = min(rem, k - rem);
    }
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> s(n), t(n);
    for (int &el: s) cin >> el;
    for (int &el: t) cin >> el;

    minimize(s, k);
    minimize(t, k);

    ranges::sort(s);
    ranges::sort(t);

    bool ok = true;
    for (int i = 0; ok && i < n; i++)
        ok = s[i] == t[i];

    cout << (ok ? "YES" : "NO") << endl;
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
