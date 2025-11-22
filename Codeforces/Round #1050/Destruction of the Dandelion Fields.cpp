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

    vector<int> a(n);
    for (int &el: a) cin >> el;

    vector<int> odds;
    // odds.reserve(n);

    ll even_sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2) odds.push_back(a[i]);
        else even_sum += a[i];
    }

    ll ans = 0;
    if (!odds.empty()) {
        ans += even_sum;
        ranges::sort(odds);

        const int skip = static_cast<int>(odds.size()) / 2;
        for (int i = skip; i < odds.size(); i++) ans += odds[i];
    }

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